#include "common.h"

/**
 * @brief Out Of Place map to debug the inplace map
 * @param n : number of trace
 * @param s : size of a trace
 * @param x : input
 * @param m : map function
 * @param y : output y=m(x)
 * */
void oop_map(int n, int s, int **x, int *m, int **y)
{
    for(int i=0; i<n; i++)
        memcpy(y[i], x[m[i]], s*sizeof(int));
}

/**
 * @return 1 if in order, 0 if not in order
 * */
int is_in_order(int *keys, int nkey, int size)
{
    t2key_t *key1, *key0; int head, *payload;
    head = sizeof(t2key_t)/sizeof(int);

    key0 = (t2key_t*)keys;
    for(int i=1; i<nkey; i++) {
        key1 = (t2key_t*)(keys+i*size);
        if(key1->key<key0->key) {
            printf("key1=%4d key0=%4d\n", key1->key, key0->key);
            return 0;   //not in order
        }
        key0 = key1;
    }
    for(int i=0; i<nkey; i++) {
        key1 = (t2key_t*)(keys+i*size);
        payload = keys+i*size+head;
        for(int j=0; j<size-head; j++) 
            if(payload[j]!=key1->key) {
                printf("[%4d] payload[%4d]=%4d key1->key=%4d\n", i, j, payload[j], key1->key);
                return 0;
            }
    }
    return 1;
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

    //Generate data
    int *trc0 = new int[nkey*size];
    gen_data(trc0, nkey, size, 100);

    //Sort keys
    t2key_t *key0 = new t2key_t[nkey];
    get_keys(trc0, nkey, size, key0);
    std::sort(key0, key0+nkey, cmp_keys);

    //Build the map!
    int *map = new int[nkey];
    for(int i=0; i<nkey; i++) {
        map[i] = key0[i].seq;
        printf("[%4d] key=%4d seq=%4d\n", i, key0[i].key, key0[i].seq);
    }

    //test out of place map
    int *trc1 = new int[nkey*size];
    int **pp0 = new int*[nkey];
    int **pp1 = new int*[nkey];
    for(int i=0; i<nkey; i++) {
        pp0[i] = trc0+i*size;
        pp1[i] = trc1+i*size;
    }
    oop_map(nkey, size, pp0, map, pp1);

    if(is_in_order(trc1, nkey, size)==0) {
        printf("Not in order!\n");
        for(int i=0; i<nkey; i++) {
            t2key_t *x = (t2key_t*)(trc1+i*size);
            printf("[%4d] key=%4d seq=%4d\n", i, x->key, x->seq);
        }
    } else {
        printf("In order!\n");
    }
    /*
    void **x = new void * [nkey];
    void **y = new void * [nkey];
    for(int i=0; i<nkey; i++) {
        x[i] = (void*)(keyx+i*size);
        y[i] = (void*)(keyy+i*size);
    }
    oop_map(nkey, size, x, map, y);
    */

    //Add code to verify the mapping!

    delete[] pp0;
    delete[] pp1;
    delete[] trc0;
    delete[] trc1;
    delete[] key0;
    delete[] map;
    return 0;
}
