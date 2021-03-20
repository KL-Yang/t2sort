#ifndef C_T2SORT_ALIGN_T2SORT
#define C_T2SORT_ALIGN_T2SORT
/**
 *       ma                                  mz
 *        |f-------------------------------n->|
 *        v Ma                                v    Mz
 *        --|---------|---------|---------|----=====|
 *       ext0            page              ext1     ^ xbase
 * */
static int t2_ext0(int64_t addr, int64_t *base, int ext1, int64_t wrap)
{   
    if((*base)%wrap==0) //update dummy ext1 value!
        ext1=PAGE_SIZE;
    int ext0=(PAGE_SIZE-addr%PAGE_SIZE)%PAGE_SIZE;
    if((ext0+ext1>PAGE_SIZE)) {
        *base += PAGE_SIZE; //extra gap
        if((*base)%wrap==0 && ext0>0)   //boundary!
            *base += PAGE_SIZE;
    }
    return ext0;
}
static int t2_ext1(int64_t addr)
{   return (addr-1)%PAGE_SIZE+1; }

static int t2_rcap(int64_t *xb, int ext0, int trln, int64_t wrap)
{   
    int ncap, size;
    //mgap = (ftr*trln)%PAGE_SIZE;
    size = wrap-(*xb)%wrap+ext0;
    if((ncap=size/trln)<=0) {
        *xb += (wrap-(*xb)%wrap)%wrap;
        if(ext0>0)
            *xb += PAGE_SIZE;
        ncap = t2_rcap(xb, ext0, trln, wrap);
    } assert(ncap>0);
    return ncap;
}

static void //count the block-block contribution
t2_scan(const void *pkey, int nkey, int klen, int bntr,
    int nblk, int *nn)
{
    memset(nn, 0, nblk*nblk*sizeof(int));
    for(int i=0, xntr; i<nkey; i+=bntr, nn+=nblk) {
        xntr = MIN(bntr, nkey-i);
        for(int j=0; j<xntr; j++, pkey+=klen)
            nn[((t2_pay_t*)pkey)->bpi.blk]++;
    }
}

static int
t2_lque(t2_que_t *xque, int *n, int nblk, int bntr, int trln, 
    int pntr, int xwrap) 
{
    int f[nblk], x=0; int64_t xbase=0;
    memset(f, 0, nblk*sizeof(int));
    for(int j=0, ext0=0, ext1=0; j<nblk; j++, n+=nblk)
        for(int i=0, ncap=0; i<nblk; i++)
            while(n[i]!=0) {
                memset(&xque[x], 0, sizeof(t2_que_t));
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                ext0 = t2_ext0(f[i]*trln, &xbase, ext1, xwrap);
                if(ext0) assert(xbase%xwrap!=0);
                ncap = t2_rcap(&xbase, ext0, trln, xwrap);
                if(ext0) assert(xbase%xwrap!=0);
                xque[x].ntr = MIN(ncap, MIN(pntr, n[i]));
                xque[x].Ma  = xbase; //one page gap
                xque[x].ma  = xque[x].Ma-ext0;
                xque[x].mz  = xque[x].ma+xque[x].ntr*trln;
                ext1 = t2_ext1(xque[x].mz);
                xque[x].Mz  = xque[x].mz-ext1+PAGE_SIZE;

                xbase = xque[x].Mz;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                x++;
            } 
    return x;
}

static t2_que_t *
t2_rque(t2_que_t *pool, t2_que_t *list, int nque) 
{
    t2_que_t *xque = calloc(nque, sizeof(t2_que_t));
    memcpy(xque, list, nque*sizeof(t2_que_t));
    for(int i=0; i<nque; i++) {
        xque[i].id = i;
        xque_enque(pool, &xque[i]);
    }
    return xque;
}

static int64_t t2_align_ge(int64_t seek)
{   return seek+(PAGE_SIZE-seek%PAGE_SIZE)%PAGE_SIZE;   }

static void t2_read_submit(t2sort_t *h, t2_que_t *r)
{
    int64_t offa, offz; t2_que_t *x;
    while(r->next!=r && //read queue not finished
        h->DONe.next->ma+h->_wrap>=r->next->Mz) {
        x = xque_deque(r);
        offa = t2_align_ge(x->seek*h->trln);
        offz = t2_align_ge((x->seek+x->ntr)*h->trln);
        assert(offz-offa==x->Mz-x->Ma);
        t2_aio_read(&x->aio, h->fd, h->_base+(x->Ma)%h->_wrap, 
                offz-offa, offa);
        assert(offa%PAGE_SIZE==0);
        assert(offz%PAGE_SIZE==0);
        assert(x->Ma%PAGE_SIZE==0);
        xque_enque(&h->wait, x);
    }
}
#endif
