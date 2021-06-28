//Auto generated file, do not edit!
#ifndef C_GENTYPE_PY_GEN
#define C_GENTYPE_PY_GEN
typedef struct { t2_pay_t pay; int32_t  key1; } t2sort_int32_t_t;

static int cmp_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_t * restrict k2=p2;
    return (k1->key1-k2->key1);
}


static void cpy_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        t2sort_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int32_t key2; } t2sort_int32_t_int32_t_t;

static int cmp_int32_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        t2sort_int32_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int32_t key2; int32_t key3; } t2sort_int32_t_int32_t_int32_t_t;

static int cmp_int32_t_int32_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int32_t_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_int32_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int32_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int32_t_int32_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int32_t key2; float key3; } t2sort_int32_t_int32_t_float_t;

static int cmp_int32_t_int32_t_float(const void *p1, const void *p2) {
    const t2sort_int32_t_int32_t_float_t * restrict k1=p1;
    const t2sort_int32_t_int32_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int32_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int32_t_int32_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int32_t key2; int64_t key3; } t2sort_int32_t_int32_t_int64_t_t;

static int cmp_int32_t_int32_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int32_t_int64_t_t * restrict k1=p1;
    const t2sort_int32_t_int32_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int32_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int32_t_int32_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int32_t key2; double key3; } t2sort_int32_t_int32_t_double_t;

static int cmp_int32_t_int32_t_double(const void *p1, const void *p2) {
    const t2sort_int32_t_int32_t_double_t * restrict k1=p1;
    const t2sort_int32_t_int32_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int32_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int32_t_int32_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; float key2; } t2sort_int32_t_float_t;

static int cmp_int32_t_float(const void *p1, const void *p2) {
    const t2sort_int32_t_float_t * restrict k1=p1;
    const t2sort_int32_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        t2sort_int32_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; float key2; int32_t key3; } t2sort_int32_t_float_int32_t_t;

static int cmp_int32_t_float_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_float_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_float_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_float_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int32_t_float_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; float key2; float key3; } t2sort_int32_t_float_float_t;

static int cmp_int32_t_float_float(const void *p1, const void *p2) {
    const t2sort_int32_t_float_float_t * restrict k1=p1;
    const t2sort_int32_t_float_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_float_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int32_t_float_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; float key2; int64_t key3; } t2sort_int32_t_float_int64_t_t;

static int cmp_int32_t_float_int64_t(const void *p1, const void *p2) {
    const t2sort_int32_t_float_int64_t_t * restrict k1=p1;
    const t2sort_int32_t_float_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_float_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int32_t_float_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; float key2; double key3; } t2sort_int32_t_float_double_t;

static int cmp_int32_t_float_double(const void *p1, const void *p2) {
    const t2sort_int32_t_float_double_t * restrict k1=p1;
    const t2sort_int32_t_float_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_float_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int32_t_float_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int64_t key2; } t2sort_int32_t_int64_t_t;

static int cmp_int32_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int64_t_t * restrict k1=p1;
    const t2sort_int32_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        t2sort_int32_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int64_t key2; int32_t key3; } t2sort_int32_t_int64_t_int32_t_t;

static int cmp_int32_t_int64_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int64_t_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_int64_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int64_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int32_t_int64_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int64_t key2; float key3; } t2sort_int32_t_int64_t_float_t;

static int cmp_int32_t_int64_t_float(const void *p1, const void *p2) {
    const t2sort_int32_t_int64_t_float_t * restrict k1=p1;
    const t2sort_int32_t_int64_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int64_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int32_t_int64_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int64_t key2; int64_t key3; } t2sort_int32_t_int64_t_int64_t_t;

static int cmp_int32_t_int64_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int32_t_int64_t_int64_t_t * restrict k1=p1;
    const t2sort_int32_t_int64_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int64_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int32_t_int64_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; int64_t key2; double key3; } t2sort_int32_t_int64_t_double_t;

static int cmp_int32_t_int64_t_double(const void *p1, const void *p2) {
    const t2sort_int32_t_int64_t_double_t * restrict k1=p1;
    const t2sort_int32_t_int64_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_int64_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int32_t_int64_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; double key2; } t2sort_int32_t_double_t;

static int cmp_int32_t_double(const void *p1, const void *p2) {
    const t2sort_int32_t_double_t * restrict k1=p1;
    const t2sort_int32_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        t2sort_int32_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; double key2; int32_t key3; } t2sort_int32_t_double_int32_t_t;

