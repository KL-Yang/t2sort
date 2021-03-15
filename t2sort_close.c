#ifndef C_T2SORT_CLOSE_T2SORT
#define C_T2SORT_CLOSE_T2SORT
int t2sort_close(t2sort_h h)
{
    t2sort_t *t = (t2sort_t*)h;
    close(t->fd);
    close(t->fd_keys);
    free(t->kdef);
    free(t->_base);
    free(t->_xque);
    free(t->_pkey);
    free(t);
    return 0;
}
#endif
