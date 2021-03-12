#ifndef C_T2SORT_INIT_T2SORT
#define C_T2SORT_INIT_T2SORT

static void t2_factor(int a, int *f)
{
    while(a!=1) {
        for(int i=2, j=0; i<=a; i++)
            if(a%i==0) {
                a=a/i;
                f[j]=i;
                j++;
                break;
            }
    }
}

static int t2_multiple(int pagemask, int trln)
{
    int f[32], multiple=(1<<pagemask);
    for(int i=0; i<32; i++)
        f[i]=1;
    t2_factor(trln, f);
    for(int i=0, j=0; i<32; i++)
        if(f[i]==2 && j<pagemask) {
            f[i] = 1;
            j++;
        }
    for(int i=0; i<32; i++)
        multiple*=f[i];
    return multiple;
}

//add to tail
static void xque_enque(t2sort_que_t *head, t2sort_que_t *x)
{
    t2sort_que_t *tail = head->prev;
    tail->next = x; x->prev = tail;
    head->prev = x; x->next = head;
}
//remove from head
t2sort_que_t * xque_deque(t2sort_que_t *head)
{
    t2sort_que_t *item = head->next;
    head->next = item->next;    //note item may be head!
    return item;
}


static void t2_init_blk(t2sort_t *h, int bsiz, int wioq, int trln)
{
    int scale, xsize;
    xsize=t2_multiple(PAGE_MASK, trln);
    scale=nearbyint(bsiz*1024.0*1024.0/xsize/(1+wioq));
    scale=MAX(1, scale);
    h->pntr = scale*(xsize/trln);
    h->bntr = h->pntr*wioq;
}

/**
 * Add DIO flag later after handling alignment issue
 * */
static void t2_init_scratch(t2sort_t *h)
{
    strcpy(h->fd_name, "delete_d_XXXXXX");
    mkstemp(h->fd_name);
    char scratchname_k[]="delete_k_XXXXXX";
    mkstemp(scratchname_k);
    printf("%s: open scratch (dat=%s, key=%s)\n", __func__, 
            h->fd_name, scratchname_k);
    h->fd = open(h->fd_name, O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
    h->fd_keys = open(scratchname_k, O_RDWR|O_CREAT, 
                    S_IRWXU|S_IRWXG|S_IRWXO);
}

t2sort_h
t2sort_init(int tlen, int ndef, const t2sort_key_def_t *kdef, 
    int bsiz, int wioq, int flag)
{
    t2sort_t *h = calloc(1, sizeof(t2sort_t));
    h->trln = tlen;
    h->ndef = ndef;
    h->kdef = calloc(ndef, sizeof(t2sort_key_def_t));
    memcpy(h->kdef, kdef, ndef*sizeof(t2sort_key_def_t));

    t2_init_blk(h, bsiz, wioq, tlen);
    h->wrap = h->pntr*(wioq+1);
    h->_base = aligned_alloc(PAGE_SIZE, h->wrap*tlen);
    printf("%s: bsiz=%dMB pntr=%ld wioq=%d buff=%8.1fMB\n", 
        __func__, bsiz, h->pntr, wioq, 
        nearbyint((h->wrap*tlen)/1024.0/1024.0));

    h->wioq  = wioq;
    h->flag  = flag;
    h->klen  = t2sort_key_size(ndef, kdef);
    t2_init_scratch(h);
    h->func_cmp_key = t2sort_getcmp(ndef, kdef);
    h->func_cpy_key = t2sort_getcpy(ndef, kdef);

    h->wait.prev = h->wait.next = &h->wait;
    h->read.prev = h->read.next = &h->read;

    //1 for write key, 1 for extra
    h->nxque = wioq+2;
    h->xque  = calloc(h->nxque, sizeof(t2sort_que_t));
    h->xhead = h->xtail = 0;
    for(int i=0; i<h->nxque; i++) 
        xque_enque(&h->read, &h->xque[i]);

    return (t2sort_h)h;
}
#endif