static int cmp_int32_t_double_int32_t(const void *p1, const void *p2) {
    const t2sort_int32_t_double_int32_t_t * restrict k1=p1;
    const t2sort_int32_t_double_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_double_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int32_t_double_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; double key2; float key3; } t2sort_int32_t_double_float_t;

static int cmp_int32_t_double_float(const void *p1, const void *p2) {
    const t2sort_int32_t_double_float_t * restrict k1=p1;
    const t2sort_int32_t_double_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_double_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int32_t_double_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; double key2; int64_t key3; } t2sort_int32_t_double_int64_t_t;

static int cmp_int32_t_double_int64_t(const void *p1, const void *p2) {
    const t2sort_int32_t_double_int64_t_t * restrict k1=p1;
    const t2sort_int32_t_double_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_double_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int32_t_double_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int32_t  key1; double key2; double key3; } t2sort_int32_t_double_double_t;

static int cmp_int32_t_double_double(const void *p1, const void *p2) {
    const t2sort_int32_t_double_double_t * restrict k1=p1;
    const t2sort_int32_t_double_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int32_t_double_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int32_t * restrict k1 = (int32_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int32_t_double_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; } t2sort_float_t;

static int cmp_float(const void *p1, const void *p2) {
    const t2sort_float_t * restrict k1=p1;
    const t2sort_float_t * restrict k2=p2;
    return (k1->key1-k2->key1);
}


static void cpy_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        t2sort_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int32_t key2; } t2sort_float_int32_t_t;

static int cmp_float_int32_t(const void *p1, const void *p2) {
    const t2sort_float_int32_t_t * restrict k1=p1;
    const t2sort_float_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_float_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        t2sort_float_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int32_t key2; int32_t key3; } t2sort_float_int32_t_int32_t_t;

static int cmp_float_int32_t_int32_t(const void *p1, const void *p2) {
    const t2sort_float_int32_t_int32_t_t * restrict k1=p1;
    const t2sort_float_int32_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int32_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_float_int32_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int32_t key2; float key3; } t2sort_float_int32_t_float_t;

static int cmp_float_int32_t_float(const void *p1, const void *p2) {
    const t2sort_float_int32_t_float_t * restrict k1=p1;
    const t2sort_float_int32_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int32_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_float_int32_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int32_t key2; int64_t key3; } t2sort_float_int32_t_int64_t_t;

static int cmp_float_int32_t_int64_t(const void *p1, const void *p2) {
    const t2sort_float_int32_t_int64_t_t * restrict k1=p1;
    const t2sort_float_int32_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int32_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_float_int32_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int32_t key2; double key3; } t2sort_float_int32_t_double_t;

static int cmp_float_int32_t_double(const void *p1, const void *p2) {
    const t2sort_float_int32_t_double_t * restrict k1=p1;
    const t2sort_float_int32_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int32_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_float_int32_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; float key2; } t2sort_float_float_t;

static int cmp_float_float(const void *p1, const void *p2) {
    const t2sort_float_float_t * restrict k1=p1;
    const t2sort_float_float_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_float_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        t2sort_float_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; float key2; int32_t key3; } t2sort_float_float_int32_t_t;

static int cmp_float_float_int32_t(const void *p1, const void *p2) {
    const t2sort_float_float_int32_t_t * restrict k1=p1;
    const t2sort_float_float_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_float_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_float_float_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; float key2; float key3; } t2sort_float_float_float_t;

static int cmp_float_float_float(const void *p1, const void *p2) {
    const t2sort_float_float_float_t * restrict k1=p1;
    const t2sort_float_float_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_float_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_float_float_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; float key2; int64_t key3; } t2sort_float_float_int64_t_t;

static int cmp_float_float_int64_t(const void *p1, const void *p2) {
    const t2sort_float_float_int64_t_t * restrict k1=p1;
    const t2sort_float_float_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_float_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_float_float_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; float key2; double key3; } t2sort_float_float_double_t;

static int cmp_float_float_double(const void *p1, const void *p2) {
    const t2sort_float_float_double_t * restrict k1=p1;
    const t2sort_float_float_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_float_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_float_float_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int64_t key2; } t2sort_float_int64_t_t;

