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
{   free(r); } 

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
static void ring_return(t2_ring_t *r, int64_t ipos, int64_t size)
{
    assert(ipos+size<=r->ipos);
    assert(ipos+r->wrap==r->zpos);
    r->zpos = ipos+size+r->wrap;
}
#endif
