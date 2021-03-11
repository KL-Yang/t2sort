#ifndef C_T2SORT_INIT_T2SORT
#define C_T2SORT_INIT_T2SORT

#define PAGE_SIZE 4096

static void t2sort_free_wpile(pile_t *p)
{
    while(p->pid!=0) 
        p=p->next;
    free(p);
}

static int t2sort_init_wpile(t2sort_t *h, int bsize, int trlen, int wioq)
{
    int pilesize;
    h->pntr = floor((bsize*1024L*1024L)/((wioq+1)*trlen));
    h->bntr = h->pntr*wioq;
    printf("%s: bsize=%d pntr=%ld wioq=%d\n", 
            __func__, bsize, h->pntr, wioq);
    pilesize = PAGE_SIZE*(floor(h->pntr*trlen/PAGE_SIZE)+2);
    h->nwrap = h->pntr*(wioq+1);
    h->rslot = h->nwrap;
    h->_base = malloc(pilesize*(wioq+1));

    //make write pile as double linked list
    h->pile = calloc(wioq+1, sizeof(pile_t));
    for(int i=0; i<wioq+1; i++) {
        h->pile[i].pid  = i;
        h->pile[i].next = &h->pile[(i+1)%(wioq+1)];
        h->pile[i].prev = &h->pile[(i+wioq)%(wioq+1)];
        h->pile[i].base = h->_base+i*pilesize;
    }
    h->pile->p = h->pile->base; //first pile
    return 0;
}

/**
 * Add DIO flag later after handling alignment issue
 * */
static void
t2sort_init_scratch(t2sort_t *h)
{
    char scratchname_d[]="delete_d_XXXXXX";
    mkstemp(scratchname_d);
    char scratchname_k[]="delete_k_XXXXXX";
    mkstemp(scratchname_k);
    printf("%s: open scratch (dat=%s, key=%s)\n", __func__, 
            scratchname_d, scratchname_k);
    h->fd = open(scratchname_d, O_RDWR|O_CREAT, 
                    S_IRWXU|S_IRWXG|S_IRWXO);
    h->fd_keys = open(scratchname_k, O_RDWR|O_CREAT, 
                    S_IRWXU|S_IRWXG|S_IRWXO);
}

t2sort_h
t2sort_init(int trlen, int ndef, const t2sort_key_def_t *kdef, 
    int bsize, int wioq, int flag)
{
    t2sort_t *h = calloc(1, sizeof(t2sort_t));
    h->bsize = bsize;
    h->trlen = trlen;
    h->kdef  = calloc(ndef, sizeof(t2sort_key_def_t));
    memcpy(h->kdef, kdef, ndef*sizeof(t2sort_key_def_t));
    h->ndef  = ndef;
    h->wioq  = wioq;
    h->flag  = flag;
    h->klen  = t2sort_key_size(ndef, kdef);
    t2sort_init_scratch(h);
    t2sort_init_wpile(h, bsize, trlen, wioq);
    h->func_cmp_key = t2sort_getcmp(ndef, kdef);
    h->func_cpy_key = t2sort_getcpy(ndef, kdef);
    h->wait = &h->wait_head;

    //1 for write key, 1 for extra
    h->nxque = wioq+2;
    h->xque  = calloc(h->nxque, sizeof(t2sort_que_t));
    h->xhead = h->xtail = 0;

    return (t2sort_h)h;
}
#endif
