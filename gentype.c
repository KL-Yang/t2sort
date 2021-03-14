#ifndef C_GENTYPE_T2SORT
#define C_GENTYPE_T2SORT

#include "gentype_gen.h"
#include "gentype_gen.c"

/**
 * @brief Get the index of compare and copy key function pointer
 * @param ndef : number of key definitions
 * @param kdef : kdef->type of T2SORT_INT32_T, T2SORT_FLOAT, ...
 * return the corresponding gentype.py func-pointer array index.
 * */
static int 
t2sort_get_func_index(int ndef, const t2_kdef_t *kdef)
{
    int index=-1;
    if(ndef==1)
        index = kdef[0].type*21;
    else if(ndef==2)
        index = kdef[0].type*21+kdef[1].type*5+1;
    else if(ndef==3)
        index = kdef[0].type*21+kdef[1].type*5+kdef[2].type+2;
    assert(index>=0 && index<84);
    return index;
}

/**
 * @brief Get compare function for qsort, for 2 to 3 kdef 
 * @param ndef : number of kdef, 1, 2 or 3
 * @param kdef : kdef->type of T2SORT_INT32, ... types
 * return the function pointer of corresponding compare function.
 * */
static int 
(*t2sort_getcmp(int ndef, const t2_kdef_t *kdef))
    (const void*,const void*)
{
    int index = t2sort_get_func_index(ndef, kdef);
    return cmp_funcs[index];
}

//return the key extraction function
static void 
(*t2sort_getcpy(int ndef, const t2_kdef_t *kdef))
    (void*,int,int,const t2_kdef_t*,void*)
{
    int index = t2sort_get_func_index(ndef, kdef);
    return cpy_funcs[index];
}

static int
t2sort_key_size(int ndef, const t2_kdef_t *kdef)
{
    int index = t2sort_get_func_index(ndef, kdef);
    return siz_types[index];
}
#endif
