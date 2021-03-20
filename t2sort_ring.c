#ifndef C_T2SORT_RING_T2SORT
#define C_T2SORT_RING_T2SORT
typedef struct {
    int64_t ipos;   //current without wrap
    int64_t zpos;   //capability without wrap
    int64_t wrap;
    int trlen, spill;
} t2_ring_t;

static t2_ring_t *ring_init(int trln, int wrap_ntr)
{
    t2_ring_t *r = calloc(1, sizeof(t2_ring_t));
    r->wrap = r->zpos = ((int64_t)wrap_ntr)*trln;
    r->trlen = trln;
    return r;
}
static void ring_destroy(t2_ring_t *r)
{
    free(r);
}

static int64_t ring_malloc(t2_ring_t *r, int *ntr)
{
    int xcap = r->zpos-r->ipos;
    int bcap = r->wrap-r->zpos%r->wrap;
    xcap = MIN(xcap, bcap);
    *ntr = MIN((*ntr), xcap/r->trlen);
    int64_t ipos = r->ipos;
    r->ipos += (*ntr)*r->trlen;
    return ipos;
}
static void
ring_return(t2_ring_t *r, int64_t ipos, int64_t size)
{
    assert(ipos+size<=r->ipos);
    assert(ipos+r->wrap>=r->zpos);
    if(ipos+r->wrap-r->zpos>=PAGE_SIZE) {
        printf("%s: Page waste found!\n", __func__);
        abort();
    }
    r->zpos = ipos+size+r->wrap;
}
static int64_t  //page aligned planing
ring_ralign(t2_ring_t *r, int ftr, int *ntr, int *ext0, int *ext1)
{
    *ext0 = t2_ext0(ftr*r->trlen, &r->ipos, r->spill, r->wrap);
    int ncap = t2_rcap(&r->ipos, *ext0, r->trlen, r->wrap);
    (*ntr) = MIN(ncap, (*ntr));
    int64_t mz=r->ipos-(*ext0)+(*ntr)*r->trlen;
    *ext1 = t2_ext1(mz);
    return r->ipos;
}
#endif
