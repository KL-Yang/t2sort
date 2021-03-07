#ifndef C_T2SORT_DESTROY_T2SORT
#define C_T2SORT_DESTROY_T2SORT
int t2sort_destroy(t2sort_h h)
{
    t2sort_t *t = (t2sort_t*)h;
    close(t->fd);
    free(t->key);
    free(t);
    return 0;
}
#endif