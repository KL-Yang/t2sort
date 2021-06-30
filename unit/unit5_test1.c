#include "common.h"
#include "../t2sort.h"
#include "../gentype_gen.h"

static ssize_t safe_pread(int fd, void *buf, size_t count, off_t offset)
{
    size_t left=count, batch=256*1024*1024; //256MB
    while(left>0) {
        ssize_t r = MIN(left, batch);
        ssize_t x = pread(fd, buf, r, offset);
        if(x<0) {
    	    int e = errno;
            printf("%s: something wrong with reading file\n", __func__);
            printf("%s: errno=%d %s\n", __func__, e, strerror(e));
            abort();
        }
        buf += x;
        offset += x;
        left -= x;
    };
    return count;
}

void check_file_order(int fd, int trlen, t2sort_key_def_t *kdef)
{
    void *wbuff; int64_t ninst, batch=1000;
    off_t length = lseek(fd, 0, SEEK_END);
    ninst = length/trlen;  assert(length%trlen==0);
    wbuff  = calloc(batch, trlen);
    
    for(int64_t i=0; i<ninst; i+=batch-1) {
        int64_t r = MIN(batch, ninst-i);
        ssize_t x = safe_pread(fd, wbuff, r*trlen, i*trlen);
        assert(x==r*trlen);
	dbg_keys_valid(wbuff, r, trlen, kdef[0].offset, kdef[1].offset);
	dbg_data_valid(wbuff, r, trlen, kdef[0].offset, kdef[1].offset);
      //dbg_keys_print(wbuff, r, trlen, kdef[0].offset, kdef[1].offset);
    };
    free(wbuff);
    printf("%s() done!\n", __func__);
}

int main(int argc, char *argv[])
{
    if(argc!=8) {
        printf("Usage: %s trlen bsize npile filein fileout dio check\n"
               "   trlen   - trace length in number of floats\n"
               "   bsize   - prefered buffer size in MiB\n"
               "   npile   - number of piles per block\n"
               "   filein  - input data file name\n"
               "   fileout - output data file name\n"
               "   dio     - 1 dio, 0 not dio\n"
	       "   check   - 1 check, 0 not check\n", argv[0]);
        exit(1);
    }
    int trlen, bsize, npile, dflag, check; const char *fname, *fsort;
    trlen = atoi(argv[1])*sizeof(float);
    bsize = atoi(argv[2]);
    npile = atoi(argv[3]);  //piles per block
    fname = argv[4];
    fsort = argv[5];
    dflag = atoi(argv[6]);
    check = atoi(argv[7]);

    t2sort_key_def_t kdef[] = {
        {.offset=0, .type=T2SORT_INT32_T, .order=1},
        {.offset=4, .type=T2SORT_INT32_T, .order=1}
    }; 
    int flag=0, fdi, fdo, batch=500, ninst=0, nread; void *buf;
    if(dflag==1) flag |= T2SORT_DIO;

    t2sort_h sort; //flag |= T2SORT_DIO;
    sort = t2sort_open(trlen, 2, kdef, bsize, npile, flag);

    fdi = open(fname, O_RDWR);
    fdo = open(fsort, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    assert(fdi>=0 && fdo>=0);

    buf = calloc(batch, trlen);
    do {
        nread = read(fdi, buf, batch*trlen);
        assert(nread%trlen==0 && nread>=0);
        nread = nread/trlen;
        t2sort_write(sort, buf, nread);
        ninst += nread;
    } while(nread>0);
    printf("Total read instance %d\n", ninst);
    close(fdi);

    t2sort_sort(sort);
    while(ninst>0) {
        nread = t2sort_read(sort, buf, batch);
        //printf(" nread=%6d left=%8d\n", nread, ninst);
        write(fdo, buf, nread*trlen);
        ninst-= nread;
    }
    t2sort_close(sort);
    
    if(check==1)
        check_file_order(fdo, trlen, kdef);

    close(fdo);
    free(buf);
    printf("Runs to the end!\n");
    return 0;
}
