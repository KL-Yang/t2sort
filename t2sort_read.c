#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

static int t2_wait_rblock(t2_que_t *stub, int bntr)
{
    int ntr=0;
    while(stub->next!=stub && ntr<bntr) {
        t2_que_t *xque=xque_deque(stub);
        t2_aio_wait(&xque->aio, 1);
        ntr += xque->ntr;
        if(xque->flag & T2_QUE_ALLOC)
            free(xque);
    };
    return ntr;
}
void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->done += h->nfly;
    try_issue_read(h, &h->read);

    if(h->done==h->tail) {    //data exhausted
        int nsort = t2_wait_rblock(&h->wait, h->bntr);
        t2_list_keys(h, nsort);
        t2_sort_block(h, h->_pkey, nsort);
        h->tail+=nsort;
    }

    *ntr = MIN(*ntr, h->tail-h->done);
    *ntr = ring_wrap(h->done, (*ntr), h->wrap);
    void *praw = h->_base+(h->done%h->wrap)*h->trln;
    h->nfly = *ntr;
    return praw;
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