static int cmp_float_int64_t(const void *p1, const void *p2) {
    const t2sort_float_int64_t_t * restrict k1=p1;
    const t2sort_float_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_float_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        t2sort_float_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int64_t key2; int32_t key3; } t2sort_float_int64_t_int32_t_t;

static int cmp_float_int64_t_int32_t(const void *p1, const void *p2) {
    const t2sort_float_int64_t_int32_t_t * restrict k1=p1;
    const t2sort_float_int64_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int64_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_float_int64_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int64_t key2; float key3; } t2sort_float_int64_t_float_t;

static int cmp_float_int64_t_float(const void *p1, const void *p2) {
    const t2sort_float_int64_t_float_t * restrict k1=p1;
    const t2sort_float_int64_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int64_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_float_int64_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int64_t key2; int64_t key3; } t2sort_float_int64_t_int64_t_t;

static int cmp_float_int64_t_int64_t(const void *p1, const void *p2) {
    const t2sort_float_int64_t_int64_t_t * restrict k1=p1;
    const t2sort_float_int64_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int64_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_float_int64_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; int64_t key2; double key3; } t2sort_float_int64_t_double_t;

static int cmp_float_int64_t_double(const void *p1, const void *p2) {
    const t2sort_float_int64_t_double_t * restrict k1=p1;
    const t2sort_float_int64_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_int64_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_float_int64_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; double key2; } t2sort_float_double_t;

static int cmp_float_double(const void *p1, const void *p2) {
    const t2sort_float_double_t * restrict k1=p1;
    const t2sort_float_double_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_float_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        t2sort_float_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; double key2; int32_t key3; } t2sort_float_double_int32_t_t;

static int cmp_float_double_int32_t(const void *p1, const void *p2) {
    const t2sort_float_double_int32_t_t * restrict k1=p1;
    const t2sort_float_double_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_double_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_float_double_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; double key2; float key3; } t2sort_float_double_float_t;

static int cmp_float_double_float(const void *p1, const void *p2) {
    const t2sort_float_double_float_t * restrict k1=p1;
    const t2sort_float_double_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_double_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_float_double_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; double key2; int64_t key3; } t2sort_float_double_int64_t_t;

static int cmp_float_double_int64_t(const void *p1, const void *p2) {
    const t2sort_float_double_int64_t_t * restrict k1=p1;
    const t2sort_float_double_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_double_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_float_double_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; float  key1; double key2; double key3; } t2sort_float_double_double_t;

static int cmp_float_double_double(const void *p1, const void *p2) {
    const t2sort_float_double_double_t * restrict k1=p1;
    const t2sort_float_double_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_float_double_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        float * restrict k1 = (float *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_float_double_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; } t2sort_int64_t_t;

static int cmp_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_t * restrict k2=p2;
    return (k1->key1-k2->key1);
}


static void cpy_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        t2sort_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int32_t key2; } t2sort_int64_t_int32_t_t;

static int cmp_int64_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int32_t_t * restrict k1=p1;
    const t2sort_int64_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        t2sort_int64_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int32_t key2; int32_t key3; } t2sort_int64_t_int32_t_int32_t_t;

static int cmp_int64_t_int32_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int32_t_int32_t_t * restrict k1=p1;
    const t2sort_int64_t_int32_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int32_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int64_t_int32_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int32_t key2; float key3; } t2sort_int64_t_int32_t_float_t;

static int cmp_int64_t_int32_t_float(const void *p1, const void *p2) {
    const t2sort_int64_t_int32_t_float_t * restrict k1=p1;
    const t2sort_int64_t_int32_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int32_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int64_t_int32_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int32_t key2; int64_t key3; } t2sort_int64_t_int32_t_int64_t_t;

static int cmp_int64_t_int32_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int32_t_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_int32_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int32_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int64_t_int32_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int32_t key2; double key3; } t2sort_int64_t_int32_t_double_t;

static int cmp_int64_t_int32_t_double(const void *p1, const void *p2) {
    const t2sort_int64_t_int32_t_double_t * restrict k1=p1;
    const t2sort_int64_t_int32_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int32_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int64_t_int32_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; float key2; } t2sort_int64_t_float_t;

static int cmp_int64_t_float(const void *p1, const void *p2) {
    const t2sort_int64_t_float_t * restrict k1=p1;
    const t2sort_int64_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        t2sort_int64_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; float key2; int32_t key3; } t2sort_int64_t_float_int32_t_t;

