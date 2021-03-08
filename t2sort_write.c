#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT

#define MIN(a,b)    ((a)>(b)?(b):(a))

/**
 * Return a list of all traces in the block for sort
 * This is no need, we need pointer as key's payload
 * */
static void *
block_keys_list(t2sort_h h, pile_t *tail, int *ntr)
{
    pile_t *head=tail; int bntr=head->ntr, nkey=0;
    while(head->bpid!=0) {  //find block head
        bntr += head->ntr;
        head  = head->prev;
    }; //assemble from head in storage order
    void *base = malloc(bntr*h->klen), *pkey=base;
    while(nkey<bntr) {
        h->func_cpy_key(head->p, h->trlen, head->ntr, h->key, pkey);
        nkey+=head->ntr;
        pkey+=head->ntr*h->klen;
        head=head->next;
    };
    *ntr = bntr; assert(nkey==bntr);
    return base;
}

static void
t2sort_wblock_process(t2sort_t *h, pile_t *tail, int trlen)
{
    int ninst; void *key; void **ptr;
    //1.sort the block key and data
    key = block_keys_list(h, tail, &ninst);
    ptr = malloc(ninst*sizeof(void*));
    for(int i=0; i<ninst; i++) {
        ptr[i] = ((void**)(key+i*h->klen))[0];
        ((int64_t*)(key+i*h->klen))[0] = i;
    }
    qsort(key, ninst, h->klen, h->func_cmp_key);

    //2.write each pile on disk
    free(key);
}

//reuse the pile struct for new block, need reset
void t2sort_wpile_reset(pile_t *p)
{
    p->ntr = 0;
    p->ri  = 0;
    p->p   = p->base+p->prev->ri;
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    if(h->pile->ntr==h->wpntr) {    //delayed prev flush
        h->wpile++;
        h->pile->ri = (h->pile->ntr*h->trlen+
                       h->pile->prev->ri)%PAGE_SIZE;
        int newblock=(h->wpile%h->wioq==0);
        if(newblock)
            t2sort_wblock_process(h->pile, h->wioq);

        h->pile = h->pile->next;
        if(h->pile->ntr!=0) {
            t2sort_aio_wait(&h->pile->cb, 1);
            t2sort_wpile_reset();
            h->pile->ntr=0;
            //reset the h->pile->p also!
        }

        h->pile->bpid = h->pile->prev->bpid+1;
        if(newblock)
            h->pile->bpid = 0;
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
