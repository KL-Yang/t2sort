#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT

static int ring_wrap(int i, int d, int n)   //maximum d without wrap
{
    int r=(i%n+d<=n)?(d):(n-(i%n));
    return r;
}

static void t2_list_keys(t2sort_t *h, int nsort)
{
    int nowrap = ring_wrap(h->tail, nsort, h->wrap);
    void *buff = h->_base+(h->tail%h->wrap)*h->trln;
    h->func_cpy_key(buff, h->trln, nowrap, h->kdef, h->_pkey);
    if(nowrap<nsort)
        h->func_cpy_key(h->_base, h->trln, nsort-nowrap, 
                h->kdef, h->_pkey+nowrap*h->klen);
}

static void t2_sort_block(t2sort_t *h, void *pkey, int nkey) 
{
//#pragma GCC ivdep
    for(int64_t i=0; i<nkey; i++) {
        h->_pptr[i] = ((t2_pay_t*)(pkey+i*h->klen))->ptr;
        ((t2_pay_t*)(pkey+i*h->klen))->idx = i;
    }
    qsort(pkey, nkey, h->klen, h->func_cmp_key);
//#pragma GCC ivdep
    for(int64_t i=0; i<nkey; i++)
        h->_imap[i] = ((t2_pay_t*)(pkey+i*h->klen))->idx;
    t2sort_map_sort(h->_pptr, nkey, h->_imap, h->trln, h->_temp);
}

static void t2_flush_block(t2sort_t *h, int nsort)
{
    t2_list_keys(h, nsort);
    t2_sort_block(h, h->_pkey, nsort);
//#pragma GCC ivdep
    for(int i=0; i<nsort; i++) {
        ((t2_pay_t*)(h->_pkey+i*h->klen))->bpi.blk = h->nblk;
        ((t2_pay_t*)(h->_pkey+i*h->klen))->bpi.idx = i;
    }
    h->nblk++;
    write(h->fd_keys, h->_pkey, nsort*h->klen);
    for(int i=0; i<nsort; i+=h->pntr) {
        t2_que_t *xque = xque_deque(&h->pool); 
        assert(xque!=&h->pool); //que exhausted
        //xque->ntr = MIN(h->pntr, nsort-i);    //align issue
        xque->ntr = h->pntr;    //last pile may have some garbage
        void *p = h->_base+(h->tail%h->wrap)*h->trln;
        t2_aio_write(&xque->aio, h->fd, p, xque->ntr*h->trln, 
                h->tail*h->trln);
        h->tail += xque->ntr;
        xque_enque(&h->wait, xque);
    }
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    //dbg_wait(h, __func__);
    if((h->head+=h->nfly)>=h->tail+h->bntr)
        t2_flush_block(h, h->bntr); 
    //ensure not cross block and ring boundary!
    *ntr = ring_wrap(h->head, (*ntr), h->wrap);
    *ntr = MIN((*ntr), h->tail+h->bntr-h->head);
    //have to wait for completion
    while(h->disk+h->wrap<h->head+(*ntr)) {
        t2_que_t *xque = xque_deque(&h->wait);
        assert(xque!=&h->wait && xque->ntr);
        t2_aio_wait(&xque->aio, 1);
        h->disk+=xque->ntr;
        xque_enque(&h->pool, xque);
    }
    h->nfly = *ntr;
    return (h->_base+(h->head%h->wrap)*h->trln);
}

int t2sort_write(t2sort_h h, const void *p, int ntr)
{
    int left=ntr, nput; const void *psrc = p;
    while(left>0) {
        nput = left;
        void *praw = t2sort_writeraw(h, &nput);
        assert(nput>0);
        memcpy(praw, psrc, h->trln*nput);
        left -= nput;
        psrc += nput*h->trln;
    };
    return (ntr-left);
}
#endif
