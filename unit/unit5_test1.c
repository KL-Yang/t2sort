#include "common.h"
#include "../t2sort.h"
#include "../gentype_gen.h"

void 
check_file_order(int fd, int ninst, int trlen, 
        t2sort_key_def_t *kdef)
{
    void *buff;
    buff = calloc(ninst, trlen);
    pread(fd, buff, ninst*trlen, 0);
    dbg_keys_valid(buff, ninst, trlen, 
            kdef[0].offset, kdef[1].offset);
    dbg_data_valid(buff, ninst, trlen, 
            kdef[0].offset, kdef[1].offset);
    dbg_keys_print(buff, ninst, trlen, 
            kdef[0].offset, kdef[1].offset);
    free(buff);
}

#define TRLEN   (1223*sizeof(float))
#define NINST   100231  //from unit4
#define GKOFS   0
#define SKOFS   4
#define TESTFD  "gendata1.dat"
#define TESTOU  "unit5_gendata1.dat"
#define MB      (1024L*1024L)
int main()
{
    int trlen = TRLEN, nkey = 2, bsize=60, wioq = 4;
    int flag=0, batch=500, nread, ninst=NINST;
    t2sort_key_def_t keys[] = {
        {.offset=GKOFS, .type=T2SORT_INT32_T, .order=1},
        {.offset=SKOFS, .type=T2SORT_INT32_T, .order=1}
    }; 
    t2sort_h sort;
    sort = t2sort_init(trlen, nkey, keys, bsize, wioq, flag);

    int fd = open(TESTFD, O_RDWR); assert(fd>=0);
    void *buff = calloc(batch, TRLEN);
    do {
        nread = read(fd, buff, batch*TRLEN);
        assert(nread%TRLEN==0);
        nread = nread/TRLEN;
        t2sort_write(sort, buff, nread);
    } while(nread>0);
    close(fd);

    //open and read file, call t2sort_dump()
    t2sort_sort(sort);

    int left=ninst;
    fd = open(TESTOU, O_RDWR|O_CREAT,
                S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    while(left>0) {
        nread = t2sort_read(sort, buff, batch);
        printf(" nread=%6d left=%8d\n", nread, left);
        write(fd, buff, nread*TRLEN);
        left -= nread;
    }
    t2sort_destroy(sort);
    
    check_file_order(fd, ninst, TRLEN, keys);

    close(fd);
    free(buff);
    printf("runs to the end!\n");
    return 0;
}
