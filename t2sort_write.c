#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    return NULL;
}
/**
 *
 * dump
 * copy buffer to the pile, pile align at 4K page.
 * (nice-1)*pile form one sorted block
 * memory is continous within one pile, each pile an aio handle
 *
 * because 4K alignment, size of each pile need to be carefully
 * computed? or 
 *
 * read to fill (nice-1)*pile
 * each sorted block may be read at most once, but may be split
 * if have to across pile.
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
