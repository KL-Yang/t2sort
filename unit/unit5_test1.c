#include "common.h"
#include "../t2sort.h"
#include "../gentype_gen.h"

#define TRLEN   (1223*sizeof(float))
#define GKOFS   0
#define SKOFS   4
#define TESTFD  "gendata1.dat"
#define MB      (1024L*1024L)
int main()
{
    int trlen = TRLEN, nkey = 2, bsize=60, wioq = 4;
    int flag=0, batch=500, nread;
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
    //t2sort_reset(sort);
    //t2sort_read(sort, buff, batch);
    //or readraw();

    t2sort_destroy(sort);
    free(buff);
    printf("runs to the end!\n");
    return 0;
}
