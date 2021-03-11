#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

//count how many trace in the waiting queue!
static int rque_wait_ntr(t2sort_que_t *head, t2sort_que_t *tail) 
{
    int ntr=0;
    while(head!=tail) {
        ntr += head->ntr;
        printf("%s: ntr=%8d @ %p\n", __func__, ntr, head); fflush(0);
        head = head->next;
    };
    return ntr;
}

static int rque_wait_blk(t2sort_que_t *head, t2sort_que_t **tail, int bntr)
{
    int ntr=0;
    t2sort_que_t *newh=head->next;
    while(newh!=NULL && ntr<bntr) {
        t2sort_aio_wait(newh->aio, 1);
        free(newh->aio);
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

//in sort_reset, prepare the first block
const void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->rslot += h->rdfly;   //land the flying buffer
    h->rdone += h->rdfly;   //h->ndata-=h->rdfly.
    if(h->rdone==h->rtail) {    //h->ndata==0
        if(rque_wait_ntr(&h->wait_head, h->wait)<h->bntr)
            try_issue_read(h); //need further issue read queue!
        int nsort = rque_wait_blk(&h->wait_head, &h->wait, h->bntr);
        void *pkey = t2sort_list_key(h, nsort);
        sort_one_block(h, pkey, nsort);
        free(pkey);
        h->rtail+=nsort;
    } else try_issue_read(h);

    void *praw;
    *ntr = MIN(*ntr, h->rtail-h->rdone);
    *ntr = ring_wrap(h->rdone, (*ntr), h->nwrap);
    praw = h->_base+(h->rdone%h->nwrap)*h->trlen;
    h->rdfly = *ntr;
    return praw;
}

int t2sort_read(t2sort_h h, void *p, int ntr)
{
    int left=ntr, nget; 
    void *pdes = p; const void *praw;
    while(left>0) {
        nget = left;
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
