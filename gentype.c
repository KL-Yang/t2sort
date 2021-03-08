#ifndef C_GENTYPE_T2SORT
#define C_GENTYPE_T2SORT

#include "gentype_gen.h"
#include "gentype_gen.c"

/**
 * @brief get the index of compare and copy key function pointer
 * @param nkey : number of keys used
 * @param keys : keys->type of T2SORT_INT32_T, T2SORT_FLOAT, ...
 * return the corresponding gentype.py func-pointer array index.
 * */
static int 
t2sort_get_func_index(int nkey, const t2sort_key_def_t *keys)
{
    int index=-1;
    if(nkey==1)
        index = keys[0].type*21;
    else if(nkey==2)
        index = keys[0].type*21+keys[1].type*5+1;
    else if(nkey==3)
        index = keys[0].type*21+keys[1].type*5+keys[2].type+2;
    assert(index>=0 && index<84);
    return index;
}

/**
 * @brief get compare function for qsort, for 2 to 3 keys
 * @param nkey : number of keys, 1, 2 or 3
 * @param keys : keys->type of T2SORT_INT32, ... types
 * return the function pointer of corresponding compare function.
 * */
static int 
(*t2sort_getcmp(int nkey, const t2sort_key_def_t *keys))
    (const void*,const void*)
{
    int index = t2sort_get_func_index(nkey, keys);
    return cmp_funcs[index];
}

//return the key extraction function
static void 
(*t2sort_getcpy(int nkey, const t2sort_key_def_t *keys))
    (const void*,int,int,const t2sort_key_def_t*,void*)
{
    int index = t2sort_get_func_index(nkey, keys);
    return cpy_funcs[index];
}

static int
t2sort_key_size(int nkey, const t2sort_key_def_t *keys)
{
    int index = t2sort_get_func_index(nkey, keys);
    return siz_types[index];
}
#endif
