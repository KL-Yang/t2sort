#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

//add to tail
static void xque_enque(t2sort_que_t *head, t2sort_que_t *x)
{
    t2sort_que_t *tail = head->prev;
    tail->next = x; x->prev = tail;
    head->prev = x; x->next = head;
}
//remove from head
t2sort_que_t * xque_deque(t2sort_que_t *head)
{
    t2sort_que_t *item = head->next;
    head->next = item->next;    //note item may be head!
    return item;
}

//build the queue, break all read large than pntr!
static t2sort_que_t *
t2sort_sort_rque2(t2sort_que_t *head, void *pkey, int nkey, 
        int klen, int bntr, int nblk, int pntr)
{
    nblk = ceilf(nkey*1.0f/bntr); int ysum=0, zsum=0;
    int f[nblk], n[nblk], x=0; t2sort_que_t *xque;
    xque = calloc(2*nblk*nblk, sizeof(t2sort_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0, xntr; k<nkey; k+=bntr) {
        xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, pkey+=klen)
            n[((t2sort_pay_t*)pkey)->bpi.blk]++;
        for(int i=0; i<nblk; i++) {
            zsum += n[i];
            while(n[i]!=0) {
                xque[x].ntr  = MIN(n[i], pntr);
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                xque[x].id   = x;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                printf("%s: id=%4d ntr=%d\n", __func__, x, 
                        xque[x].ntr);
                ysum += xque[x].ntr;
                x++;
            }
        }
    } assert(x<=2*nblk*nblk);
    printf("%s: ysum=%d zsum=%d x=%d\n", __func__, ysum, zsum, x);
    return realloc(xque, x*sizeof(t2sort_que_t));
}


int t2sort_sort(t2sort_h h)
{
    //flush piles of the last block
    h->rhead += h->rdfly;
    if(h->rhead>h->rtail) {
        t2sort_write_block(h, h->rhead-h->rtail);
    }
    for(;h->xtail<h->xhead; h->xtail++) {
        int j=h->xtail%h->nxque;
        t2sort_aio_wait(&h->xque[j].aio, 1);
        h->rdone+=h->xque[j].ntr;
    }
    //read keys to the buffer for sorting!
    //2. read all keys in memory, may exceed bsize.
    h->nkey = h->rhead;
    dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);
    //abort();

    void *key;
    key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    //3. sort all keys
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. build read queue!
    //h->read = t2sort_sort_rque(key, h->nkey, h->klen, 
    //            h->pntr*h->wioq);
    t2sort_sort_rque2(&h->read2, key, h->nkey, h->klen, 
            h->bntr, h->nblk, h->pntr);
    //debug
    int xsum=0; 
    t2sort_que_t *xhead = h->read2.next;
    while(xhead!=&h->read2) {
        xsum += xhead->ntr;
        printf("xhead->id=%6d  ntr=%8d sum=%8d\n", xhead->id,
                    xhead->ntr, xsum);
        xhead = xhead->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    free(key);
    //abort();

    //1. free wpile buffers
    free(h->_base);

    //for reference implementation
    h->nwrap = h->pntr*(h->wioq+1);
    h->_base = calloc(h->nwrap, h->trln);
    free(h->xque);

    //read for a block
    h->rhead = 0;
    h->rtail = 0;
    h->rdone = 0;
    h->rdfly = 0;

    return 0;
}

#endif
