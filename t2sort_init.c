#ifndef C_T2SORT_INIT_T2SORT
#define C_T2SORT_INIT_T2SORT

#define PAGE_SIZE 4096

/**
 * Add DIO flag later after handling alignment issue
 * */
static void t2sort_init_scratch(t2sort_t *h)
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
t2sort_init(int tlen, int ndef, const t2sort_key_def_t *kdef, 
    int bsiz, int wioq, int flag)
{
    t2sort_t *h = calloc(1, sizeof(t2sort_t));
    h->trln  = tlen;
    h->ndef  = ndef;
    h->kdef  = calloc(ndef, sizeof(t2sort_key_def_t));
    memcpy(h->kdef, kdef, ndef*sizeof(t2sort_key_def_t));

    h->pntr  = floor(bsiz*1024L*1024L/((wioq+1)*tlen));
    h->bntr  = h->pntr*wioq;
    h->nwrap = h->pntr*(wioq+1);
    h->_base = malloc(h->nwrap*tlen);
    printf("%s: bsiz=%dMB pntr=%ld wioq=%d\n", __func__, bsiz, h->pntr, wioq);

    h->wioq  = wioq;
    h->flag  = flag;
    h->klen  = t2sort_key_size(ndef, kdef);
    t2sort_init_scratch(h);
    h->func_cmp_key = t2sort_getcmp(ndef, kdef);
    h->func_cpy_key = t2sort_getcpy(ndef, kdef);
    h->wait2.prev = h->wait2.next = &h->wait2;
    h->read2.prev = h->read2.next = &h->read2;

    //1 for write key, 1 for extra
    h->nxque = wioq+2;
    h->xque  = calloc(h->nxque, sizeof(t2sort_que_t));
    h->xhead = h->xtail = 0;

    return (t2sort_h)h;
}
#endif
