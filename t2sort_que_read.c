/**
 *       ma                                  mz
 *        |f-------------------------------n->|
 *        v Ma                                v    Mz
 *        --|---------|---------|---------|----=====|
 *       ext0            page              ext1     ^ xbase
 * */
static int t2_ext0(int64_t addr)
{   return (PAGE_SIZE-addr%PAGE_SIZE)%PAGE_SIZE; }
static int t2_ext1(int64_t addr)
{   return (addr-1)%PAGE_SIZE+1; }

static int t2_rcap(int64_t *xb, int ftr, int trln, int64_t wrap)
{   
    int ncap, size, mgap;
    mgap = (ftr*trln)%PAGE_SIZE;
    size = wrap-(*xb)%wrap-mgap;
    if((ncap=size/trln)<=0) {
        *xb += (wrap-(*xb)%wrap)%wrap;
        ncap = t2_rcap(xb, ftr, trln, wrap);
    } assert(ncap>0);
    return ncap;
}
/*
static int64_t
t2_addr(int64_t xbase, int64_t xwrap, int first, int *ninst, 
        int trlen)
{
    int ncap = xwrap-xbase%xwrap-first*trlen%PAGE_SIZE;
    return ncap;
} */

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
} /*
static void //create a memory list
t2_list(int *nn, int nblk, int tlen)
{
    int nque=0, f[nblk]; memset(f, 0, nblk*sizeof(float));
    for(int k=0; k<nblk; k++, nn+=nblk) 
        for(int i=0; i<nblk; i++) {
            ext0 = t2_ext0(f[i]*tlen);
            ncap = t2_rcap(&xbase, f[i], tlen, xwrap);
        }
} */
/*
static t2_que_t *
t2_rque(t2_que_t *head, int *n, int nblk, int trln, int wrap) 
{
    t2_que_t *xque; 
    int f[nblk], x=0, ncap, nque; 
    int64_t xbase=PAGE_SIZE;
    nque = MAX(nblk*(bntr/pntr+1)+nblk, 2*nblk*nblk+nblk);
    xque = calloc(nque, sizeof(t2_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0; k<nblk; k++, n+=nblk) {
        for(int i=0; i<nblk; i++) {
            while(n[i]!=0) {
                //each block head @ f[i]
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                xque[x].id   = x;
                //memory range for read!
                ext0 = t2_ext0(f[i]*tlen);
                ncap = t2_rcap(&xbase, ext0, tlen, wrap);
                xque[x].ntr = MIN(ncap, MIN(pntr, n[i]));
                xque[x].Ma  = xbase; //one page gap
                xque[x].ma  = xque[x].Ma-ext0;
                xque[x].mz  = xque[x].ma+xque[x].ntr*tlen;
                xque[x].Mz  = xque[x].mz;
                if((ext1=xque[x].mz%PAGE_SIZE)!=0)
                    xque[x].Mz = xque[x].mz-ext1+PAGE_SIZE;

                assert(xque[x].Mz>=xque[x].mz);
                assert((xque[x].Mz-1)/wrap==xque[x].mz/wrap);
                t2_que_t *item=&xque[x];
                assert((item->ma-1)/wrap==(item->Mz-1)/wrap);
                if((xbase=xque[x].Mz+PAGE_SIZE)%wrap==0)
                    xbase+=PAGE_SIZE;   //start new wrap
                assert(xbase%wrap!=0);
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                x++;
            }
        }
    } assert(x<=nque);
    printf("%s: total read queue=%d\n", __func__, x);
    return realloc(xque, x*sizeof(t2_que_t));
    //TODO: realloc is very dangerous here as it uses
    //pointer for the double linked list!!!
} */

