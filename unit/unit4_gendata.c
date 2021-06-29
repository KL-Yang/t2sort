#include "common.h"
#include "../t2sort_debug.c"

#define GKOFS   0
#define GKMIN   1
#define GKMAX   200
#define SKOFS   4
#define SKMIN   1
#define SKMAX   900 

int main(int argc, char *argv[])
{
    if(argc!=5) {
        printf("Usage: %s trlen ninst rseed filename\n"
               "   trlen - trace length in number of floats\n"
               "   ninst - number of instance\n"
               "   rseed - random number seeds\n"
               "   filename - output file name\n", argv[0]);
        exit(1);
    }
    const char *fname; void *buf;
    unsigned int rseed; int ninst, trlen, fdd, batch=10000;
    trlen = atoi(argv[1])*sizeof(float);
    ninst = atoi(argv[2]);
    rseed = atoi(argv[3]);
    fname = argv[4];

    srandom(rseed);
    buf = calloc(batch, trlen);
    fdd = open(fname, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    for(int i=0, j=0, ngen; i<ninst; i+=batch, j++) {
        ngen = MIN(batch, ninst-i);
        printf("write batch[%02d]=%d\n", j, ngen);
        dbg_gen_data(buf, ngen, trlen, GKOFS, GKMIN, GKMAX,
                SKOFS, SKMIN, SKMAX);
        write(fdd, buf, ngen*trlen);
    }
    free(buf);
    close(fdd);
    return 0;
}
