#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../t2sort_i.h"
#include "gentype_gen.h"
#include "gentype_gen.c"
#include "../gentype.c"

int main()
{
    int x, t[3]; t2_kdef_t kdef[3];

    //test for 1-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++) {
        kdef[0].type = t[0];
        x = t2sort_get_func_index(1, kdef);
        printf("1@type=%d index=%d\n", t[0], x);
        dbg_funcs[x](t);
    }
    //test for 2-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++) {
        kdef[0].type = t[0];
        for(t[1]=0; t[1]<T2SORT_NTYPE; t[1]++) {
            kdef[1].type = t[1];
            x = t2sort_get_func_index(2, kdef);
            printf("2@type=%d,%d index=%d\n", t[0], t[1], x);
            dbg_funcs[x](t);
        } 
    }
    //test for 3-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++) {
        kdef[0].type = t[0];
        for(t[1]=0; t[1]<T2SORT_NTYPE; t[1]++) {
            kdef[1].type = t[1];
            for(t[2]=0; t[2]<T2SORT_NTYPE; t[2]++) {
                kdef[2].type = t[2];
                x = t2sort_get_func_index(3, kdef);
                printf("2@type=%d,%d,%d index=%d\n", t[0], t[1], t[2], x);
                dbg_funcs[x](t);
            }
        }
    }
    printf("Unit test successful!\n");
    return 0;
}
