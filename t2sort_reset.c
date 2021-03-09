#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

int t2sort_reset(t2sort_h h)
{
    //flush piles of the last block
    if(h->pile->ntr!=0)
        t2sort_wblock_process(h, h->pile);
    //wait all piles write finishes
    pile_t *head=h->pile->next, *tail=head;
    do {
        t2sort_aio_wait(&tail->cb, 1);
        tail = tail->next;
    } while(tail!=head);
    //read keys to the buffer for sorting!
    //1. free wpile buffers
    free(h->_base);
    t2sort_free_wpile(h->pile);
    //2. read all keys in memory, may exceed bsize.
    void *key;
    key = malloc(h->winst*h->klen);
    //3. sort all keys
    //4. build read queue!
    //5. release the key memories.
    free(key);
    return 0;
}

#endif
