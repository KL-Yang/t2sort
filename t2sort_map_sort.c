#ifndef C_T2SORT_MAP_T2SORT
#define C_T2SORT_MAP_T2SORT

/**
 * Here cannot use pointer map, as it will not give enough
 * ordering information:
 *   1. order of pointers
 *   2. order of keys
 * while integer map orignally is in sequantial order.
 *
 * @param src  : source, unsorted, but position is in order
 * @param des  : destination, sorted pointers according keys
 * @param swap : temporial buffer for sorting
 *
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
#endif
