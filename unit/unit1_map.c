#include "../t2sort_i.h"
#include "gentype_gen.h"
#include "gentype_gen.c"
#include "../t2sort_debug.c"
#include "../t2sort_map_sort.c"

typedef t2sort_int32_t_int32_t_t t2ii_t;    //short name

static t2sort_key_def_t kdef[] = {
    {.offset=0, .type=T2SORT_INT32_T, .order=1},
    {.offset=4, .type=T2SORT_INT32_T, .order=1} };

static int cmp_trace(const void *p1, const void *p2)
{
    t2sort_int32_t_int32_t_t k1, k2;
    cpy_int32_t_int32_t((void*)p1, 0, 1, kdef, &k1);
    cpy_int32_t_int32_t((void*)p2, 0, 1, kdef, &k2);
    return cmp_int32_t_int32_t(&k1, &k2);
}

void unit1_test(int64_t ninst, int trlen, unsigned int seed)
{
    srandom(seed);
    void *t0 = calloc(ninst, trlen);
    void *t1 = calloc(ninst, trlen);
    dbg_gen_data(t0, ninst, trlen, kdef[0].offset, 1, 300, 
            kdef[1].offset, 1, 999);
    memcpy(t1, t0, ninst*trlen);
    //sort-1
    qsort(t0, ninst, trlen, cmp_trace);
    //sort-2
    t2ii_t *pk = calloc(ninst, sizeof(t2ii_t));
    cpy_int32_t_int32_t(t1, trlen, ninst, kdef, pk);
    void **pp = calloc(ninst, sizeof(void*));
    for(int i=0; i<ninst; i++) {
        pp[i] = pk[i].pay.ptr;
        pk[i].pay.idx = i;
    }
    qsort(pk, ninst, sizeof(t2ii_t), cmp_int32_t_int32_t);
    int *map = calloc(ninst, sizeof(int));
    for(int i=0; i<ninst; i++)
        map[i] = pk[i].pay.idx;
    free(pk);

    void *swap = malloc(trlen);
    t2sort_map_sort(pp, ninst, map, trlen, swap);
    free(swap);
    free(map);
    free(pp);

    if(memcmp(t0, t1, ninst*trlen)!=0) {
        printf("%s: validation ninst=%ld trlen=%d failed!\n",
                __func__, ninst, trlen);
        abort();
    }
    dbg_keys_valid(t1, ninst, trlen, kdef[0].offset, kdef[1].offset);
    dbg_data_valid(t1, ninst, trlen, kdef[0].offset, kdef[1].offset);
    //dbg_keys_print(t1, ninst, trlen, kdef[0].offset, kdef[1].offset);
    free(t0);
    free(t1);
    printf("%s: ninst=%8ld trlen=%5d OK!\n", __func__,
            ninst, trlen);
}

int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("Usage: %s trlen ninst\n", argv[0]);
        exit(1);
    }

    int trlen = atoi(argv[1]);
    int ninst = atoi(argv[2]);
    unit1_test(ninst, trlen, 1234);
    return 0;
}
