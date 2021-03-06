#ifdef __cplusplus
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../t2sort_i.h"

#ifdef __cplusplus
typedef struct {
    int     seq;        //key sequence
    int     key;        //key value, key might be longer!
} t2key_t;

void gen_data(int *p, int n, int size, int kmax);
void get_keys(int *p, int n, int size, t2key_t *k);
bool cmp_keys(const t2key_t &a, const t2key_t &b);
#endif