static t2_que_t *
t2_list_rque2(t2_que_t *head, void *pkey, int nkey, int klen, 
        int bntr, int nblk, int pntr, int tlen)
{
    t2_que_t *xque; 
    int f[nblk], n[nblk], x=0, ncap, nque; 
    //int64_t xbase=PAGE_SIZE, xwrap=(bntr+pntr)*tlen;
    int64_t xbase=0, xwrap=(bntr+pntr)*tlen;
    nque = MAX(nblk*(bntr/pntr+1)+nblk, 2*nblk*nblk+nblk);
    xque = calloc(nque, sizeof(t2_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0, xntr, ext0=0, ext1=0; k<nkey; k+=bntr) {
        xntr = MIN(bntr, nkey-k);
        memset(n, 0, nblk*sizeof(int));
        for(int j=0; j<xntr; j++, pkey+=klen)
            n[((t2_pay_t*)pkey)->bpi.blk]++;
        for(int i=0; i<nblk; i++) {
            while(n[i]!=0) {
                //each block head @ f[i]
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                xque[x].id   = x;
                //memory range for read!
                ext0 = t2_ext0(f[i]*tlen);
                ncap = t2_rcap(&xbase, f[i], tlen, xwrap);
                xque[x].ntr = MIN(ncap, MIN(pntr, n[i]));
                xque[x].Ma  = xbase; //one page gap
                if(ext1+ext0>PAGE_SIZE || ((xbase%xwrap==0)&&ext0>0))
                    xque[x].Ma += PAGE_SIZE;
                xque[x].ma  = xque[x].Ma-ext0;
                if(x>0) {
                    if(xque[x].ma/xwrap==xque[x-1].mz/xwrap) {
                        if(xque[x].ma-xque[x-1].mz>PAGE_SIZE)
                            abort();
                        if(xque[x].ma<xque[x-1].mz)
                            abort();
                    }
                }
                xque[x].mz  = xque[x].ma+xque[x].ntr*tlen;
                ext1 = t2_ext1(xque[x].mz);
                xque[x].Mz = xque[x].mz-ext1+PAGE_SIZE;

                //NOTE: here ext1 maps to 1->PAGE_SIZE;
                //ext0 maps to 0->PAGE_SIZE-1

                assert(xque[x].Mz>=xque[x].mz);
                assert((xque[x].Mz-1)/xwrap==xque[x].mz/xwrap);
                t2_que_t *item=&xque[x];
                assert((item->ma-1)/xwrap==(item->Mz-1)/xwrap);
                xbase = xque[x].Mz;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                x++;
            }
        }
    } assert(x<=nque);
    printf("%s: total read queue=%d\n", __func__, x);
    return realloc(xque, x*sizeof(t2_que_t));
}

static void t2_print_queu(t2_que_t *stub, int trln, int wrap)
{
    t2_que_t *item=stub->next;
    int xwrap = wrap*trln;
    while(item!=stub) {
        printf("%4d BLK[%2d] NTR=%5d [%16ld,%16ld] [%16ld,%16ld]\n",
            item->id, item->blk, item->ntr, item->Ma, item->Mz,
            item->ma, item->mz);
        assert((item->ma-1)/xwrap==(item->Mz-1)/xwrap);
        assert(item->Ma%PAGE_SIZE==0);
        assert(item->Mz%PAGE_SIZE==0);
        assert(item->Ma>=item->ma);
        assert(item->Mz>=item->mz);
        assert(item->mz-item->ma==item->ntr*trln);
        if(item->next!=stub) {
            assert(item->mz<=item->next->ma);
            assert(item->Mz<=item->next->Ma);
            if(item->next->ma-item->mz >=PAGE_SIZE && 
                (item->next->ma/xwrap == item->mz/xwrap)) {
                printf("%s: waste a page!\n", __func__);
            }
        }
        item=item->next;
    }
}

static int64_t t2_align_ge(int64_t seek)
{   return seek+(PAGE_SIZE-seek%PAGE_SIZE)%PAGE_SIZE;   }

static void t2_read_submit(t2sort_t *h, t2_que_t *r)
{
    int64_t offa, offz; t2_que_t *x;
    while(r->next!=r && //read queue not finished
        h->DONe.next->ma+h->_wrap>=r->next->Mz) {
        x = xque_deque(r);
        printf("%s: id=%3d ntr=%d\n", __func__, x->id, x->ntr);
        fflush(0);
        offa = t2_align_ge(x->seek*h->trln);
        offz = t2_align_ge((x->seek+x->ntr)*h->trln);
        assert(offz-offa==x->Mz-x->Ma);
        t2_aio_read(&x->aio, h->fd, h->_base+(x->Ma)%h->_wrap, 
                offz-offa, offa);
        xque_enque(&h->wait, x);
    }
}
