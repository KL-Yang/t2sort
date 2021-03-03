#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "x_unit3_type.c"

static int t2sort_index1(int t1)
{   return t1*21;           } 
static int t2sort_index2(int t1, int t2)
{   return t1*21+t2*5+1;    }
static int t2sort_index3(int t1, int t2, int t3)
{   return t1*21+t2*5+t3+2; }

int main()
{
    int x, i[2], t[3];
    x = 0; i[0] = 5; i[1] = 7;
    cmp_funcs[0](&i[0], &i[1]);
    cpy_funcs[0](&i[0], &x, &i[1]);
    //test for 1-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++) {
        x = t2sort_index1(t[0]);
        printf("1@type=%d index=%d\n", t[0], x);
        dbg_funcs[x](t);
    }
    //test for 2-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++)
        for(t[1]=0; t[1]<T2SORT_NTYPE; t[1]++) {
            x = t2sort_index2(t[0], t[1]);
            printf("2@type=%d,%d index=%d\n", t[0], t[1], x);
            dbg_funcs[x](t);
    }
    //test for 2-key only
    for(t[0]=0; t[0]<T2SORT_NTYPE; t[0]++)
        for(t[1]=0; t[1]<T2SORT_NTYPE; t[1]++)
            for(t[2]=0; t[2]<T2SORT_NTYPE; t[2]++) {
                x = t2sort_index3(t[0], t[1], t[2]);
                printf("2@type=%d,%d,%d index=%d\n", t[0], t[1], t[2], x);
                dbg_funcs[x](t);
            }
    printf("Unit test successful!\n");
    return 0;
}