static int cmp_int64_t_float_int32_t(const void *p1, const void *p2) {
    const t2sort_int64_t_float_int32_t_t * restrict k1=p1;
    const t2sort_int64_t_float_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_float_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int64_t_float_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; float key2; float key3; } t2sort_int64_t_float_float_t;

static int cmp_int64_t_float_float(const void *p1, const void *p2) {
    const t2sort_int64_t_float_float_t * restrict k1=p1;
    const t2sort_int64_t_float_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_float_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int64_t_float_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; float key2; int64_t key3; } t2sort_int64_t_float_int64_t_t;

static int cmp_int64_t_float_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_float_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_float_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_float_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int64_t_float_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; float key2; double key3; } t2sort_int64_t_float_double_t;

static int cmp_int64_t_float_double(const void *p1, const void *p2) {
    const t2sort_int64_t_float_double_t * restrict k1=p1;
    const t2sort_int64_t_float_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_float_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int64_t_float_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int64_t key2; } t2sort_int64_t_int64_t_t;

static int cmp_int64_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        t2sort_int64_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int64_t key2; int32_t key3; } t2sort_int64_t_int64_t_int32_t_t;

static int cmp_int64_t_int64_t_int32_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int64_t_int32_t_t * restrict k1=p1;
    const t2sort_int64_t_int64_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int64_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int64_t_int64_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int64_t key2; float key3; } t2sort_int64_t_int64_t_float_t;

static int cmp_int64_t_int64_t_float(const void *p1, const void *p2) {
    const t2sort_int64_t_int64_t_float_t * restrict k1=p1;
    const t2sort_int64_t_int64_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int64_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int64_t_int64_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int64_t key2; int64_t key3; } t2sort_int64_t_int64_t_int64_t_t;

static int cmp_int64_t_int64_t_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_int64_t_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_int64_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int64_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int64_t_int64_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; int64_t key2; double key3; } t2sort_int64_t_int64_t_double_t;

static int cmp_int64_t_int64_t_double(const void *p1, const void *p2) {
    const t2sort_int64_t_int64_t_double_t * restrict k1=p1;
    const t2sort_int64_t_int64_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_int64_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int64_t_int64_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; double key2; } t2sort_int64_t_double_t;

static int cmp_int64_t_double(const void *p1, const void *p2) {
    const t2sort_int64_t_double_t * restrict k1=p1;
    const t2sort_int64_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        t2sort_int64_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; double key2; int32_t key3; } t2sort_int64_t_double_int32_t_t;

static int cmp_int64_t_double_int32_t(const void *p1, const void *p2) {
    const t2sort_int64_t_double_int32_t_t * restrict k1=p1;
    const t2sort_int64_t_double_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_double_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_int64_t_double_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; double key2; float key3; } t2sort_int64_t_double_float_t;

static int cmp_int64_t_double_float(const void *p1, const void *p2) {
    const t2sort_int64_t_double_float_t * restrict k1=p1;
    const t2sort_int64_t_double_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_double_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_int64_t_double_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; double key2; int64_t key3; } t2sort_int64_t_double_int64_t_t;

static int cmp_int64_t_double_int64_t(const void *p1, const void *p2) {
    const t2sort_int64_t_double_int64_t_t * restrict k1=p1;
    const t2sort_int64_t_double_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_double_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_int64_t_double_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; int64_t  key1; double key2; double key3; } t2sort_int64_t_double_double_t;

static int cmp_int64_t_double_double(const void *p1, const void *p2) {
    const t2sort_int64_t_double_double_t * restrict k1=p1;
    const t2sort_int64_t_double_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_int64_t_double_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        int64_t * restrict k1 = (int64_t *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_int64_t_double_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; } t2sort_double_t;

static int cmp_double(const void *p1, const void *p2) {
    const t2sort_double_t * restrict k1=p1;
    const t2sort_double_t * restrict k2=p2;
    return (k1->key1-k2->key1);
}


static void cpy_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        t2sort_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int32_t key2; } t2sort_double_int32_t_t;

static int cmp_double_int32_t(const void *p1, const void *p2) {
    const t2sort_double_int32_t_t * restrict k1=p1;
    const t2sort_double_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_double_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        t2sort_double_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int32_t key2; int32_t key3; } t2sort_double_int32_t_int32_t_t;

