#!/usr/bin/python3
import sys
##########################################################
# Support maximum 3 key all togather, template functions
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
static void cpy_{t1}(const void *p, const int *ib, void *pk) {{
    {t1} * k1 = ({t1} *)(p+ib[0]);
    t2sort_{t1}_t *k = pk;
    k->key1 = *k1;
}}
"""
type2_cpy = """
static void cpy_{t1}_{t2}(const void *p, const int *ib, void *pk) {{
    {t1} * k1 = ({t1} *)(p+ib[0]);
    {t2} * k2 = ({t2} *)(p+ib[1]);
    t2sort_{t1}_{t2}_t *k = pk;
    k->key1 = *k1; k->key2 = *k2;
}}
"""
type3_cpy = """
static void cpy_{t1}_{t2}_{t3}(const void *p, const int *ib, void *pk) {{
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
    if(T2SORT_{T1}!=t[0]) {{
        printf("%s-error: type[%d]={t1}\\n", __func__, t[0]);
        abort();
}} }}
"""
type2_dbg = """
static void dbg_{t1}_{t2}(int *t) {{
    if(T2SORT_{T1}!=t[0] || T2SORT_{T2}!=t[1]) {{
        printf("%s-error: type[%d]={t1} type[%d]={t2}\\n", __func__, t[0], t[1]);
    abort();
}} }}
"""
type3_dbg = """
static void dbg_{t1}_{t2}_{t3}(int *t) {{
    if(T2SORT_{T1}!=t[0] || T2SORT_{T2}!=t[1] ||T2SORT_{T3}!=t[2]) {{
        printf("%s-error: type[%d]={t1}, type[%d]={t2}, type[%d]={t3}\\n",
            __func__, t[0], t[1], t[3]);
        abort();
}} }}
"""

# if order changes, call dbg to verify
types = ["int32_t", "float", "int64_t", "double"]
print("//Auto generated file, do not edit!")

if len(sys.argv)>1 and sys.argv[1]=="header":
    print("#ifndef H_GENTYPE_PY_GEN")
    print("#define H_GENTYPE_PY_GEN")
    print("\nenum {")
    for t1 in types:
        print("T2SORT_%s"%t1.upper(),',')   
    print("T2SORT_NTYPE };\n")      #number of types
    print("int t2sort_type_size[] = {")
    for t1 in types:
        print("sizeof(%s),"%t1)
    print("};")
    print("#endif")
    sys.exit(0)

print("#ifndef C_GENTYPE_PY_GEN")
print("#define C_GENTYPE_PY_GEN")
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

print("static void (*cpy_funcs[4+16+64])(const void*,const int*,void*) = {")
for t1 in types:
    print("cpy_{t1}, ".format(t1=t1), end='')
    for t2 in types:
        print("cpy_{t1}_{t2}, ".format(t1=t1, t2=t2), end='')
        for t3 in types:
            print("cpy_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='')
        print()
print("};\n")
print("#endif")

if len(sys.argv)<=1 or sys.argv[1]!="debug":
    sys.exit(0)
############################ debug-functions ##############################

print("#ifndef C_DEBUG_GENTYPE_PY_GEN")
print("#define C_DEBUG_GENTYPE_PY_GEN")
for t1 in types:
    print(type1_dbg.format(t1=t1, T1=t1.upper()))
    for t2 in types:
        print(type2_dbg.format(t1=t1, t2=t2, T1=t1.upper(), T2=t2.upper()))
        for t3 in types:
            print(type3_dbg.format(t1=t1, t2=t2, t3=t3, T1=t1.upper(), T2=t2.upper(), T3=t3.upper()))

print("static void (*dbg_funcs[4+16+64])(int*) = {")
for t1 in types:
    print("dbg_{t1}, ".format(t1=t1), end='\n')
    for t2 in types:
        print("dbg_{t1}_{t2}, ".format(t1=t1, t2=t2), end='\n')
        for t3 in types:
            print("dbg_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='\n')
        print()
print("};\n")
print("#endif")
