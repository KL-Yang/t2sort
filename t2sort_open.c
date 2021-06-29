#ifndef C_T2SORT_OPEN_T2SORT
#define C_T2SORT_OPEN_T2SORT

#ifdef T2SORT_RHEL6 //For rhel6, aligned_alloc(C11)
static void * aligned_alloc(size_t alignment, size_t size)
{
    void *p = malloc(size);
    if(posix_memalign(&p, alignment, size)!=0) {
        printf("%s(%lu, %lu) Failed!\n", __func__, alignment, size);
        abort();
    }
    return p;
}
#endif

#define LEN_PATH    128
static void t2_scratchname(const char *seed, char *name)
{
    char temp[LEN_PATH];
    time_t t1; struct tm t2; pid_t pid;
    t1 = time(NULL);
    gmtime_r(&t1, &t2);
    pid = getpid();
    snprintf(temp, LEN_PATH, "%s_%02d%02d%02d%02d%02d_%u.delete",
        seed, t2.tm_mon+1, t2.tm_mday, t2.tm_hour, t2.tm_min, 
        t2.tm_sec, pid);
    const char *scrdir=getenv("T2SORT_SCRATCH");
    name[0]='\0';
    if(scrdir!=NULL) {
        strcpy(name, scrdir);
        int n=strlen(scrdir);
        if(name[n-1]!='/')
            strcat(name, "/");
    }
    strcat(name, temp);
}

static void t2_factor(int a, int * restrict f)
{
    int j=0;
    while(a!=1) {
        for(int i=2; i<=a; i++)
            if(a%i==0) {
                a=a/i;
                f[j]=i;
                j++;
                break;
            } };
}
static int t2_multiple(int pagemask, int trln)
{
    int f[32], multiple=(1<<pagemask);
    for(int i=0; i<32; i++)
        f[i]=1;
    t2_factor(trln, f);
    for(int i=0, j=0; i<32; i++)
        if(f[i]==2 && j<pagemask) {
            f[i] = 1;
            j++;
        }
    for(int i=0; i<32; i++)
        multiple*=f[i];
    return multiple;
}
static void xque_enque(t2_que_t *stub, t2_que_t *x)
{
    t2_que_t *tail = stub->prev;
    tail->next = x; x->prev = tail;
    stub->prev = x; x->next = stub;
}
static t2_que_t *xque_deque(t2_que_t *stub)
{
    t2_que_t *head = stub->next;
    stub->next = head->next;
    head->next->prev = stub;
    return head;
}
static void t2_init_blk(t2sort_t *h, int bsiz, int wioq, int trln)
{
    int xsize=t2_multiple(PAGE_MASK, trln);
    int scale=MAX(1, nearbyint(bsiz*1024.0*1024.0/xsize/(1+wioq)));
    h->pntr = scale*(xsize/trln);
    h->bntr = h->pntr*wioq;
}
static void t2_init_scratch(t2sort_t *h, int flag)
{
    char scratchname_k[128];
    t2_scratchname("delete_data", h->fd_name);
    t2_scratchname("delete_head", scratchname_k);
    printf("%s: open scratch (dat=%s, key=%s)\n", __func__, 
            h->fd_name, scratchname_k);
    int oflag = (flag&T2SORT_DIO)?(O_DIRECT):(0);
    h->fd = open(h->fd_name, O_RDWR|O_CREAT|oflag,
            S_IRWXU|S_IRWXG|S_IRWXO);
    h->fd_keys = open(scratchname_k, O_RDWR|O_CREAT, 
                    S_IRWXU|S_IRWXG|S_IRWXO);
    if(!(flag & T2SORT_DEBUG)) {
        remove(h->fd_name);
        remove(scratchname_k);
    }
}

t2sort_h
t2sort_open(int tlen, int ndef, const t2_kdef_t *kdef, 
    int bsiz, int wioq, int flag)
{
    t2sort_t *h = calloc(1, sizeof(t2sort_t));
    h->trln = tlen;
    h->ndef = ndef;
    h->kdef = calloc(ndef, sizeof(t2_kdef_t));
    memcpy(h->kdef, kdef, ndef*sizeof(t2_kdef_t));

    t2_init_blk(h, bsiz, wioq, tlen);
    h->wrap  = h->pntr*(wioq+1);
    h->_base = aligned_alloc(PAGE_SIZE, ((size_t)h->wrap)*tlen);
    printf("%s: bsiz=%dMB pntr=%ld wioq=%d buff=%8.1fMB\n", 
        __func__, bsiz, h->pntr, wioq, 
        nearbyint((h->wrap*tlen)/1024.0/1024.0));

    h->wioq  = wioq;
    h->flag  = flag;
    h->klen  = t2sort_key_size(ndef, kdef);
    h->_xque = calloc((wioq+2), sizeof(t2_que_t));
    h->_temp = malloc(h->trln);
    h->_pkey = malloc(h->bntr*h->klen);
    h->_imap = malloc(h->bntr*sizeof(int));
    h->_pptr = malloc(h->bntr*sizeof(void*));

    t2_init_scratch(h, flag);
    h->func_cmp_key = t2sort_getcmp(ndef, kdef);
    h->func_cpy_key = t2sort_getcpy(ndef, kdef);

    h->wait.prev = h->wait.next = &h->wait;
    h->pool.prev = h->pool.next = &h->pool;
    for(int i=0; i<(wioq+2); i++) 
        xque_enque(&h->pool, &h->_xque[i]);

    return (t2sort_h)h;
}
#endif
