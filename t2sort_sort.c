#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

static t2sort_que_t *
rque_new(t2sort_que_t *tail, int ntr, int dblk, int seek)
{
    if(ntr==0)  //do nothing
        return tail;

    t2sort_que_t *xque = calloc(1, sizeof(t2sort_que_t));
    xque->ntr  = ntr;
    xque->blk  = dblk;
    xque->seek = seek;
    tail->next = xque;
    xque->id   = tail->id+1;
    return xque;
}

/**
 * @brief Split the Read queue item if necessary
 * @param x : detached item, if x->next!=NULL, two linked item!
 * */
static t2sort_que_t *rque_split(t2sort_t *h, t2sort_que_t *x) 
{
    if((h->rhead%h->nwrap+x->ntr)<=h->nwrap)
        return x;
    int ntrx = x->ntr-(h->rhead+x->ntr)%h->nwrap;
    int ntry = x->ntr-ntrx;
    printf("  %s: %d -> %d+%d\n", __func__, x->ntr, ntrx, ntry); fflush(0);
    x->ntr = ntrx;      //first part
    t2sort_que_t *y;    //second part
    y = rque_new(x, ntry, x->blk, x->seek+ntrx);
    x->flag |= T2SORT_RQUE_SPLIT;
    y->flag |= T2SORT_RQUE_SPLIT;
    return x;
}

//each time read h->pntr*h->wioq
static t2sort_que_t *
t2sort_sort_rque(void *pkey, int nkey, int klen, int bntr)
{
    t2sort_pay_t *payl=pkey;
    t2sort_que_t *head, *tail;
    int nblk = ceilf(nkey*1.0f/bntr), f[nblk], n[nblk];

    tail = head = calloc(1, sizeof(t2sort_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0; k<nkey; k+=bntr) {
        int xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, payl=(void*)payl+klen)
            n[payl->bpi.blk]++;

        for(int i=0; i<nblk; i++) {
            tail = rque_new(tail, n[i], i, i*bntr+f[i]);
            f[i] += n[i];
        }
    }
    tail = head;
    head = head->next;
    free(tail);
    return head;
}

int t2sort_sort(t2sort_h h)
{
    //flush piles of the last block
    h->rhead += h->rdfly;
    if(h->rhead>h->rtail) {
        t2sort_write_block(h, h->rhead-h->rtail);
    }
    for(;h->xtail<h->xhead; h->xtail++) {
        int j=h->xtail%h->nxque;
        t2sort_aio_wait(h->xque[j].aio, 1);
        free(h->xque[j].aio);
        h->rdone+=h->xque[j].ntr;
    }
    //read keys to the buffer for sorting!
    //2. read all keys in memory, may exceed bsize.
    h->nkey = h->rhead;
    dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);
    //abort();

    void *key;
    key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    //3. sort all keys
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. build read queue!
    h->read = t2sort_sort_rque(key, h->nkey, h->klen, 
                h->pntr*h->wioq);
    //debug
    int xsum=0; t2sort_que_t *xtail = h->read;
    while(xtail!=NULL) {
        xsum += xtail->ntr;
        xtail = xtail->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    free(key);

    //1. free wpile buffers
    free(h->_base);

    //for reference implementation
    h->nwrap = h->pntr*(h->wioq+1);
    h->_base = calloc(h->nwrap, h->trlen);

    //read for a block
    h->rslot = h->nwrap;    //all buffer is empty
    h->rhead = 0;
    h->rtail = 0;
    h->rdone = 0;

    return 0;
}

#endif
