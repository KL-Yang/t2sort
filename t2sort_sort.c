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

    //dbg_blocks_check(h);
    printf("checked!, nkey=%ld\n", h->nkey); fflush(0);

    //3. read and sort all keys
    void *key = malloc(h->nkey*h->klen);
    pread(h->fd_keys, key, h->nkey*h->klen, 0);
    qsort(key, h->nkey, h->klen, h->func_cmp_key);
    //4. clear and rebuild read queue!
    h->wait.prev = h->wait.next = &h->wait;
    h->read.prev = h->read.next = &h->read;
    h->DONe.prev = h->DONe.next = &h->DONe;

    h->_rblk = calloc(h->nblk, sizeof(t2_blk_t));
    for(int i=0; i<h->nblk; i++) 
        h->_rblk[i].page = aligned_alloc(PAGE_SIZE, PAGE_SIZE);
    h->_wrap = (h->bntr+h->pntr)*h->trln;
    h->_xque = t2_list_rque2(&h->read, key, h->nkey, h->klen, 
            h->bntr, h->nblk, h->pntr, h->trln);
    //int *nn = calloc(h->nblk*h->nblk, sizeof(int));
    //t2_scan(key, h->nkey, h->klen, h->bntr, h->nblk, nn);
    //t2_rque(&h->read, nn, 
    //free(nn);
    //debug
    int xsum=0; 
    t2_que_t *xhead = h->read.next;
    while(xhead!=&h->read) {
        xsum += xhead->ntr;
        xhead = xhead->next;
    }
    printf("%s:total rque ntr=%d\n", __func__, xsum);
    free(key);

    t2_print_queu(&h->read, h->trln, h->wrap);
    //abort();

    //Initiate for t2sort_read()
    h->head = h->tail = h->done = h->nfly = 0;
    //try_issue_read(h, &h->read);
    t2_read_submit(h, &h->read);

    return 0;
}
#endif
