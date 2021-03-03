#!/usr/bin/python3

##########################################################
# Support maximum 3 key at once, template strings
#
#  t2sort_getkey(id, trace, n, key)
# we assemble an instance like segy trace, with header and
#   trace altogether, 
##########################################################
type1_str = "typedef struct {{ {t1}  key1; }} t2sort_{t1}_t;"
type2_str = "typedef struct {{ {t1}  key1; {t2} key2; }} t2sort_{t1}_{t2}_t;"
type3_str = "typedef struct {{ {t1}  key1; {t2} key2; {t3} key3; }} t2sort_{t1}_{t2}_{t3}_t;"

type1_cmp = """
static int cmp_{t1}(const void *p1, const void *p2) {{
    const t2sort_{t1}_t *k1=p1;
    const t2sort_{t1}_t *k2=p2;
    return (k1->key1-k2->key1);
}}
"""
type2_cmp = """
static int cmp_{t1}_{t2}(const void *p1, const void *p2) {{
    const t2sort_{t1}_{t2}_t *k1=p1;
    const t2sort_{t1}_{t2}_t *k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}}
"""
type3_cmp = """
static int cmp_{t1}_{t2}_{t3}(const void *p1, const void *p2) {{
    const t2sort_{t1}_{t2}_{t3}_t *k1=p1;
    const t2sort_{t1}_{t2}_{t3}_t *k2=p2;
    if(k1->key1==k2->key1) {{
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }}
    return (k1->key1-k2->key1);
}}
"""
type1_cpy = """
static void cpy_{t1}(const void *p, int *ib, void *pk) {{
    {t1} * k1 = ({t1} *)(p+ib[0]);
    t2sort_{t1}_t *k = pk;
    k->key1 = *k1;
}}
"""
type2_cpy = """
static void cpy_{t1}_{t2}(const void *p, int *ib, void *pk) {{
    {t1} * k1 = ({t1} *)(p+ib[0]);
    {t2} * k2 = ({t2} *)(p+ib[1]);
    t2sort_{t1}_{t2}_t *k = pk;
    k->key1 = *k1; k->key2 = *k2;
}}
"""
type3_cpy = """
static void cpy_{t1}_{t2}_{t3}(const void *p, int *ib, void *pk) {{
    {t1} * k1 = ({t1} *)(p+ib[0]);
    {t2} * k2 = ({t2} *)(p+ib[1]);
    {t3} * k3 = ({t3} *)(p+ib[2]);
    t2sort_{t1}_{t2}_{t3}_t *k = pk;
    k->key1 = *k1; k->key2 = *k2; k->key3 = *k3;
}}
"""
#debug function to cross check and validate helper functions
type1_dbg = """
static void dbg_{t1}(int *t) {{
    printf("%s: type[%d]={t1}\\n", __func__, t[0]);
}}
"""
type2_dbg = """
static void dbg_{t1}_{t2}(int *t) {{
    printf("%s: type[%d]={t1} type[%d]={t2}\\n", __func__, t[0], t[1]);
}}
"""
type3_dbg = """
static void dbg_{t1}_{t2}_{t3}(int *t) {{
    printf("%s: type[%d]={t1}, type[%d]={t2}, type[%d]={t3}\\n",
        __func__, t[0], t[1], t[3]);
}}
"""

# if order changes, call dbg to verify
types = ["int32_t", "float", "int64_t", "double"]
print("#include <stdio.h>")
print("#include <stdint.h>")
print("enum {")
for t1 in types:
    print("T2SORT_%s"%t1.upper(),',')   
print("T2SORT_NTYPE };")    #number of types

for t1 in types:
    print(type1_str.format(t1=t1))
    print(type1_cmp.format(t1=t1))
    print(type1_cpy.format(t1=t1))
    for t2 in types:
        print(type2_str.format(t1=t1, t2=t2))
        print(type2_cmp.format(t1=t1, t2=t2))
        print(type2_cpy.format(t1=t1, t2=t2))
        for t3 in types:
            print(type3_str.format(t1=t1, t2=t2, t3=t3))
            print(type3_cmp.format(t1=t1, t2=t2, t3=t3))
            print(type3_cpy.format(t1=t1, t2=t2, t3=t3))

print("static int (*cmp_funcs[4+16+64])(const void*, const void*) = {")
for t1 in types:
    print("cmp_{t1}, ".format(t1=t1), end='')
    for t2 in types:
        print("cmp_{t1}_{t2}, ".format(t1=t1, t2=t2), end='')
        for t3 in types:
            print("cmp_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='')
        print()
print("};\n")

print("static void (*cpy_funcs[4+16+64])(const void*,int*,void*) = {")
for t1 in types:
    print("cpy_{t1}, ".format(t1=t1), end='')
    for t2 in types:
        print("cpy_{t1}_{t2}, ".format(t1=t1, t2=t2), end='')
        for t3 in types:
            print("cpy_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='')
        print()
print("};\n")

##############################debug-functions##################
for t1 in types:
    print(type1_dbg.format(t1=t1))
    for t2 in types:
        print(type2_dbg.format(t1=t1, t2=t2))
        for t3 in types:
            print(type3_dbg.format(t1=t1, t2=t2, t3=t3))

print("static void (*dbg_funcs[4+16+64])(int*) = {")
for t1 in types:
    print("dbg_{t1}, ".format(t1=t1), end='\n')
    for t2 in types:
        print("dbg_{t1}_{t2}, ".format(t1=t1, t2=t2), end='\n')
        for t3 in types:
            print("dbg_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='\n')
        print()
print("};\n")
