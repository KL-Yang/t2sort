// Complicated Types Sorting Example.
// By Zereo 04/22/13
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stdlib.h>
#include "../t2sort_i.h"
#include "gentype_gen.h"
#include "../t2sort_debug.c"

template <typename T1, typename T2>

struct key2_t {
    T1      key1;
    T2      key2;
};

template <typename T1, typename T2>
bool sort_key2(const struct key2_t<T1,T2> &p1, const struct key2_t<T1,T2> &p2)
{
    if(p1.key1!=p2.key1)
        return p1.key1<p2.key1;
    return p1.key2<p2.key2;
}

struct ckey_t { float key1; float key2; };
int sort_ccmp(const void *p1, const void *p2) 
{
    const ckey_t *k1=(const ckey_t*)p1;
    const ckey_t *k2=(const ckey_t*)p2;
    if(k1->key1!=k2->key1)
        return k1->key1-k2->key1;
    return k1->key2-k2->key2;
}

//run ninst method
int main(int argc, const char *argv[])
{
    if(argc!=3) {
        printf("Usage: %s ninst method\n"
               "     method=0 dryrun\n"
               "     method=1 c++\n"
               "     method=2 c99\n", argv[0]);
        exit(1);
    }
    int ninst = atoi(argv[1]);
    int methd = atoi(argv[2]);

    srandom(1234);
    //std::vector <struct key2_t <int,int>> mykey(ninst);
    //struct key2_t <int,int> mykey[ninst];
    struct key2_t <int,int> *mykey;
    mykey = new struct key2_t <int,int> [ninst];
    for(int i=0; i<ninst; i++) {
        mykey[i].key1 = dbg_gen_key(1,999);
        mykey[i].key2 = dbg_gen_key(1,999);
    }
    if(methd==2) {
        printf("c99 qsort!\n");
        qsort(mykey, ninst, sizeof(ckey_t), &sort_ccmp);
    } else if (methd==1) {
        printf("c++ std::sort!\n");
        std::sort(mykey, &mykey[ninst-1], sort_key2<int,int>);
        //std::sort(mykey.begin(), mykey.end(), sort_key2<float,float>);
    } else {
        printf("without sort!\n");
    }

    delete mykey;
    return 0;
}
