import os

##########################################################
# Support maximum 2 key at once for now, template string
#
#  t2sort_getkey(id, trace, n, key)
# we assemble an instance like segy trace, with header and
#   trace altogether, 
##########################################################
type2_str = "typedef struct {{ {t1}  key1; {t2} key2; }} t2sort_{t1}_{t2}_t;"
type3_str = "typedef struct {{ {t1}  key1; {t2} key2; {t3} key3; }} t2sort_{t1}_{t2}_{t3}_t;"

type2_cmp = """
static int cmp_{t1}_{t2}(const void *p1, const void *p2)
{{
    const t2sort_{t1}_{t2}_t *k1=p1;
    const t2sort_{t1}_{t2}_t *k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}}
"""
type3_cmp = """
static int cmp_{t1}_{t2}_{t3}(const void *p1, const void *p2)
{{
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

types = ["int32_t", "float", "int64_t", "double"]
print("#include <stdint.h>")
print("#define T2SORT_INT32    %d"%types.index('int32_t'))
print("#define T2SORT_FLOAT    %d"%types.index('float'))
print("#define T2SORT_INT64    %d"%types.index('int64_t'))
print("#define T2SORT_DOUBLE   %d"%types.index('double'))

for t1 in types:
    for t2 in types:
        print(type2_str.format(t1=t1, t2=t2))
        print(type2_cmp.format(t1=t1, t2=t2))
        for t3 in types:
            print(type3_str.format(t1=t1, t2=t2, t3=t3))
            print(type3_cmp.format(t1=t1, t2=t2, t3=t3))

int (*compar)(const void *, const void *)
print("static int cmp_funcs = ")
