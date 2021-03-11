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
    int part1 = ring_wrap(h->rtail, nsort, h->nwrap);
    pkey = malloc(nsort*h->klen);
    buff = h->_base+(h->rtail%h->nwrap)*h->trlen;
    h->func_cpy_key(buff, h->trlen, part1, h->kdef, pkey);
    if(part1<nsort)
        h->func_cpy_key(h->_base, h->trlen, nsort-part1, 
                h->kdef, pkey+part1*h->klen);
    return pkey;
}

static void sort_one_block(t2sort_t *h, void *pkey, int nkey) 
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

/**
 * DO not use the pile concept!
 * 1. rdone, traces already on disk, aio_wait of write finish
 *       move forward by call aio_wait
 * 2. rtail<-rdone,  aio_write issued but not waited yet.
 * 3. rhead<-rtail, where writeraw API append new data!
 * */
static void 
t2sort_write_block(t2sort_t *h, int nsort)
{
    printf("%s: nsort=%d nwrap=%ld\n", __func__, nsort, h->nwrap);
    fflush(0);
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
        h->xque[j].aio = calloc(1, sizeof(t2sort_aio_t));
        h->xque[j].ntr = ntr;
        p = h->_base+(h->rtail%h->nwrap)*h->trlen;
        t2sort_aio_write(h->xque[j].aio, h->fd, p, 
                ntr*h->trlen, h->rtail*h->trlen);
        h->rtail += ntr;
        printf("%s:  xhead=%d ntr=%d\n", __func__, h->xhead, 
                h->xque[j].ntr); fflush(0);
        h->xhead++;
    }
    free(key);
}

// from rtail to rhead is in buffer
// from rdone to rtail is aio_write submited, not finished
// from 0 to rdone is on disk!
void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    h->rhead += h->rdfly;       //TODO: change to nfly
    printf("%s: h->rhead=%8ld tail=%8ld\n", __func__, h->rhead,
            h->rtail); fflush(0);
    if(h->rhead-h->rtail>=h->bntr) {   //delayed prev flush
        t2sort_write_block(h, h->bntr); 
    } 
    void *praw;
    *ntr = ring_wrap(h->rhead, (*ntr), h->nwrap);
    if(h->rslot<(*ntr) && h->rtail>h->rdone) {
        assert(h->xtail<h->xhead);
        int j=h->xtail%h->nxque;
        printf("%s: xtail=%d ntr=%d\n", __func__,  h->xtail, 
                    h->xque[j].ntr); fflush(0);
        t2sort_aio_wait(h->xque[j].aio, 1);
        free(h->xque[j].aio);
        h->rslot+=h->xque[j].ntr;
        h->rdone+=h->xque[j].ntr;
        h->xtail++;
    }
    *ntr = MIN(*ntr, h->rslot);
    praw = h->_base+(h->rhead%h->nwrap)*h->trlen;
    h->rdfly = *ntr;
    h->rslot -= h->rdfly;   //mark in use!
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
        memcpy(praw, psrc, h->trlen*nput);
        left -= nput;
        psrc += nput*h->trlen;
    };
    return (ntr-left);
}

#endif
