#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT
//return the maximum size without wrap as first part!
static int ring_wrap(int i, int d, int n)
{
    if(i%n+d<=n)
        return d;
    return (n-(i%n));
}

void * t2sort_list_key(t2sort_t *h, int nsort)
{
    void *buff, *pkey;
    int part1 = ring_wrap(h->rtail, nsort, h->wrap);
    pkey = malloc(nsort*h->klen);
    buff = h->_base+(h->rtail%h->wrap)*h->trln;
    h->func_cpy_key(buff, h->trln, part1, h->kdef, pkey);
    if(part1<nsort)
        h->func_cpy_key(h->_base, h->trln, nsort-part1, 
                h->kdef, pkey+part1*h->klen);
    return pkey;
}

static void sort_one_block(t2sort_t *h, void *pkey, int nkey) 
{
    void **ptr, *tmp; int *map;
    tmp = malloc(h->trln);
    map = malloc(nkey*sizeof(int));
    ptr = malloc(nkey*sizeof(void*));
    for(int64_t i=0; i<nkey; i++) {
        ptr[i] = ((t2sort_pay_t*)(pkey+i*h->klen))->ptr;
        ((t2sort_pay_t*)(pkey+i*h->klen))->idx = i;
    }
    qsort(pkey, nkey, h->klen, h->func_cmp_key);
    for(int64_t i=0; i<nkey; i++)
        map[i] = ((t2sort_pay_t*)(pkey+i*h->klen))->idx;
    t2sort_map_sort(ptr, nkey, map, h->trln, tmp);
    free(tmp);
    free(map);
    free(ptr);
}

static void t2sort_write_block(t2sort_t *h, int nsort)
{
    void *key, *p;
    key = t2sort_list_key(h, nsort);
    sort_one_block(h, key, nsort);
    for(int i=0; i<nsort; i++) {
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.blk = h->nblk;
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.idx = i;
    }
    h->nblk++;
    write(h->fd_keys, key, nsort*h->klen);
    //use ring buffer to handle the write queue!!!
    for(int i=0, j, ntr; i<h->wioq; i++) {
        assert(h->xhead-h->xtail<h->nxque);
        j = h->xhead%h->nxque;
        ntr = MIN(h->pntr, nsort-i*h->pntr);
        if(ntr<=0) 
            break;
        h->xque[j].ntr = ntr;
        p = h->_base+(h->rtail%h->wrap)*h->trln;
        t2sort_aio_write(&h->xque[j].aio, h->fd, p, 
                ntr*h->trln, h->rtail*h->trln);
        h->rtail += ntr;
        h->xhead++;
    }
    free(key);
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    h->rhead += h->rdfly;
    if(h->rhead-h->rtail>=h->bntr)   //delayed prev flush
        t2sort_write_block(h, h->bntr); 

    //do not cross the block and memory boundary!
    *ntr = ring_wrap(h->rhead, (*ntr), h->wrap);
    *ntr = MIN((*ntr), h->rtail+h->bntr-h->rhead);

    //wait all to satisfy *ntr since user requested
    while(h->rdone+h->wrap<h->rhead+(*ntr)) {  //must wait
        assert(h->xtail<h->xhead);
        int x=h->xtail%h->nxque;
        t2sort_aio_wait(&h->xque[x].aio, 1);
        h->rdone+=h->xque[x].ntr;
        h->xtail++;
    }
    void *praw = h->_base+(h->rhead%h->wrap)*h->trln;
    h->rdfly = *ntr;
    return praw;
}
/**
 *
 * */
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
