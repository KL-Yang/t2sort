#ifndef C_T2SORT_DEBUG_T2SORT
#define C_T2SORT_DEBUG_T2SORT

void dbg_ablock_check()
{
}

void dbg_blocks_check(t2sort_t *h)
{
    int bntr = h->wpntr*h->wioq;
    void *buff = malloc(bntr*h->trlen);
    void *pkey = malloc(bntr*h->klen);
    for(int64_t i=0, n; i<h->winst; i+=bntr) {
        n = MIN(bntr, h->winst-i);
        pread(h->fd, buff, n*h->trlen, i*h->trlen);
        h->func_cpy_key(buff, h->trlen, n, h->kdef, pkey);
        dbg_ablock_check();
    }
    free(buff);
    free(pkey);
}

void dbg_print_iikey()
{
}

#endif
