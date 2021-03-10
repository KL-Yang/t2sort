#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

//  use two queue
//  rhead,    rslot
// 1. read que, deque for aio_read, and attach to wait que
//      read que move forward rhead, and reduces rslot
// 2. wait que, deque for aio_wait, and ready to end user
//      wait que move forward rtail only
//  rtail
// 3. If user already retrieve the result, move forward
//  rdone, and increase rslot to allow more read
//
//  from rdone->rtail is readily availabe to give user
//  to increase rtail, need access wait que for block and sort
//  to increase rhead, need access read que.

//return the maximum size without wrap as first part!
int ring_wrap(int i, int d, int n)
{
    if(i%n+d<=n)
        return d;
    return (n-(i%n));
}

void sort_one_block(t2sort_t *h, void *pkey, int nkey) 
{
    void **ptr, *tmp; int *map;
    tmp = malloc(h->trlen);
    map = malloc(nkey*sizeof(int));
    ptr = malloc(nkey*sizeof(void*));
    for(int64_t i=0; i<nkey; i++) {
        ptr[i] = ((t2sort_pay_t*)(pkey+i*h->klen))->ptr;
        ((t2sort_pay_t*)(pkey+i*h->klen))->idx = i;
    }
    qsort(pkey, nkey, h->klen, h->func_cmp_key);
    for(int64_t i=0; i<nkey; i++)
        map[i] = ((t2sort_pay_t*)(pkey+i*h->klen))->idx;
    t2sort_map_sort(ptr, nkey, map, h->trlen, tmp);
    free(tmp);
    free(map);
    free(ptr);
}

//sort from h->rtail, +nsort
void t2sort_one_rblock(t2sort_t *h, int nsort)
{
    void *buff, *pkey;
    int part1 = ring_wrap(h->rtail, nsort, h->nwrap);

    pkey = malloc(nsort*h->klen);
    buff = h->_base+(h->rtail%h->nwrap)*h->trlen;
    h->func_cpy_key(buff, h->trlen, part1, h->kdef, pkey);
    printf("%s: part1=%d nsort=%d\n", __func__, part1, nsort);
    fflush(0);
    if(part1<nsort) {
        h->func_cpy_key(h->_base, h->trlen, nsort-part1, 
                h->kdef, pkey+part1*h->klen);
    }
    sort_one_block(h, pkey, nsort);
    free(pkey);
}

//count how many trace in the waiting queue!
int rque_wait_ntr(t2sort_que_t *head, t2sort_que_t *tail) 
{
    int ntr=0;
    while(head!=tail) {
        ntr += head->ntr;
        printf("%s: ntr=%8d @ %p\n", __func__, ntr, head); fflush(0);
        head = head->next;
    };
    return ntr;
}

int rque_wait_blk(t2sort_que_t *head, t2sort_que_t **tail, int bntr)
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
//h->rinst = h->pntr*h->wioq;
const void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    h->rslot += h->rdfly;   //land the flying buffer
    h->rdone += h->rdfly;
    if(h->rdone==h->rtail) {
        if(rque_wait_ntr(&h->wait_head, h->wait)<h->bntr)
            try_issue_read(h); //need further issue read queue!
        int nsort = rque_wait_blk(&h->wait_head, &h->wait, h->bntr);
        t2sort_one_rblock(h, nsort);
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
