#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

//build the queue, break all read large than pntr!
static t2sort_que_t *
t2sort_sort_rque2(t2sort_que_t *head, void *pkey, int nkey, 
        int klen, int bntr, int nblk, int pntr)
{
    nblk = ceilf(nkey*1.0f/bntr);
    int f[nblk], n[nblk], x=0; t2sort_que_t *xque;
    xque = calloc(2*nblk*nblk, sizeof(t2sort_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0, xntr; k<nkey; k+=bntr) {
        xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, pkey+=klen)
            n[((t2_pay_t*)pkey)->bpi.blk]++;
        for(int i=0; i<nblk; i++) {
            while(n[i]!=0) {
                xque[x].ntr  = MIN(n[i], pntr);
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                xque[x].id   = x;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                x++;
            }
        }
    } assert(x<=2*nblk*nblk);
    return realloc(xque, x*sizeof(t2sort_que_t));
}

int t2sort_sort(t2sort_h h)
{
    //1. flush piles of the last block
    if((h->rhead+=h->nfly)>h->rtail)
        t2_flush_block(h, h->rhead-h->rtail);
    t2sort_que_t *xque = xque_deque(&h->wait);
    while(xque!=&h->wait && xque->ntr>0) {
        t2sort_aio_wait(&xque->aio, 1);
        h->rdone+=xque->ntr;
        xque = xque_deque(&h->wait);
    };
    free(h->xque);

    //2. read all keys in memory, may exceed bsize.
    h->nkey = h->rhead;
    dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);
    //abort();

    void *key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    //3. sort all keys
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. clear and rebuild read queue!
    h->wait.prev = h->wait.next = &h->wait;
    h->read.prev = h->read.next = &h->read;
    t2sort_sort_rque2(&h->read, key, h->nkey, h->klen, 
            h->bntr, h->nblk, h->pntr);
    //debug
    int xsum=0; 
    t2sort_que_t *xhead = h->read.next;
    while(xhead!=&h->read) {
        xsum += xhead->ntr;
        xhead = xhead->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    free(key);
    //abort();

    //read for a block
    h->rhead = 0;
    h->rtail = 0;
    h->rdone = 0;
    h->nfly = 0;

    return 0;
}

#endif
