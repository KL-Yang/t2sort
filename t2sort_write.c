#ifndef C_T2SORT_WRITE_T2SORT
#define C_T2SORT_WRITE_T2SORT
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
    int ninst; void *key; void **ptr;
    //1.sort the block key and data
    key = block_keys_list(h, tail, &ninst);
    ptr = malloc(ninst*sizeof(void*));
    for(int i=0; i<ninst; i++) {
        ptr[i] = ((t2sort_pay_t*)(key+i*h->klen))->ptr;
        ((t2sort_pay_t*)(key+i*h->klen))->idx = i;
    }
    qsort(key, ninst, h->klen, h->func_cmp_key);

    int * map = malloc(ninst*sizeof(int));
    void *tmp = malloc(h->trlen);
    for(int i=0; i<ninst; i++) {
        map[i] = ((t2sort_pay_t*)(key+i*h->klen))->idx;
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.blk = h->block;
        ((t2sort_pay_t*)(key+i*h->klen))->bpi.idx = i;
    }
    write(h->fd_keys, key, ninst*h->klen);
    t2sort_map_sort(ptr, ninst, map, h->trlen, tmp);
    //t2sort_map_sort2(ptr, ninst, map, h->trlen);
    free(tmp);
    free(map);
    free(ptr);
    free(key);
    //2.write each pile on disk
    block_pile_write(h, tail);
    h->block++;
}

//reuse the pile struct for new block, need reset
void t2sort_wpile_reset(pile_t *p)
{
    p->ntr = 0;
    p->p = p->base;
    //p->ri  = 0;
    //p->p   = p->base+p->prev->ri;
}

void * t2sort_writeraw(t2sort_h h, int *ntr)
{
    if(h->pile->ntr==h->wpntr) {    //delayed prev flush
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
    *ntr = MIN(*ntr, h->wpntr-h->pile->ntr);
    h->pile->ntr += (*ntr);
    return praw;
}

/**
 *
 * */
int t2sort_write(t2sort_h h, const void *p, int ntr)
{
    //dbg_keys_print(p, ntr, h->trlen, h->kdef[0].offset,
    //        h->kdef[1].offset);

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