static int cmp_double_int32_t_int32_t(const void *p1, const void *p2) {
    const t2sort_double_int32_t_int32_t_t * restrict k1=p1;
    const t2sort_double_int32_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int32_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_double_int32_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int32_t key2; float key3; } t2sort_double_int32_t_float_t;

static int cmp_double_int32_t_float(const void *p1, const void *p2) {
    const t2sort_double_int32_t_float_t * restrict k1=p1;
    const t2sort_double_int32_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int32_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_double_int32_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int32_t key2; int64_t key3; } t2sort_double_int32_t_int64_t_t;

static int cmp_double_int32_t_int64_t(const void *p1, const void *p2) {
    const t2sort_double_int32_t_int64_t_t * restrict k1=p1;
    const t2sort_double_int32_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int32_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_double_int32_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int32_t key2; double key3; } t2sort_double_int32_t_double_t;

static int cmp_double_int32_t_double(const void *p1, const void *p2) {
    const t2sort_double_int32_t_double_t * restrict k1=p1;
    const t2sort_double_int32_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int32_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int32_t * restrict k2 = (int32_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_double_int32_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; float key2; } t2sort_double_float_t;

static int cmp_double_float(const void *p1, const void *p2) {
    const t2sort_double_float_t * restrict k1=p1;
    const t2sort_double_float_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_double_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        t2sort_double_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; float key2; int32_t key3; } t2sort_double_float_int32_t_t;

static int cmp_double_float_int32_t(const void *p1, const void *p2) {
    const t2sort_double_float_int32_t_t * restrict k1=p1;
    const t2sort_double_float_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_float_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_double_float_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; float key2; float key3; } t2sort_double_float_float_t;

static int cmp_double_float_float(const void *p1, const void *p2) {
    const t2sort_double_float_float_t * restrict k1=p1;
    const t2sort_double_float_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_float_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_double_float_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; float key2; int64_t key3; } t2sort_double_float_int64_t_t;

static int cmp_double_float_int64_t(const void *p1, const void *p2) {
    const t2sort_double_float_int64_t_t * restrict k1=p1;
    const t2sort_double_float_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_float_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_double_float_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; float key2; double key3; } t2sort_double_float_double_t;

static int cmp_double_float_double(const void *p1, const void *p2) {
    const t2sort_double_float_double_t * restrict k1=p1;
    const t2sort_double_float_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_float_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        float * restrict k2 = (float *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_double_float_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int64_t key2; } t2sort_double_int64_t_t;

static int cmp_double_int64_t(const void *p1, const void *p2) {
    const t2sort_double_int64_t_t * restrict k1=p1;
    const t2sort_double_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_double_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        t2sort_double_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int64_t key2; int32_t key3; } t2sort_double_int64_t_int32_t_t;

static int cmp_double_int64_t_int32_t(const void *p1, const void *p2) {
    const t2sort_double_int64_t_int32_t_t * restrict k1=p1;
    const t2sort_double_int64_t_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int64_t_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_double_int64_t_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int64_t key2; float key3; } t2sort_double_int64_t_float_t;

static int cmp_double_int64_t_float(const void *p1, const void *p2) {
    const t2sort_double_int64_t_float_t * restrict k1=p1;
    const t2sort_double_int64_t_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int64_t_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_double_int64_t_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int64_t key2; int64_t key3; } t2sort_double_int64_t_int64_t_t;

static int cmp_double_int64_t_int64_t(const void *p1, const void *p2) {
    const t2sort_double_int64_t_int64_t_t * restrict k1=p1;
    const t2sort_double_int64_t_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int64_t_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_double_int64_t_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; int64_t key2; double key3; } t2sort_double_int64_t_double_t;

static int cmp_double_int64_t_double(const void *p1, const void *p2) {
    const t2sort_double_int64_t_double_t * restrict k1=p1;
    const t2sort_double_int64_t_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_int64_t_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        int64_t * restrict k2 = (int64_t *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_double_int64_t_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; double key2; } t2sort_double_double_t;

static int cmp_double_double(const void *p1, const void *p2) {
    const t2sort_double_double_t * restrict k1=p1;
    const t2sort_double_double_t * restrict k2=p2;
    if(k1->key1==k2->key1)
        return (k1->key2-k2->key2);
    return (k1->key1-k2->key1);
}


static void cpy_double_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        t2sort_double_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; double key2; int32_t key3; } t2sort_double_double_int32_t_t;

static int cmp_double_double_int32_t(const void *p1, const void *p2) {
    const t2sort_double_double_int32_t_t * restrict k1=p1;
    const t2sort_double_double_int32_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_double_int32_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int32_t * restrict k3 = (int32_t *)(p+kd[2].offset);
        t2sort_double_double_int32_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; double key2; float key3; } t2sort_double_double_float_t;

static int cmp_double_double_float(const void *p1, const void *p2) {
    const t2sort_double_double_float_t * restrict k1=p1;
    const t2sort_double_double_float_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_double_float(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        float * restrict k3 = (float *)(p+kd[2].offset);
        t2sort_double_double_float_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; double key2; int64_t key3; } t2sort_double_double_int64_t_t;

static int cmp_double_double_int64_t(const void *p1, const void *p2) {
    const t2sort_double_double_int64_t_t * restrict k1=p1;
    const t2sort_double_double_int64_t_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_double_int64_t(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        int64_t * restrict k3 = (int64_t *)(p+kd[2].offset);
        t2sort_double_double_int64_t_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

typedef struct { t2_pay_t pay; double  key1; double key2; double key3; } t2sort_double_double_double_t;

static int cmp_double_double_double(const void *p1, const void *p2) {
    const t2sort_double_double_double_t * restrict k1=p1;
    const t2sort_double_double_double_t * restrict k2=p2;
    if(k1->key1==k2->key1) {
        if(k1->key2==k2->key2) 
            return k1->key3-k2->key3;
        return (k1->key2-k2->key2);
    }
    return (k1->key1-k2->key1);
}


static void cpy_double_double_double(void * restrict p, int l, int n, const t2sort_key_def_t *kd, void * restrict pk) {
#pragma GCC ivdep
    for(int i=0; i<n; i++, p+=l) {
        double * restrict k1 = (double *)(p+kd[0].offset);
        double * restrict k2 = (double *)(p+kd[1].offset);
        double * restrict k3 = (double *)(p+kd[2].offset);
        t2sort_double_double_double_t * restrict k = pk;
        k[i].key1 = *k1; k[i].key2 = *k2; k[i].key3 = *k3; k[i].pay.ptr = p;
    } }

static int siz_types[] = {
sizeof(t2sort_int32_t_t), sizeof(t2sort_int32_t_int32_t_t), sizeof(t2sort_int32_t_int32_t_int32_t_t), sizeof(t2sort_int32_t_int32_t_float_t), sizeof(t2sort_int32_t_int32_t_int64_t_t), sizeof(t2sort_int32_t_int32_t_double_t), sizeof(t2sort_int32_t_float_t), sizeof(t2sort_int32_t_float_int32_t_t), sizeof(t2sort_int32_t_float_float_t), sizeof(t2sort_int32_t_float_int64_t_t), sizeof(t2sort_int32_t_float_double_t), sizeof(t2sort_int32_t_int64_t_t), sizeof(t2sort_int32_t_int64_t_int32_t_t), sizeof(t2sort_int32_t_int64_t_float_t), sizeof(t2sort_int32_t_int64_t_int64_t_t), sizeof(t2sort_int32_t_int64_t_double_t), sizeof(t2sort_int32_t_double_t), sizeof(t2sort_int32_t_double_int32_t_t), sizeof(t2sort_int32_t_double_float_t), sizeof(t2sort_int32_t_double_int64_t_t), sizeof(t2sort_int32_t_double_double_t), sizeof(t2sort_float_t), sizeof(t2sort_float_int32_t_t), sizeof(t2sort_float_int32_t_int32_t_t), sizeof(t2sort_float_int32_t_float_t), sizeof(t2sort_float_int32_t_int64_t_t), sizeof(t2sort_float_int32_t_double_t), sizeof(t2sort_float_float_t), sizeof(t2sort_float_float_int32_t_t), sizeof(t2sort_float_float_float_t), sizeof(t2sort_float_float_int64_t_t), sizeof(t2sort_float_float_double_t), sizeof(t2sort_float_int64_t_t), sizeof(t2sort_float_int64_t_int32_t_t), sizeof(t2sort_float_int64_t_float_t), sizeof(t2sort_float_int64_t_int64_t_t), sizeof(t2sort_float_int64_t_double_t), sizeof(t2sort_float_double_t), sizeof(t2sort_float_double_int32_t_t), sizeof(t2sort_float_double_float_t), sizeof(t2sort_float_double_int64_t_t), sizeof(t2sort_float_double_double_t), sizeof(t2sort_int64_t_t), sizeof(t2sort_int64_t_int32_t_t), sizeof(t2sort_int64_t_int32_t_int32_t_t), sizeof(t2sort_int64_t_int32_t_float_t), sizeof(t2sort_int64_t_int32_t_int64_t_t), sizeof(t2sort_int64_t_int32_t_double_t), sizeof(t2sort_int64_t_float_t), sizeof(t2sort_int64_t_float_int32_t_t), sizeof(t2sort_int64_t_float_float_t), sizeof(t2sort_int64_t_float_int64_t_t), sizeof(t2sort_int64_t_float_double_t), sizeof(t2sort_int64_t_int64_t_t), sizeof(t2sort_int64_t_int64_t_int32_t_t), sizeof(t2sort_int64_t_int64_t_float_t), sizeof(t2sort_int64_t_int64_t_int64_t_t), sizeof(t2sort_int64_t_int64_t_double_t), sizeof(t2sort_int64_t_double_t), sizeof(t2sort_int64_t_double_int32_t_t), sizeof(t2sort_int64_t_double_float_t), sizeof(t2sort_int64_t_double_int64_t_t), sizeof(t2sort_int64_t_double_double_t), sizeof(t2sort_double_t), sizeof(t2sort_double_int32_t_t), sizeof(t2sort_double_int32_t_int32_t_t), sizeof(t2sort_double_int32_t_float_t), sizeof(t2sort_double_int32_t_int64_t_t), sizeof(t2sort_double_int32_t_double_t), sizeof(t2sort_double_float_t), sizeof(t2sort_double_float_int32_t_t), sizeof(t2sort_double_float_float_t), sizeof(t2sort_double_float_int64_t_t), sizeof(t2sort_double_float_double_t), sizeof(t2sort_double_int64_t_t), sizeof(t2sort_double_int64_t_int32_t_t), sizeof(t2sort_double_int64_t_float_t), sizeof(t2sort_double_int64_t_int64_t_t), sizeof(t2sort_double_int64_t_double_t), sizeof(t2sort_double_double_t), sizeof(t2sort_double_double_int32_t_t), sizeof(t2sort_double_double_float_t), sizeof(t2sort_double_double_int64_t_t), sizeof(t2sort_double_double_double_t), };

static int (*cmp_funcs[4+16+64])(const void*, const void*) = {
cmp_int32_t, cmp_int32_t_int32_t, cmp_int32_t_int32_t_int32_t, cmp_int32_t_int32_t_float, cmp_int32_t_int32_t_int64_t, cmp_int32_t_int32_t_double, 
cmp_int32_t_float, cmp_int32_t_float_int32_t, cmp_int32_t_float_float, cmp_int32_t_float_int64_t, cmp_int32_t_float_double, 
cmp_int32_t_int64_t, cmp_int32_t_int64_t_int32_t, cmp_int32_t_int64_t_float, cmp_int32_t_int64_t_int64_t, cmp_int32_t_int64_t_double, 
cmp_int32_t_double, cmp_int32_t_double_int32_t, cmp_int32_t_double_float, cmp_int32_t_double_int64_t, cmp_int32_t_double_double, 
cmp_float, cmp_float_int32_t, cmp_float_int32_t_int32_t, cmp_float_int32_t_float, cmp_float_int32_t_int64_t, cmp_float_int32_t_double, 
cmp_float_float, cmp_float_float_int32_t, cmp_float_float_float, cmp_float_float_int64_t, cmp_float_float_double, 
cmp_float_int64_t, cmp_float_int64_t_int32_t, cmp_float_int64_t_float, cmp_float_int64_t_int64_t, cmp_float_int64_t_double, 
cmp_float_double, cmp_float_double_int32_t, cmp_float_double_float, cmp_float_double_int64_t, cmp_float_double_double, 
cmp_int64_t, cmp_int64_t_int32_t, cmp_int64_t_int32_t_int32_t, cmp_int64_t_int32_t_float, cmp_int64_t_int32_t_int64_t, cmp_int64_t_int32_t_double, 
cmp_int64_t_float, cmp_int64_t_float_int32_t, cmp_int64_t_float_float, cmp_int64_t_float_int64_t, cmp_int64_t_float_double, 
cmp_int64_t_int64_t, cmp_int64_t_int64_t_int32_t, cmp_int64_t_int64_t_float, cmp_int64_t_int64_t_int64_t, cmp_int64_t_int64_t_double, 
cmp_int64_t_double, cmp_int64_t_double_int32_t, cmp_int64_t_double_float, cmp_int64_t_double_int64_t, cmp_int64_t_double_double, 
cmp_double, cmp_double_int32_t, cmp_double_int32_t_int32_t, cmp_double_int32_t_float, cmp_double_int32_t_int64_t, cmp_double_int32_t_double, 
cmp_double_float, cmp_double_float_int32_t, cmp_double_float_float, cmp_double_float_int64_t, cmp_double_float_double, 
cmp_double_int64_t, cmp_double_int64_t_int32_t, cmp_double_int64_t_float, cmp_double_int64_t_int64_t, cmp_double_int64_t_double, 
cmp_double_double, cmp_double_double_int32_t, cmp_double_double_float, cmp_double_double_int64_t, cmp_double_double_double, 
};

static void (*cpy_funcs[4+16+64])(void*,int,int,const t2sort_key_def_t*,void*) = {
cpy_int32_t, cpy_int32_t_int32_t, cpy_int32_t_int32_t_int32_t, cpy_int32_t_int32_t_float, cpy_int32_t_int32_t_int64_t, cpy_int32_t_int32_t_double, 
cpy_int32_t_float, cpy_int32_t_float_int32_t, cpy_int32_t_float_float, cpy_int32_t_float_int64_t, cpy_int32_t_float_double, 
cpy_int32_t_int64_t, cpy_int32_t_int64_t_int32_t, cpy_int32_t_int64_t_float, cpy_int32_t_int64_t_int64_t, cpy_int32_t_int64_t_double, 
cpy_int32_t_double, cpy_int32_t_double_int32_t, cpy_int32_t_double_float, cpy_int32_t_double_int64_t, cpy_int32_t_double_double, 
cpy_float, cpy_float_int32_t, cpy_float_int32_t_int32_t, cpy_float_int32_t_float, cpy_float_int32_t_int64_t, cpy_float_int32_t_double, 
cpy_float_float, cpy_float_float_int32_t, cpy_float_float_float, cpy_float_float_int64_t, cpy_float_float_double, 
cpy_float_int64_t, cpy_float_int64_t_int32_t, cpy_float_int64_t_float, cpy_float_int64_t_int64_t, cpy_float_int64_t_double, 
cpy_float_double, cpy_float_double_int32_t, cpy_float_double_float, cpy_float_double_int64_t, cpy_float_double_double, 
cpy_int64_t, cpy_int64_t_int32_t, cpy_int64_t_int32_t_int32_t, cpy_int64_t_int32_t_float, cpy_int64_t_int32_t_int64_t, cpy_int64_t_int32_t_double, 
cpy_int64_t_float, cpy_int64_t_float_int32_t, cpy_int64_t_float_float, cpy_int64_t_float_int64_t, cpy_int64_t_float_double, 
cpy_int64_t_int64_t, cpy_int64_t_int64_t_int32_t, cpy_int64_t_int64_t_float, cpy_int64_t_int64_t_int64_t, cpy_int64_t_int64_t_double, 
cpy_int64_t_double, cpy_int64_t_double_int32_t, cpy_int64_t_double_float, cpy_int64_t_double_int64_t, cpy_int64_t_double_double, 
cpy_double, cpy_double_int32_t, cpy_double_int32_t_int32_t, cpy_double_int32_t_float, cpy_double_int32_t_int64_t, cpy_double_int32_t_double, 
cpy_double_float, cpy_double_float_int32_t, cpy_double_float_float, cpy_double_float_int64_t, cpy_double_float_double, 
cpy_double_int64_t, cpy_double_int64_t_int32_t, cpy_double_int64_t_float, cpy_double_int64_t_int64_t, cpy_double_int64_t_double, 
cpy_double_double, cpy_double_double_int32_t, cpy_double_double_float, cpy_double_double_int64_t, cpy_double_double_double, 
};

#endif
