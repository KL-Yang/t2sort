#ifndef C_T2SORT_MAP_T2SORT
#define C_T2SORT_MAP_T2SORT
/**
 * Cannot use pointer map instead of index map, as pointer will 
 * not give enough information to create a linked list.
 *   1. in ideal case the memcpys form a single linked loop
 *   2. actually it is breaked into many small linked loops
 * @param p    : traces, originally out of order
 * @param n    : number of traces
 * @param m    : sorted map
 * @param len  : trace length in byte
 * @param swap : temporial buffer for sorting
 * */
void
t2sort_map_sort(void **p, int n, int *m, int len, void *swap)
{
    for(register int i=0; i<n; /*no action*/ ) {
        while(i<n && m[i]==i)
            i++;
        if(i==n)
            break;
        memcpy(swap, p[i], len);
        for(register int j=i, src=m[j]; j!=src; src=m[j]) {
            if(src<=i) {
                memcpy(p[j], swap, len);   //must be in swap
                m[j] = j;
                break;
            } 
            memcpy(p[j], p[src], len);
            m[j] = j;
            j = src;
        }
    }
}

//this is dumb version use much more memory
void t2sort_map_sort2(void **p, int n, int *m, int64_t len)
{
    void *x = calloc(n, len);
    for(int i=0, j; i<n; i++) {
        j = m[i];
        memcpy(x+i*len, p[j], len);
    }
    for(int i=0; i<n; i++) 
        memcpy(p[i], x+i*len, len);
    free(x);
}
#endif
