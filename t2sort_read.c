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
/**
 * @brief Issue the read request and transfer to wait queue
 * */
static void rque_issue(t2sort_t *h, t2_que_t *r)
{
    void *p = h->_base+(h->head%h->wrap)*h->trln;
    t2_aio_read(&r->aio, h->fd, p, r->ntr*h->trln,
            r->seek*h->trln);
    h->head += r->ntr;
    xque_enque(&h->wait, r);
}

//deque one, issue no wrap read,
//if read incomplete, split, issue and enque part two.
static void try_issue_read2(t2sort_t *h, t2_que_t *stub)
{
    t2_que_t *x, *y; int n, r;
    while(stub->next!=stub&& //can read
            h->done+h->wrap>=h->head+stub->next->ntr) {
        x = xque_deque(stub); assert(x!=stub && x->ntr!=0);
        n = ring_wrap(h->head, x->ntr, h->wrap);
        r = x->ntr-n;
        x->ntr = n;
        rque_issue(h, x); //TODO: if partial issue return a flag!
        if(r>0) {
            y = calloc(1, sizeof(t2_que_t));
            y->flag |= T2_QUE_ALLOC;
            y->ntr  = r;
            y->blk  = x->blk;
            y->seek = x->seek+n;
            rque_issue(h, y);
        }
    }
}

//in sort_reset, prepare the first block
const void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->done += h->nfly;
    try_issue_read2(h, &h->read);

    if(h->done==h->tail) {    //data exhausted
        int nsort = t2_wait_rblock(&h->wait, h->bntr);
        void *pkey = t2_list_keys(h, nsort);
        t2_sort_block(h, pkey, nsort);
        free(pkey);
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
