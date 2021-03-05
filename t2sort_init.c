
#define PAGE_SIZE 4096
/**
 * pile size aligned at Page size (4K)
 * */
int t2sort_pilesize(int bsize, int trlen, int wioq)
{
    size_t p_ntr, psize;    //number of trace per pile
    p_ntr = floor((bsize*1024L*1024L)/((wioq+1.0f)*trlen));
    psize = PAGE_SIZE*(floor(p_ntr*trlen/PAGE_SIZE)+2);
    return psize;
}

int t2sort_pile_alloc(t2sort_t *h, int bsize, int trlen, int wioq)
{
    h->npile = wioq+1;
    h->pile  = aligned_alloc(PAGE_SIZE, h->npile*sizeof(pile_t));
    memset(h->pile, 0, h->npile*sizeof(pile_t));

    int pilesize;
    h->wpntr = floor((bsize*1024L*1024L)/(h->npile*trlen));
    pilesize = PAGE_SIZE*(floor(h->wpntr*trlen/PAGE_SIZE)+2);
    h->_base = malloc(pilesize*h->npile);

    //AIO write use p_disk, write d_size bytes
    //data copy @ p and write pntr*trlen bytes
    /*
    h->pile[0].p_disk = h->pile[0].p = h->_base;
    h->pile[0].rbyte  = h->wpntr*h->trlen%PAGE_SIZE;
    h->pile[0].d_size = h->wpntr*h->trlen-h->pile[0].rbyte;
    for(int i=1; i<h->npile; i++) {
        h->pile[i].p_disk = h->pile[i-1].p_disk+pilesize;
        h->pile[i].p = h->pile[i].p_disk+h->pile[i-1].rbyte;
        h->pile[i].rbyte = 0;
    } */
    return 0;
}

/**
 * Add DIO flag later after handling alignment issue
 * */
static void
t2sort_init_scratch(t2sort_t *h)
{
    char scratchname[]="delete_XXXXXX";
    mktemp(scratchname);
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
    t2sort_init_scratch(h);
    //t2sort_init_wpile();
    return (t2sort_h)h;
}
