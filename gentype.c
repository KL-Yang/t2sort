#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include "gentype_gen.h"

/**
 * @brief get the index of compare and copy key function pointer
 * @param nkey    : number of keys used
 * @param t[nkey] : type length argument of key-1, key-2, key-3
 * of type T2SORT_INT32_T, T2SORT_FLOAT, ...
 * */
static int t2sort_get_index(int nkey, int *t)
{
    int index=-1;
    if(nkey==1)
        index = t[0]*21;
    else if(nkey==2)
        index = t[0]*21+t[1]*5+1;
    else if(nkey==3)
        index = t[0]*21+t[1]*5+t[2]+2;
    assert(index>=0 && index<84);
    return index;
}

/**
 * @brief get compare function for qsort, for 2 to 3 keys
 * @param num  : number of keys, 1, 2 or 3
 * @param variable length arguments of T2SORT_INT32, ... types
 * return the function pointer of corresponding compare function.
 * */
static int (*t2sort_getcmp(int num, ...))(const void*,const void*)
{
    int t[3];
    va_list valist;
    assert(num<=3 && num>=1);   //1-3 keys
    va_start(valist, num);
    for(int i=0; i<num; i++)
        t[i] = va_arg(valist, int);
    va_end(valist);
    int index = t2sort_get_index(num, t);
    return cmp_funcs[index];
}

//return the key extraction function
static void (*t2sort_getcpy(int num, ...))(const void*,const int*,void*)
{
    int t[3];
    va_list valist;
    assert(num<=3 && num>=1);   //1-3 keys
    va_start(valist, num);
    for(int i=0; i<num; i++)
        t[i] = va_arg(valist, int);
    va_end(valist);
    int index = t2sort_get_index(num, t);
    return cpy_funcs[index];
}
