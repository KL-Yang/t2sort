#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

static int 
t2_wait_rblock(t2sort_t *h, t2_que_t *wait, int bntr, t2_que_t *DONe)
{
    int ntr=0;
    while(wait->next!=wait && ntr<bntr) {
        t2_que_t *xque=xque_deque(wait);
        t2_aio_wait(&xque->aio, 1);
        if(xque->ma!=xque->Ma)
            memcpy(h->_base+xque->ma%h->_wrap,
                    h->_rblk[xque->blk].page, xque->Ma-xque->ma);
        if(xque->Mz!=xque->mz)
            memcpy(h->_rblk[xque->blk].page, 
                h->_base+xque->mz%h->_wrap, xque->Mz-xque->mz);
        h->func_cpy_key(h->_base+xque->ma%h->_wrap, h->trln, 
                xque->ntr, h->kdef, h->_pkey+ntr*h->klen);
        ntr += xque->ntr;
        xque_enque(DONe, xque);
    };
    return ntr;
}

void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->DONe.next->ma  += h->nfly*h->trln;
    h->DONe.next->ntr -= h->nfly;

    if(h->DONe.next->ntr==0 && h->DONe.next!=&h->DONe)
        xque_deque(&h->DONe);
    //make sure submit not overrun on buffers
    if(h->DONe.next==&h->DONe) { //data exhausted, sort a block!
        int nsort = t2_wait_rblock(h, &h->wait, h->bntr, &h->DONe);
        t2_sort_block(h, h->_pkey, nsort);
    }
    //Check if DONe queue left room, submit new read!
    t2_read_submit(h, &h->read);
    *ntr = MIN((*ntr), h->DONe.next->ntr);
    h->nfly = (*ntr);
    return h->_base+(h->DONe.next->ma)%h->_wrap;
}

int t2sort_read(t2sort_h h, void *p, int ntr)
{
    int left=ntr; void *pdes=p; const void *praw;
    while(left>0) {
        int nget = left;
        praw = t2sort_readraw(h, &nget);
        if(nget<=0)
            break;
        memcpy(pdes, praw, h->trln*nget);
        left -= nget;
        pdes += nget*h->trln;
    };
    assert(left!=ntr);
    return (ntr-left);
}
#endif
