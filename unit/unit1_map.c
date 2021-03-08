#include "../t2sort_i.h"
#include "../gentype_gen.h"
#include "../gentype_gen.c"
#include "common1.c"
#include "../t2sort_map.c"

/**
 * @brief Out Of Place map to debug the inplace map
 * @param n : number of trace
 * @param s : size of a trace
 * @param x : input
 * @param m : map function
 * @param y : output y=m(x)
 * */
void oop_map(int n, int s, const void **x, int *m, void **y)
{
    for(int i=0; i<n; i++)
        memcpy(y[i], x[m[i]], s);
}

/**
 * test n size
 * n is number of values
 * size is payload size, in number of int
 * */
int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("Usage: %s nkey size\n", argv[0]);
        exit(1);
    }
    int nkey, size;
    nkey = atoi(argv[1]);
    size = atoi(argv[2]);
    srandom(1234);

    t2sort_key_def_t key[] = {
        {.offset=0, .type=T2SORT_INT32_T, .order=1},
        {.offset=4, .type=T2SORT_INT32_T, .order=1} };

    //Generate data
    void *p = calloc(nkey, size);
    gen_data(p, nkey, size, key[0].offset, 1, 50, 
        key[1].offset, 1, 200);

    //extrace keys
    t2sort_int32_t_int32_t_t *k;
    k = calloc(nkey, sizeof(t2sort_int32_t_int32_t_t));
    int ibyte[2] = {key[0].offset, key[1].offset};
    cpy_int32_t_int32_t(p, size, nkey, ibyte, k);

    void **pp = calloc(nkey, sizeof(void*));
    for(int i=0; i<nkey; i++) {
        pp[i] = k[i].p;
        assert(pp[i]==p+i*size);
        k[i].i = i;
    }
    qsort(k, nkey, sizeof(t2sort_int32_t_int32_t_t),
            cmp_int32_t_int32_t);

    int *map = calloc(nkey, sizeof(int));
    for(int i=0; i<nkey; i++)
        map[i] = k[i].i;
    free(k);

    void *x = calloc(nkey, size);
    void **xx = calloc(nkey, sizeof(void*));
    for(int i=0; i<nkey; i++)
        xx[i] = x+i*size;

    //oop_map(nkey, size, pp, map, xx);
    void *swap = malloc(size);
    t2sort_remap_pt(pp, nkey, map, size, swap);
    memcpy(x, p, nkey*size);
    free(swap);

    free(map);
    free(pp);
    free(xx);
    free(p);
    
    keys_print(x, nkey, size, key[0].offset, key[1].offset);
    keys_valid(x, nkey, size, key[0].offset, key[1].offset);
    data_valid(x, nkey, size, key[0].offset, key[1].offset);

    free(x);
    return 0;
}
