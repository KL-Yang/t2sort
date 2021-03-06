#ifndef C_T2SORT_READ_T2SORT
#define C_T2SORT_READ_T2SORT

const void * t2sort_readraw(t2sort_h h, int *ntr)
{
    return NULL;
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
