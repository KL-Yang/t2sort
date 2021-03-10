#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

t2sort_que_t *
rque_new(t2sort_que_t *tail, int ntr, int dblk, int seek)
{
    if(ntr==0)  //do nothing
        return tail;

    t2sort_que_t *xque = calloc(1, sizeof(t2sort_que_t));
    xque->ntr  = ntr;
    xque->blk  = dblk;
    xque->seek = seek;
    tail->next = xque;
    xque->id   = tail->id+1;
    return xque;
}

//each time read h->pntr*h->wioq
static t2sort_que_t *
t2sort_sort_rque(void *pkey, int nkey, int klen, int bntr)
{
    t2sort_pay_t *payl=pkey;
    t2sort_que_t *head, *tail;
    int nblk = ceilf(nkey*1.0f/bntr), f[nblk], n[nblk];

    tail = head = calloc(1, sizeof(t2sort_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0; k<nkey; k+=bntr) {
        int xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, payl=(void*)payl+klen)
            n[payl->bpi.blk]++;

        for(int i=0; i<nblk; i++) {
            tail = rque_new(tail, n[i], i, i*bntr+f[i]);
            f[i] += n[i];
        }
    }
    tail = head;
    head = head->next;
    free(tail);
    return head;
}

//TODO: here break the read list at boundary!!!
t2sort_que_t *
t2sort_rque_break(t2sort_que_t *rque, int *nque, int nkey, int wrap)
{
    int nwrap=nkey/wrap, sum=0, nxque=0;
    t2sort_que_t *xque = calloc(*nque+nwrap, sizeof(t2sort_que_t));
    for(int i=0, j=0; i<*nque; i++,j++,nxque++) {
        if(sum/wrap!=(sum+rque[i].ntr)/wrap) {
            int res=(sum+rque[i].ntr)%wrap;
            if(res!=0) {    //break one to two
                assert(res<=rque[i].ntr);
                memcpy(&xque[j+0], &rque[i], sizeof(t2sort_que_t));
                memcpy(&xque[j+1], &rque[i], sizeof(t2sort_que_t));
                xque[j+0].ntr=xque[j].ntr-res; 
                xque[j+1].ntr=res;
                xque[j+1].seek+=xque[j].ntr;
                nxque++;
                j++;
            }
        }
        memcpy(&xque[j], &rque[i], sizeof(t2sort_que_t));
        sum += rque[i].ntr;
    }
    assert(sum==nkey);
    assert(nxque<=(*nque+nwrap));
    free(rque);
    *nque = nxque;
    xque = realloc(xque, nxque*sizeof(t2sort_que_t));
    return xque;
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
    //2. read all keys in memory, may exceed bsize.
    dbg_blocks_check(h);

    void *key;
    key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    //3. sort all keys
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. build read queue!
    h->rque = t2sort_sort_rque(key, h->nkey, h->klen, 
                h->pntr*h->wioq);
    //debug
    int xsum=0; t2sort_que_t *xtail = h->rque;
    while(xtail!=NULL) {
        xsum += xtail->ntr;
        xtail = xtail->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    
    //h->rque = t2sort_rque_break(h->rque, &h->nque, h->nkey, 
    //            h->pntr*(h->wioq+1));
    //5. release the key memories.
    free(key);

    //1. free wpile buffers
    t2sort_free_wpile(h->pile);
    free(h->_base);

    //for reference implementation
    h->_base = calloc(h->pntr*(h->wioq+1), h->trlen);
    h->nwrap = h->pntr*h->wioq;

    //read for a block
    return 0;
}

#endif
