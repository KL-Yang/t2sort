#ifndef C_T2SORT_DEBUG_T2SORT
#define C_T2SORT_DEBUG_T2SORT
/**
 * Generate random integer keys in range from kmin to kmax 
 * */
int dbg_gen_key(int kmin, int kmax)
{
    int key;
    key = nearbyint(kmin+(kmax-kmin)*(random()*1.0/RAND_MAX));
    return key;
}

void dbg_gen_data(void *p, int n, size_t len, 
    int gofs, int gmin, int gmax, 
    int sofs, int smin, int smax)
{
    assert(gofs%4==0 && sofs%4==0 && len%4==0);
    assert(gmin<=gmax && gmax<1000 && gmin>=0);
    assert(smin<=smax && smax<1000 && smin>=0);
    int ndat = len/4;
    float *t = (float*)p;
    for(int i=0; i<n; i++) {
        int pkey = dbg_gen_key(gmin, gmax);
        int skey = dbg_gen_key(smin, smax);
        for(int j=0; j<ndat; j++)
            t[j]=pkey+skey*1E-3;    //3digit accuracy
        ((int*)((void*)t+gofs))[0] = pkey;
        ((int*)((void*)t+sofs))[0] = skey;
        t += ndat;
    }
}

void dbg_keys_valid(void *p, int n, int len, int gofs, int sofs)
{
    assert(gofs%4==0 && sofs%4==0 && len%4==0);
    assert(n>=2 && gofs<len && sofs<len && gofs!=sofs);
    void *p0=p, *p1=p+len; int error=0;
    for(int i=0; i<n-1; i++, p0+=len, p1+=len) {
        int pk0 = ((int*)(p0+gofs))[0];
        int sk0 = ((int*)(p0+sofs))[0];
        int pk1 = ((int*)(p1+gofs))[0];
        int sk1 = ((int*)(p1+sofs))[0];
        if(((pk0==pk1) && sk0>sk1) || (pk0>pk1)) {
                printf("Order is wrong @ %d <%d,%d> vs <%d,%d>!\n",
                        i, pk0, sk0, pk1, sk1);
                error++;
        } }
    if(error)
        abort();
}

void dbg_keys_print(void *p, int n, int len, int gofs, int sofs)
{
    assert(gofs%4==0 && sofs%4==0 && len%4==0);
    assert(n>=2 && gofs<len && sofs<len && gofs!=sofs);
    for(int i=0; i<n; i++, p+=len) {
        int pk = ((int*)(p+gofs))[0];
        int sk = ((int*)(p+sofs))[0];
        printf("[%4d] key <%3d,%3d>\n", i, pk, sk);
    }
}

void dbg_data_valid(void *p, int n, int len, int gofs, int sofs)
{
    int error=0;
    for(int i=0; i<n; i++, p+=len) {
        int pk = ((int*)(p+gofs))[0];
        int sk = ((int*)(p+sofs))[0];
        float val = pk+sk*1E-3;
        for(int j=0; j<len; j+=4)
            if(j!=gofs && j!=sofs) 
                if(((float*)(p+j))[0]!=val)
                    error++;
    }
    if(error) {
        printf("data corruption found! error=%d\n", error);
        abort();
    }
}

void dbg_ablock_check(t2sort_t *h, void *buff, int n)
{
    dbg_keys_valid(buff, n, h->trlen, h->kdef[0].offset,
        h->kdef[1].offset);
    //dbg_keys_print(buff, n, h->trlen, h->kdef[0].offset,
    //    h->kdef[1].offset);
    dbg_data_valid(buff, n, h->trlen, h->kdef[0].offset,
        h->kdef[1].offset);
}

void dbg_blocks_check(t2sort_t *h)
{
    int bntr = h->wpntr*h->wioq;
    void *buff = malloc(bntr*h->trlen);
    void *pkey = malloc(bntr*h->klen);
    for(int64_t i=0, n; i<h->nkey; i+=bntr) {
        n = MIN(bntr, h->nkey-i);
        pread(h->fd, buff, n*h->trlen, i*h->trlen);
        h->func_cpy_key(buff, h->trlen, n, h->kdef, pkey);
        dbg_ablock_check(h, buff, n);
    }
    free(buff);
    free(pkey);
}

#endif
