#ifndef C_T2SORT_MAP_SORT_T2SORT
#define C_T2SORT_MAP_SORT_T2SORT
/**
 * @param p    : traces, originally out of order
 * @param n    : number of traces
 * @param m    : sorted map
 * @param len  : trace length in byte
 * @param swap : temporial buffer for sorting
 * */
static void
t2sort_map_sort(void * restrict * p, int n, int * restrict m, int len, 
        void * restrict swap)
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
