//split must be considered here too!!!

//        |f-------------------------------n->|
//        v                                   v
//        --|---------|---------|---------|----=====|
//        x0            page               x1       ^ xbase
static int t2_align_tail(int64_t faddr)
{   return (PAGE_SIZE-faddr%PAGE_SIZE)%PAGE_SIZE; }
static int t2_align_head(int64_t maddr)
{   return maddr%PAGE_SIZE; }
//static int t2_align_rcap(int64_t maddr, int tlen, int64_t xwrap)
//{   return (xwrap-maddr)/tlen; }
static int t2_align_rcap(int64_t *xbase, int *x1, int x0,
         int trln, int64_t xwrap)
{   
    int ma = (*xbase)-x0, ncap;
    if((*x1)+x0>PAGE_SIZE)
        ma += PAGE_SIZE;    //leave a gap there
    ncap = (xwrap-ma)/trln;
    if(ncap<=0) {
        *xbase = 0;
        *x1 = PAGE_SIZE;
        ncap = t2_align_rcap(xbase, x1, x0, trln, xwrap);
    }
    assert(ncap>0);
    return ncap;
}
//
static t2_que_t *
t2_list_rque2(t2_que_t *head, void *pkey, int nkey, int klen, 
        int bntr, int nblk, int pntr, int tlen)
{
    nblk = ceilf(nkey*1.0f/bntr);
    int f[nblk], n[nblk], x=0; t2_que_t *xque; 
    int64_t xbase=0, xwrap=(bntr+pntr)*tlen;
    int x0=0, x1=0, ncap;
    xque = calloc(2*nblk*nblk+nblk, sizeof(t2_que_t));
    memset(f, 0, nblk*sizeof(int));
    for(int k=0, xntr; k<nkey; k+=bntr) {
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
                xque[x].ntr  = MIN(n[i], pntr);
                //memory range for read!
                x0 = t2_align_tail(f[i]*tlen);
                ncap = t2_align_rcap(&xbase, &x1, x0, tlen, xwrap);
                xque[x].ntr = MIN(ncap, xque[x].ntr);
                xque[x].Ma  = xbase;
                if(x1+x0>PAGE_SIZE)
                    xque[x].Ma = xbase+PAGE_SIZE;
                xque[x].ma = xque[x].Ma-x0;
                xque[x].mz = xque[x].ma+xque[x].ntr*tlen;
                x1 = t2_align_head(xque[x].mz);
                xque[x].Mz = xque[x].mz-x1+PAGE_SIZE;
                if(x1==0)
                    xque[x].Mz = xque[x].mz;
                assert(xque[x].Mz<=xwrap);

                xbase = xque[x].Mz;
                f[i] += xque[x].ntr;
                n[i] -= xque[x].ntr;
                xque_enque(head, &xque[x]);
                x++;
            }
        }
    } assert(x<=2*nblk*nblk+nblk);
    printf("%s: total read queue=%d\n", __func__, x);
    return realloc(xque, x*sizeof(t2_que_t));
}

static void t2_print_queu(t2_que_t *stub, int trln)
{
    t2_que_t *item=stub->next;
    while(item!=stub) {
        printf("%4d BLK[%2d] NTR=%5d [%8ld,%8ld] [%8ld,%8ld]\n",
            item->id, item->blk, item->ntr, item->Ma, item->Mz,
            item->ma, item->mz);
        assert(item->Ma%PAGE_SIZE==0);
        assert(item->Mz%PAGE_SIZE==0);
        assert(item->Ma>=item->ma);
        assert(item->Mz>=item->mz);
        assert(item->mz-item->ma==item->ntr*trln);
        item=item->next;
    }
}
