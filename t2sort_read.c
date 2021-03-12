#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

static int rque_wait_blk2(t2sort_que_t *head, int bntr)
{
    int ntr=0;
    t2sort_que_t *newh=head->next;
    while(newh!=head && ntr<bntr) {
        t2sort_aio_wait(&newh->aio, 1);
        ntr += newh->ntr;
        newh->flag |= T2SORT_RQUE_FINISH;
        printf("%s: free(%p)\n", __func__, newh); fflush(0);
        t2sort_que_t *temp = newh; //avoid use after free()!
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
static void rque_issue(t2sort_t *h, t2sort_que_t *r)
{
    void *p = h->_base+(h->rhead%h->wrap)*h->trln;
    t2sort_aio_read(&r->aio, h->fd, p, r->ntr*h->trln,
            r->seek*h->trln);
    r->flag |= T2SORT_RQUE_SUBMIT;
    h->rhead += r->ntr;
    printf("  %s: ntr=%d\n", __func__, r->ntr);
    t2sort_que_t *xtail = h->wait2.prev;
    xtail->next = r; r->prev = xtail;
    r->next = &h->wait2; h->wait2.prev = r;
}

//deque one, issue no wrap read,
//if read incomplete, split, issue and enque part two.
static void try_issue_read2(t2sort_t *h, t2sort_que_t *head) 
{
    t2sort_que_t *x, *y; int n, r;
    while(head->next!=head && //can read
            h->rdone+h->wrap>=h->rhead+head->next->ntr) {
        x = xque_deque(head); assert(x!=head && x->ntr!=0);
        n = ring_wrap(h->rhead, x->ntr, h->wrap);
        r = x->ntr-n;
        x->ntr = n;
        rque_issue(h, x); //TODO: if partial issue return a flag!
        if(r>0) {
            y = calloc(1, sizeof(t2sort_que_t));
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
    h->rdone += h->rdfly;   //h->ndata-=h->rdfly.
    try_issue_read2(h, &h->read2);
    //try to issue read right now!!!

    if(h->rdone==h->rtail) {    //data exhausted
        int nsort = rque_wait_blk2(&h->wait2, h->bntr);
        void *pkey = t2sort_list_key(h, nsort);
        sort_one_block(h, pkey, nsort);
        free(pkey);
        h->rtail+=nsort;
    }

    void *praw;
    *ntr = MIN(*ntr, h->rtail-h->rdone);
    *ntr = ring_wrap(h->rdone, (*ntr), h->wrap);
    praw = h->_base+(h->rdone%h->wrap)*h->trln;
    h->rdfly = *ntr;
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
