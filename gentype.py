#!/usr/bin/python3
import sys
##########################################################
# Support maximum 3 key all togather, template functions
##########################################################
type1_str = "typedef struct {{ t2_pay_t pay; {t1}  key1; }} t2sort_{t1}_t;"
type2_str = "typedef struct {{ t2_pay_t pay; {t1}  key1; {t2} key2; }} t2sort_{t1}_{t2}_t;"
type3_str = "typedef struct {{ t2_pay_t pay; {t1}  key1; {t2} key2; {t3} key3; }} t2sort_{t1}_{t2}_{t3}_t;"

type1_cmp = """
static int cmp_{t1}(const void *p1, const void *p2) {{
    const t2sort_{t1}_t * restrict k1=p1;
    const t2sort_{t1}_t * restrict k2=p2;
    return (k1->key1-k2->key1);
}}
"""
type2_cmp = """
static int cmp_{t1}_{t2}(const void *p1, const void *p2) {{
    const t2sort_{t1}_{t2}_t * restrict k1=p1;
    const t2sort_{t1}_{t2}_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}}
"""
type3_cmp = """
static int cmp_{t1}_{t2}_{t3}(const void *p1, const void *p2) {{
    const t2sort_{t1}_{t2}_{t3}_t * restrict k1=p1;
    const t2sort_{t1}_{t2}_{t3}_t * restrict k2=p2;
    if(k1->key1==k2->key1) {{
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }}
    return (k1->key1-k2->key1);
}}
"""
type1_cpy = """
static void cpy_{t1}(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {{
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {{
        {t1} * restrict k1 = ({t1} *)(p+kd[0].offset);
        t2sort_{t1}_t * restrict k = pk;
        k[i].key1 = *k1; k[i].pay.ptr = p;
    }} }}
"""
type2_cpy = """
static void cpy_{t1}_{t2}(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {{
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {{
        {t1} * restrict k1 = ({t1} *)(p+kd[0].offset);
        {t2} * restrict k2 = ({t2} *)(p+kd[1].offset);
        t2sort_{t1}_{t2}_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    }} }}
"""
type3_cpy = """
static void cpy_{t1}_{t2}_{t3}(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {{
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {{
        {t1} * restrict k1 = ({t1} *)(p+kd[0].offset);
        {t2} * restrict k2 = ({t2} *)(p+kd[1].offset);
        {t3} * restrict k3 = ({t3} *)(p+kd[2].offset);
        t2sort_{t1}_{t2}_{t3}_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    }} }}
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

print("static int siz_types[] = {")
for t1 in types:
    print("sizeof(t2sort_{t1}_t), ".format(t1=t1), end='')
    for t2 in types:
        print("sizeof(t2sort_{t1}_{t2}_t), ".format(t1=t1, t2=t2), end='')
        for t3 in types:
            print("sizeof(t2sort_{t1}_{t2}_{t3}_t), ".format(t1=t1, t2=t2, t3=t3), end='')
print("};\n")

print("static int (*cmp_funcs[4+16+64])(const void*, const void*) = {")
for t1 in types:
    print("cmp_{t1}, ".format(t1=t1), end='')
    for t2 in types:
        print("cmp_{t1}_{t2}, ".format(t1=t1, t2=t2), end='')
        for t3 in types:
            print("cmp_{t1}_{t2}_{t3}, ".format(t1=t1, t2=t2, t3=t3), end='')
        print()
print("};\n")

print("static void (*cpy_funcs[4+16+64])(void*,int,int,const t2sort_key_def_t*,void*) = {")
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
