#include "common.h"

/**
 * @param size : total size in number of int
 * */
void gen_data(int *p, int n, int size, int kmax)
{
    t2key_t *k; int head, *payload; 
    head = sizeof(t2key_t)/sizeof(int); assert(size>head);
    for(int i=0; i<n; i++) {
        k = (t2key_t*)(p+i*size);
        k->seq = i;
        k->key = random()%(kmax+1);

        payload = p+i*size+head;
        for(int j=0; j<size-head; j++)
            payload[j] = k->key;
    }
}

void get_keys(int *p, int n, int size, t2key_t *k)
{
    for(int i=0; i<n; i++) {
        t2key_t *x = (t2key_t*)(p+i*size);
        k[i] = x[0];
    }
}

bool cmp_keys(const t2key_t &a, const t2key_t &b)
{
    return a.key<b.key;
}
