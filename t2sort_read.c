#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

static int rque_wait_blk2(t2_que_t *head, int bntr)
{
    int ntr=0;
    t2_que_t *newh=head->next;
    while(newh!=head && ntr<bntr) {
        t2_aio_wait(&newh->aio, 1);
        ntr += newh->ntr;
        newh->flag |= T2SORT_RQUE_FINISH;
        //printf("%s: free(%p)\n", __func__, newh); fflush(0);
        t2_que_t *temp = newh; //avoid use after free()!
        newh = newh->next;
        if(temp->flag & T2SORT_RQUE_ALLOC)
        free(temp);
    };
    head->next = newh; newh->prev = head;
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
    r->flag |= T2SORT_RQUE_SUBMIT;
    h->head += r->ntr;
    //printf("  %s: ntr=%d\n", __func__, r->ntr);
    t2_que_t *xtail = h->wait.prev;
    xtail->next = r; r->prev = xtail;
    r->next = &h->wait; h->wait.prev = r;
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
            y->flag |= T2SORT_RQUE_ALLOC;
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
        int nsort = rque_wait_blk2(&h->wait, h->bntr);
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
