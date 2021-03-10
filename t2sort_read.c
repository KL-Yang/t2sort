#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

int t2sort_rblock_process(t2sort_t *h)
{
    int rbntr=0, bntr=h->bntr;
    t2sort_que_t *head=h->rque;
    while(rbntr<bntr && head!=NULL) {
        void *buff = h->_base+rbntr*h->trlen;
        size_t count = head->ntr*h->trlen;
        off_t offset = head->seek*h->trlen;
        pread(h->fd, buff, count, offset);
        rbntr += head->ntr;
        head = head->next;
    } //TODO: release those read queue memory!!!
    h->rque = head;
    if(head!=NULL)
        assert(rbntr==bntr);
    if(rbntr==0)
        return 0;

    void *key = malloc(rbntr*h->klen);
    h->func_cpy_key(h->_base, h->trlen, rbntr, h->kdef, key);
    void **ptr = malloc(rbntr*sizeof(void*));
    for(int i=0; i<rbntr; i++) {
        ptr[i] = ((t2sort_pay_t*)(key+i*h->klen))->ptr;
        ((t2sort_pay_t*)(key+i*h->klen))->idx = i;
    }
    qsort(key, rbntr, h->klen, h->func_cmp_key);

    int *map  = malloc(rbntr*sizeof(int));
    void *tmp = malloc(h->trlen);
    for(int i=0; i<rbntr; i++)
        map[i] = ((t2sort_pay_t*)(key+i*h->klen))->idx;
    t2sort_map_sort(ptr, rbntr, map, h->trlen, tmp);

    dbg_ablock_check(h, h->_base, rbntr);

    free(tmp);
    free(map);
    free(ptr);
    free(key);
    printf("%s: rbntr=%d bntr=%d\n", __func__, rbntr, bntr);
    return rbntr;
}

//in sort_reset, prepare the first block
//h->rinst = h->pntr*h->wioq;
const void * t2sort_readraw(t2sort_t *h, int *ntr)
{
    if((h->rdone+=h->rdfly)==h->nsort) {
        int rbntr = t2sort_rblock_process(h);
        if(rbntr==0) {
            *ntr = 0;
            return NULL;
        }
        h->nsort += rbntr;
    }
    int rdone = h->rdone%h->nwrap;
    int nsort = h->nsort%h->nwrap;
    void *praw = h->_base+rdone*h->trlen;
    if(nsort>rdone)
        *ntr = MIN(*ntr, nsort-rdone);
    else //wrapped
        *ntr = MIN(*ntr, h->nwrap-rdone);
    h->rdfly = *ntr;
    printf("%s: =%d\n", __func__, *ntr);
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
