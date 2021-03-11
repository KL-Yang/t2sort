#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

//remove the first item from the queue
static t2sort_que_t * rque_deque(t2sort_que_t **head)
{
    t2sort_que_t *x = *head;
    *head = (*head)->next;
    x->next = NULL;
    return x;
}
static void rque_enque(t2sort_que_t **tail, t2sort_que_t *x)
{
    (*tail)->next = x;
    (*tail) = x;
}

static int rque_wait_blk(t2sort_que_t *head, t2sort_que_t **tail, int bntr)
{
    int ntr=0;
    t2sort_que_t *newh=head->next;
    while(newh!=NULL && ntr<bntr) {
        t2sort_aio_wait(&newh->aio, 1);
        ntr += newh->ntr;
        newh->flag |= T2SORT_RQUE_FINISH;
        free(newh);
        newh = newh->next;
    };
    head->next = newh;
    if(newh==NULL) { *tail = head; } 
    else { assert(ntr==bntr); }
    return ntr;
}

/**
 * @brief Issue the read request and transfer to wait queue
 * */
static void rque_issue(t2sort_t *h, t2sort_que_t *r)
{
    void *p = h->_base+(h->rhead%h->nwrap)*h->trlen;
    t2sort_aio_read(&r->aio, h->fd, p, r->ntr*h->trlen,
            r->seek*h->trlen);
    r->flag |= T2SORT_RQUE_SUBMIT;
    h->rhead += r->ntr;
    printf("  %s: ntr=%d\n", __func__, r->ntr);
    rque_enque(&h->wait, r);    //attach to wait queue
}

//issue as much read as possibly can
static void try_issue_read(t2sort_t *h) {
    while(h->read!=NULL && 
            (h->rdone+h->nwrap-h->rhead)>=h->read->ntr) { //can read
        t2sort_que_t *x;
        x = rque_deque(&h->read);   //deque
        x = rque_split(h, x);       //split if required
        do {
            rque_issue(h, x);
            x = x->next;
        } while(x!=NULL);
    }
}

//in sort_reset, prepare the first block
const void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->rdone += h->rdfly;   //h->ndata-=h->rdfly.
    try_issue_read(h);
    //try to issue read right now!!!

    if(h->rdone==h->rtail) {    //data exhausted
        int nsort = rque_wait_blk(&h->wait_head, &h->wait, h->bntr);
        void *pkey = t2sort_list_key(h, nsort);
        sort_one_block(h, pkey, nsort);
        free(pkey);
        h->rtail+=nsort;
    }

    void *praw;
    *ntr = MIN(*ntr, h->rtail-h->rdone);
    *ntr = ring_wrap(h->rdone, (*ntr), h->nwrap);
    praw = h->_base+(h->rdone%h->nwrap)*h->trlen;
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
        memcpy(pdes, praw, h->trlen*nget);
        left -= nget;
        pdes += nget*h->trlen;
    };
    return (ntr-left);
}

#endif
