#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

//build the queue, break all read large than pntr!
static t2_que_t *
t2_list_rque(t2_que_t *head, void *pkey, int nkey, 
        int klen, int bntr, int nblk, int pntr)
{
    nblk = ceilf(nkey*1.0f/bntr);
    int f[nblk], n[nblk], x=0; t2_que_t *xque;
    xque = calloc(2*nblk*nblk, sizeof(t2_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0, xntr; k<nkey; k+=bntr) {
        xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, pkey+=klen)
            n[((t2_pay_t*)pkey)->bpi.blk]++;
        for(int i=0; i<nblk; i++) {
            while(n[i]!=0) {
                xque[x].ntr  = MIN(n[i], pntr);
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                xque[x].id   = x;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                x++;
            }
        }
    } assert(x<=2*nblk*nblk);
    return realloc(xque, x*sizeof(t2_que_t));
}

int t2sort_sort(t2sort_h h)
{
    //1. flush piles of the last block
    if((h->head+=h->nfly)>h->tail)
        t2_flush_block(h, h->head-h->tail);
    t2_que_t *xque = xque_deque(&h->wait);
    while(xque!=&h->wait) {
        t2sort_aio_wait(&xque->aio, 1);
        h->done+=xque->ntr;
        xque = xque_deque(&h->wait);
    };
    free(h->_xque);
    if(h->flag & T2SORT_DIO) {
        close(h->fd);   //reopen without O_DIRECT for now!
        h->fd = open(h->fd_name, O_RDWR|O_CREAT,
                S_IRWXU|S_IRWXG|S_IRWXO);
    }
    h->nkey = h->head;

    dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);

    //3. read and sort all keys
    void *key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. clear and rebuild read queue!
    h->wait.prev = h->wait.next = &h->wait;
    h->read.prev = h->read.next = &h->read;
    h->_xque = t2_list_rque(&h->read, key, h->nkey, h->klen, 
            h->bntr, h->nblk, h->pntr);
    //debug
    int xsum=0; 
    t2_que_t *xhead = h->read.next;
    while(xhead!=&h->read) {
        xsum += xhead->ntr;
        xhead = xhead->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    free(key);
    //abort();

    //Initiate for t2sort_read()
    h->head = h->tail = h->done = h->nfly = 0;

    return 0;
}
#endif
