#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

static int 
t2_wait(t2sort_t *h, t2_que_t *wait, int bntr, t2_que_t *done)
{
    int ntr=0;
    while(wait->next!=wait && ntr<bntr) {
        t2_que_t *x=xque_deque(wait);
        t2_aio_wait(&x->aio, 1);
        if(x->ma!=x->Ma)
            memcpy(h->_base+x->ma%h->_wrap,
                    h->_rblk[x->blk].page, x->Ma-x->ma);
        if(x->Mz!=x->mz)
            memcpy(h->_rblk[x->blk].page, 
                    h->_base+x->mz%h->_wrap, x->Mz-x->mz);
        h->func_cpy_key(h->_base+x->ma%h->_wrap, h->trln, 
                x->ntr, h->kdef, h->_pkey+ntr*h->klen);
        ntr += x->ntr;
        xque_enque(done, x);
    };
    return ntr;
}

void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->done.next->ma  += h->nfly*h->trln;
    h->done.next->ntr -= h->nfly;
    //dbg_wait(h, __func__);
    if(h->done.next->ntr==0 && h->done.next!=&h->done)
        xque_deque(&h->done);
    //make sure submit not overrun on buffers
    if(h->done.next==&h->done) { //data exhausted, sort a block!
        int nsort = t2_wait(h, &h->wait, h->bntr, &h->done);
        t2_sort_block(h, h->_pkey, nsort);
    }
    //Check if done queue left room, submit new read!
    t2_read_submit(h, &h->pool);
    *ntr = MIN((*ntr), h->done.next->ntr);
    h->nfly = (*ntr);
    return h->_base+(h->done.next->ma)%h->_wrap;
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
