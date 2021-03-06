#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT

#define MIN(a,b)    ((a)>(b)?(b):(a))
/**
 * @brief Get list of piles in current block
 * */
static pile_t ** block_pile_list(pile_t *pile, int n)
{
    pile_t **p = calloc(n, sizeof(pile_t*));
    for(int i=n-1; i>=0; i--) {
        assert(pile->bpid==i);
        p[i] = pile; 
        pile = pile->prev;
    }
    return p;
}

static void
t2sort_wblock_process(pile_t *pile, int n)
{
    pile_t **p = block_pile_list(pile, n);

    //1.sort the block
    //2.write each pile on disk
    free(p);
}

static void t2sort_wpile_wait(pile_t *pile)
{
    t2sort_aio_wait(&pile->cb, 1);
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    int newblock=0;
    if(h->pile->ntr==h->wpntr) {    //delayed prev flush
        if((++h->wpile)%h->wioq==0) {
            t2sort_wblock_process(h->pile, h->wioq);
            newblock=1;
        }
        t2sort_wpile_wait(h->pile->next);
        h->pile = h->pile->next;
        h->pile->bpid = (newblock)?(0):(h->pile->prev->bpid+1);
    } //as later as possible to let user operate on praw

    void *praw = h->pile->p + h->pile->ntr*h->trlen;
    *ntr = MIN(*ntr, h->wpntr-h->pile->ntr);
    h->pile->ntr += (*ntr);
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
