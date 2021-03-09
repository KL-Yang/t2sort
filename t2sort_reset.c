#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

//each time read h->wpntr*h->wioq
static t2sort_que_t *
t2sort_sort_rque(void *key, int nkey, int klen, int bntr, 
                int *nrque)
{

    int xntr, nblk = ceilf(nkey*1.0f/bntr);
    int f[nblk], n[nblk], l[nblk]; void *bkey=key;
    int nque=0;
    t2sort_que_t *rque = calloc(nblk*nblk, sizeof(t2sort_que_t));
    for(int k=0, mblk=0; k<nkey; k+=bntr, mblk++) {
        xntr = MIN(bntr, nkey-k);
        for(int i=0; i<nblk; i++) {
            f[i] = INT_MAX;
            l[i] = -1;
            n[i] = 0;
        }
        for(int j=0; j<xntr; j++, bkey+=klen) {
            int blk = ((t2sort_pay_t*)bkey)->bpi.blk;
            int idx = ((t2sort_pay_t*)bkey)->bpi.idx;
            f[blk] = MIN(f[blk], idx);
            n[blk]++;
            l[blk] = MAX(l[blk], idx);
        }
        int sum = 0;
        for(int i=0; i<nblk; i++) {
            if(l[i]!=(-1)) {
                assert(n[i]==l[i]-f[i]+1);
                rque[nque].ntr  = n[i];
                rque[nque].blk  = i;
                rque[nque].seek = i*bntr+f[i];
                rque[nque].mblk = mblk;
                nque++;
            }
            sum += n[i];
        }
        assert(sum==xntr);
    }
    *nrque = nque;
    rque = realloc(rque, nque*sizeof(t2sort_que_t));
    return rque;
}

int t2sort_reset(t2sort_h h)
{
    //flush piles of the last block
    if(h->pile->ntr!=0)
        t2sort_wblock_process(h, h->pile);
    //wait all piles write finishes
    pile_t *head=h->pile->next, *tail=head;
    do {
        t2sort_aio_wait(&tail->cb, 1);
        tail = tail->next;
    } while(tail!=head);

    //read keys to the buffer for sorting!
    //1. free wpile buffers
    free(h->_base);
    t2sort_free_wpile(h->pile);
    //2. read all keys in memory, may exceed bsize.
    dbg_blocks_check(h);

    void *key;
    key = malloc(h->winst*h->klen);
    pread(h->fd_keys, key, h->winst*h->klen, 0);
    //3. sort all keys
    qsort(key, h->winst, h->klen, h->func_cmp_key);
    //4. build read queue!
    h->rque = t2sort_sort_rque(key, h->winst, h->klen, 
                h->wpntr*h->wioq, &h->nque);
    //5. release the key memories.
    free(key);
    return 0;
}

#endif
