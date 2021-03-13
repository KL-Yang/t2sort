#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT

static int ring_wrap(int i, int d, int n)   //maximum d without wrap
{
    int r=(i%n+d<=n)?(d):(n-(i%n));
    return r;
}

void * t2_list_keys(t2sort_t *h, int nsort)
{
    int nowrap = ring_wrap(h->rtail, nsort, h->wrap);
    void *pkey = malloc(nsort*h->klen);
    void *buff = h->_base+(h->rtail%h->wrap)*h->trln;
    h->func_cpy_key(buff, h->trln, nowrap, h->kdef, pkey);
    if(nowrap<nsort)
        h->func_cpy_key(h->_base, h->trln, nsort-nowrap, 
                h->kdef, pkey+nowrap*h->klen);
    return pkey;
}

static void t2_sort_block(t2sort_t *h, void *pkey, int nkey) 
{
    void **ptr, *tmp; int *map; //TODO: pre-allocate in init
    tmp = malloc(h->trln);
    map = malloc(nkey*sizeof(int));
    ptr = malloc(nkey*sizeof(void*));
    for(int64_t i=0; i<nkey; i++) {
        ptr[i] = ((t2_pay_t*)(pkey+i*h->klen))->ptr;
        ((t2_pay_t*)(pkey+i*h->klen))->idx = i;
    }
    qsort(pkey, nkey, h->klen, h->func_cmp_key);
    for(int64_t i=0; i<nkey; i++)
        map[i] = ((t2_pay_t*)(pkey+i*h->klen))->idx;
    t2sort_map_sort(ptr, nkey, map, h->trln, tmp);
    free(tmp);
    free(map);
    free(ptr);
}

static void t2_flush_block(t2sort_t *h, int nsort)
{
    void *key, *p;
    key = t2_list_keys(h, nsort);
    t2_sort_block(h, key, nsort);
    for(int i=0; i<nsort; i++) {
        ((t2_pay_t*)(key+i*h->klen))->bpi.blk = h->nblk;
        ((t2_pay_t*)(key+i*h->klen))->bpi.idx = i;
    }
    h->nblk++;
    write(h->fd_keys, key, nsort*h->klen);
    for(int i=0; i<nsort; i+=h->pntr) {
        t2sort_que_t *xque = xque_deque(&h->read); 
        assert(xque!=&h->read); //que exhausted
        //xque->ntr = MIN(h->pntr, nsort-i);
        xque->ntr = h->pntr;    //last pile may have some garbage
        p = h->_base+(h->rtail%h->wrap)*h->trln;
        t2sort_aio_write(&xque->aio, h->fd, p, xque->ntr*h->trln, 
                h->rtail*h->trln);
        h->rtail += xque->ntr;
        xque_enque(&h->wait, xque);
    }
    free(key);
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    if((h->head+=h->nfly)>=h->rtail+h->bntr)   //delayed flush
        t2_flush_block(h, h->bntr); 

    //do not cross block and ring buffer boundary!
    *ntr = ring_wrap(h->head, (*ntr), h->wrap);
    *ntr = MIN((*ntr), h->rtail+h->bntr-h->head);

    //wait all to satisfy *ntr since user requested
    while(h->rdone+h->wrap<h->head+(*ntr)) {  //must wait
        t2sort_que_t *xque = xque_deque(&h->wait);
        assert(xque!=&h->wait && xque->ntr);
        t2sort_aio_wait(&xque->aio, 1);
        h->rdone+=xque->ntr;
        memset(xque, 0, sizeof(t2sort_que_t));  //for safty!
        xque_enque(&h->read, xque);
    }
    void *praw = h->_base+(h->head%h->wrap)*h->trln;
    h->nfly = *ntr;
    return praw;
}

int t2sort_write(t2sort_h h, const void *p, int ntr)
{
    int left=ntr, nput;
    void *praw; const void *psrc = p;
    while(left>0) {
        nput = left;
        praw = t2sort_writeraw(h, &nput);
        assert(nput>0);
        memcpy(praw, psrc, h->trln*nput);
        left -= nput;
        psrc += nput*h->trln;
    };
    return (ntr-left);
}
#endif
