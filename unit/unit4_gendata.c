#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int gen_key(int kmin, int kmax)
{
    int key;
    key = nearbyint(kmin+(kmax-kmin)*(random()*1.0/RAND_MAX));
    return key;
}

/**
 * @brief generate data and keys
 * @param p,n,len : buffer, number of trace, trace length in byte
 * @param gofs,gmin,gmax : offset to group key and min, max
 * @param sofs,smin,smax : offset to sub key and min, max
 * Except key, all other samples are float with gkey.skey form.
 * If limit key to 3 digit, float number can accurately represent
 *  6 valid digts, and data can be verified later.
 * */
void gen_data(void *p, int n, size_t len, 
    int gofs, int gmin, int gmax, 
    int sofs, int smin, int smax)
{
    //integer and float alignment!
    assert(gofs%4==0 && sofs%4==0 && len%4==0);
    assert(gmin<=gmax && gmax<1000 && gmin>=0);
    assert(smin<=smax && smax<1000 && smin>=0);
    int pkey = gen_key(gmin, gmax);
    int skey = gen_key(smin, smax);
    int ndat = len/4;
    float *t = (float*)p;
    for(int i=0; i<n; i++) {
        for(int j=0; j<ndat; j++)
            t[j]=pkey+skey*1E-3;    //3digit accuracy
        ((int*)((void*)t+gofs))[0] = pkey;
        ((int*)((void*)t+sofs))[0] = skey;
        t += ndat;
    }
}

#define MIN(a,b)    ((a>b)?(b):(a))

#define TRLEN   (1223*sizeof(float))
#define GKOFS   0
#define GKMIN   1
#define GKMAX   200
#define SKOFS   4
#define SKMIN   1
#define SKMAX   900 
int main()
{
    unsigned int seed = 101;
    int ntrace = 100231, batch=10000;
    srandom(seed);
    int fd=open("gendata1.dat", O_RDWR|O_CREAT,
                S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    void *buf = calloc(batch, TRLEN);
    for(int i=0, j=0; i<ntrace; i+=batch, j++) {
        int ngen = MIN(batch, ntrace-i);
        printf("write batch[%02d]=%d\n", j, ngen);
        gen_data(buf, ngen, TRLEN, GKOFS, GKMIN, GKMAX,
            SKOFS, SKMIN, SKMAX);
        write(fd, buf, ngen*TRLEN);
    }
    free(buf);
    close(fd);
    return 0;
}
