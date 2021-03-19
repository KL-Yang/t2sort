//split must be considered here too!!!

//        |f-------------------------------n->|
//        v                                   v
//        --|---------|---------|---------|----=====|
//        x0            page               x1       ^ xbase
static int t2_extra_tail(int64_t faddr)
{   return (PAGE_SIZE-faddr%PAGE_SIZE)%PAGE_SIZE; }

static int t2_extra_head(int64_t maddr)
{   return maddr%PAGE_SIZE; }

//xbase is not wrapped!
static int t2_align_rcap(int64_t *xbase, int *x1, 
        int x0, int trln, int64_t xwrap)
{   
    int64_t oldx = *xbase;
    int ma = (*xbase)%xwrap-x0; assert(ma>=0);
    int ncap = (xwrap-ma)/trln;
    if(ncap<=0) {
        *xbase += (xwrap-(*xbase)%xwrap)%xwrap; //next block
        assert((*xbase)%xwrap==0);
        *xbase += PAGE_SIZE;
        printf("%s: ncap=0 xbase %ld -> %ld\n", __func__, 
                oldx, *xbase); fflush(0);
        *x1 = 0;
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
    int x0=0, x1=0, ncap, nque;
    nque = MAX(nblk*(bntr/pntr+1)+nblk, 2*nblk*nblk+nblk);
    xque = calloc(nque, sizeof(t2_que_t));
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
                xque[x].seek = i*bntr+f[i]; //TODO-->
                xque[x].id   = x;
                //memory range for read!
                x0 = t2_extra_tail(f[i]*tlen);
                printf("%s-1: queue %2d xbase=%14ld\n",
                     __func__, x, xbase);
                if(x0!=0) {
                    if(xbase%xwrap==0) {
                        xbase += PAGE_SIZE;     //add gap!
                        printf("%s  : wrap @+4096=%ld!\n", __func__, xbase);
                        x1 = 0;
                    } /* else if(x1+x0<=PAGE_SIZE) {
                        xbase -= PAGE_SIZE;
                        if(xbase%xwrap==0 && x0!=0)
                            xbase += PAGE_SIZE;
                        //printf("%s  : merg @-4096=%ld x1=%4d x0=%4d!\n",
                        //     __func__, xbase, x1, x0);
                    } */
                }
                printf("%s-2: queue %2d xbase=%14ld\n",
                     __func__, x, xbase);
                ncap = t2_align_rcap(&xbase, &x1, x0, tlen, xwrap);
                xque[x].ntr  = MIN(ncap, MIN(pntr, n[i]));
                xque[x].Ma   = xbase; //one page gap
                xque[x].ma = xque[x].Ma-x0;
                xque[x].mz = xque[x].ma+xque[x].ntr*tlen;
                x1 = t2_extra_head(xque[x].mz);
                if(x1==0)
                    xque[x].Mz = xque[x].mz;
                else 
                    xque[x].Mz = xque[x].mz-x1+PAGE_SIZE;

                assert(xque[x].Mz>=xque[x].mz);
                assert((xque[x].Mz-1)/xwrap==xque[x].mz/xwrap);
                t2_que_t *item=&xque[x];
                assert((item->ma-1)/xwrap==(item->Mz-1)/xwrap);
                printf("%s-3: x0=%4d Ma=%14ld Mz=%14ld x1=%4d\n",
                   __func__, x0, xque[x].Ma, xque[x].Mz, x1);
                xbase = xque[x].Mz+PAGE_SIZE;
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
