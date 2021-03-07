
#define PAGE_SIZE 4096

int t2sort_init_wpile(t2sort_t *h, int bsize, int trlen, int wioq)
{
    int pilesize;
    h->wpntr = floor((bsize*1024L*1024L)/((wioq+1)*trlen));
    pilesize = PAGE_SIZE*(floor(h->wpntr*trlen/PAGE_SIZE)+2);
    h->_base = malloc(pilesize*(wioq+1));

    //make write pile as double linked list
    h->pile = calloc(wioq+1, sizeof(pile_t));
    for(int i=0; i<wioq+1; i++) {
        h->pile[i].pid  = i;
        h->pile[i].next = &h->pile[(i+1)%(wioq+1)];
        h->pile[i].prev = &h->pile[(i+wioq)%(wioq+1)];
        h->pile[i].base = h->_base+i*pilesize;
    }
    return 0;
}

/**
 * Add DIO flag later after handling alignment issue
 * */
static void
t2sort_init_scratch(t2sort_t *h)
{
    char scratchname[]="delete_XXXXXX";
    mkstemp(scratchname);
    printf("%s: open scratch (%s)\n", __func__, scratchname);
    h->fd = open(scratchname, O_RDWR|O_CREAT, 
                    S_IRWXU|S_IRWXG|S_IRWXO);
}

t2sort_h
t2sort_init(int trlen, int nkey, const t2sort_key_def_t *keys, 
    int bsize, int wioq, int flag)
{
    t2sort_t *h = calloc(1, sizeof(t2sort_t));
    h->bsize = bsize;
    h->trlen = trlen;
    h->key   = calloc(nkey, sizeof(t2sort_key_def_t));
    memcpy(h->key, keys, nkey*sizeof(t2sort_key_def_t));
    h->nkey  = nkey;
    h->wioq  = wioq;
    h->flag  = flag;
    for(int i=0; i<nkey; i++)
        h->klen += t2sort_type_size[keys[i].type];
    t2sort_init_scratch(h);
    t2sort_init_wpile(h, bsize, trlen, wioq);
    h->func_cmp_key = t2sort_getcmp(nkey, keys);
    h->func_cpy_key = t2sort_getcpy(nkey, keys);
    return (t2sort_h)h;
}
