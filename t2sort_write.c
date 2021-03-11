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
 * Return a list of all traces in the block for sort
 * This is no need, we need pointer as key's payload
 * */
static void *
block_keys_list(t2sort_h h, pile_t *tail, int *ntr)
{
    pile_t *head=tail; *ntr=0;
    for(int i=tail->bpid; i>=0; i--, head=head->prev)
        *ntr += head->ntr;
    head = head->next;  //reverse the over-run
    //assemble from head in storage order
    void *base, *pkey;
    base = pkey = malloc((*ntr)*h->klen);
    for(int i=0; i<=tail->bpid; i++, head=head->next) {
        h->func_cpy_key(head->p, h->trlen, head->ntr, h->kdef, pkey);
        pkey+=head->ntr*h->klen;
    }
    return base;
}

static void
block_pile_write(t2sort_t *h, pile_t *tail)
{
    pile_t *head=tail; int bntr=head->ntr, nkey=0;
    while(head->bpid!=0) {  //find block head
        bntr += head->ntr;
        head  = head->prev;
    }; //assemble from head in storage order
    while(nkey<bntr) {
        t2sort_aio_write(&head->cb, h->fd, head->p, 
            head->ntr*h->trlen, h->nkey*h->trlen);
        nkey+=head->ntr;
        h->nkey+=head->ntr;
        head=head->next;
    }
    return;
}

static void 
t2sort_wblock_process(t2sort_t *h, pile_t *tail)
{
    printf("%s:\n", __func__);
    int ninst; void *key;
    //1.sort the block key and data
    key = block_keys_list(h, tail, &ninst);
    sort_one_block(h, key, ninst);
    for(int i=0; i<ninst; i++) {
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.blk = h->nblk;
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.idx = i;
    }
    write(h->fd_keys, key, ninst*h->klen);
    free(key);
    //2.write each pile on disk
    block_pile_write(h, tail);
    h->nblk++;
}

//reuse the pile struct for new block, need reset
static void t2sort_wpile_reset(pile_t *p)
{
    p->ntr = 0;
    p->p = p->base;
    //p->ri  = 0;
    //p->p   = p->base+p->prev->ri;
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    if(h->pile->ntr==h->pntr) {    //delayed prev flush
        h->pile->next->bpid = h->pile->bpid+1;
        if((++h->wpile)%h->wioq==0) {
            t2sort_wblock_process(h, h->pile);
            h->pile->next->bpid = 0;
        }

        if(h->pile->next->ntr!=0)
            t2sort_aio_wait(&h->pile->next->cb, 1);
        t2sort_wpile_reset(h->pile->next);
        h->pile = h->pile->next;
    } //as later as possible to let user operate on praw

    void *praw = h->pile->p + h->pile->ntr*h->trlen;
    *ntr = MIN(*ntr, h->pntr-h->pile->ntr);
    h->pile->ntr += (*ntr);
    return praw;
}

/**
 * DO not use the pile concept!
 * 1. rdone, traces already on disk, aio_wait of write finish
 *       move forward by call aio_wait
 * 2. rtail<-rdone,  aio_write issued but not waited yet.
 * 3. rhead<-rtail, where writeraw API append new data!
 * */
//#define XXXXXXXXX
#ifdef XXXXXXXXX
static void 
t2sort_write_block(t2sort_t *h, int nsort)
{
    void *key, *p;
    key = t2sort_list_key(h, nsort);
    sort_one_block(h, key, nsort);
    for(int i=0; i<nsort; i++) {
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.blk = h->nblk;
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.idx = i;
    }
    write(h->fd_keys, key, nsort*h->klen);
    //use ring buffer to handle the write queue!!!
    for(int i=0, j; i<h->wioq; i++) {
        assert(h->xhead-h->xtail<h->nxque);
        j = h->xhead%h->nxque;
        h->xque[j].aio = calloc(1, sizeof(t2sort_aio_t));
        p = h->_base+(h->rtail%h->nwrap)*h->trlen;
        t2sort_aio_write(h->xque[j].aio, h->fd, p, 
                h->pntr*h->trlen, h->rtail*h->trlen);
        h->xhead++;
        h->rtail += h->pntr;
    }
    free(key);
}

void * t2sort_writeraw2(t2sort_h h, int *ntr)
{
    h->rhead += h->rdfly;       //TODO: change to nfly
    if(h->rhead-h->rtail>=h->bntr) {   //delayed prev flush
        t2sort_write_block(h, h->bntr); 
        h->rtail += h->bntr;
    } 
    void *praw;
    *ntr = ring_wrap(h->rhead, (*ntr), h->nwrap);
    if(h->rslot<(*ntr) && (*ntr)<1000) {
        int j=h->xtail%h->nxque;
        t2sort_aio_wait(h->xque[j].aio, 1);
        free(h->xque[j].aio);
        h->xtail++;
    }
    *ntr = MIN(*ntr, h->rslot);
    praw = h->_base+(h->rhead%h->nwrap)*h->trlen;
    h->rdfly = *ntr;
    h->rslot -= h->rdfly;   //mark in use!
    return praw;
}
#endif
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
