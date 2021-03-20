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
}

static int
t2_lque(t2_que_t *xque, int *n, int nblk, int bntr, int trln, 
    int pntr, int xwrap) 
{   //give it _base as temp buff buffer as 
    int f[nblk], x=0; int64_t xbase=0;
    memset(f, 0, nblk*sizeof(int));
    for(int j=0, ext0=0, ext1=0; j<nblk; j++, n+=nblk)
        for(int i=0, ncap=0; i<nblk; i++)
            while(n[i]!=0) {
                memset(&xque[x], 0, sizeof(t2_que_t));
                xque[x].blk  = i;
                xque[x].seek = i*bntr+f[i];
                ext0 = t2_ext0(f[i]*trln);
                ncap = t2_rcap(&xbase, f[i], trln, xwrap);
                xque[x].ntr = MIN(ncap, MIN(pntr, n[i]));
                xque[x].Ma  = xbase; //one page gap
                if(ext1+ext0>PAGE_SIZE || ((xbase%xwrap==0)&&ext0>0))
                    xque[x].Ma += PAGE_SIZE;
                xque[x].ma  = xque[x].Ma-ext0;
                xque[x].mz  = xque[x].ma+xque[x].ntr*trln;
                ext1 = t2_ext1(xque[x].mz);
                xque[x].Mz = xque[x].mz-ext1+PAGE_SIZE;
                xbase = xque[x].Mz;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                x++;
            } printf("%s: total read queue=%d\n", __func__, x);
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

static void t2_print_queu(t2_que_t *stub, int trln, int wrap)
{
    t2_que_t *item=stub->next;
    int xwrap = wrap*trln;
    while(item!=stub) {
        printf("%4d BLK[%2d] NTR=%5d [%16ld,%16ld] [%16ld,%16ld] seek=%8ld\n",
            item->id, item->blk, item->ntr, item->Ma, item->Mz,
            item->ma, item->mz, item->seek);
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
