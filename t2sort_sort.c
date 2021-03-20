#ifndef C_T2SORT_SORT_T2SORT
#define C_T2SORT_SORT_T2SORT

int t2sort_sort(t2sort_h h)
{
    //1. flush piles of the last block
    if((h->head+=h->nfly)>h->tail)
        t2_flush_block(h, h->head-h->tail);
    t2_que_t *xque = xque_deque(&h->wait);
    while(xque!=&h->wait) {
        t2_aio_wait(&xque->aio, 1);
        h->disk+=xque->ntr;
        xque = xque_deque(&h->wait);
    };
    free(h->_xque);
    h->nkey = h->head;

    //dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);

    //3. read and sort all keys
    void *key = malloc(h->nkey*h->klen);
    int *bbnn = calloc(h->nblk*h->nblk, sizeof(int));
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    t2_scan(key, h->nkey, h->klen, h->bntr, h->nblk, bbnn);
    free(key);

    //4. clear and rebuild read queue!
    h->wait.prev = h->wait.next = &h->wait;
    h->pool.prev = h->pool.next = &h->pool;
    h->done.prev = h->done.next = &h->done;

    h->_rblk = calloc(h->nblk, sizeof(t2_blk_t));
    for(int i=0; i<h->nblk; i++) 
        h->_rblk[i].page = aligned_alloc(PAGE_SIZE, PAGE_SIZE);
    h->_wrap = (h->bntr+h->pntr)*h->trln;

    int nque = t2_lque(h->_base, bbnn, h->nblk, h->bntr, 
            h->trln, h->pntr, h->_wrap);
    free(bbnn);
    h->_xque = t2_rque(&h->pool, h->_base, nque); 

    //dbg_rque_print(&h->pool, h->trln, h->_wrap);

    h->nfly = 0;
    t2_read_submit(h, &h->pool);

    return 0;
}
#endif
