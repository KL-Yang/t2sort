#ifndef H_I_T2SORT_T2SORT
#define H_I_T2SORT_T2SORT

#include <aio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "t2sort.h"

typedef t2sort_key_def_t t2_kdef_t;

#define MIN(a,b)    ((a)>(b)?(b):(a))
#define MAX(a,b)    ((a)>(b)?(a):(b))
#define PAGE_SIZE   4096
#define PAGE_MASK   12  //1<<PAGE_MASK==PAGE_SIZE

typedef struct t2sort_aio_struct {
    struct aiocb    paio;
} t2_aio_t;

typedef union t2sort_pay_struct {
    void      * ptr;    //pointer
    int64_t     idx;    //index
    struct { 
        int32_t blk,idx;}
                bpi;  //Block-Pile-Information
} t2_pay_t;

typedef struct t2sort_blk_struct {
    void      * page;
} t2_blk_t;

typedef struct t2sort_que_struct t2_que_t;
struct t2sort_que_struct {
    t2_que_t  * next;
    t2_que_t  * prev;
    int         ntr;
    int         blk;    //read from which disk block
    off_t       seek;   //trace index of seeking
    t2_aio_t    aio;
    int         id;
    int64_t     ma, Ma, mz, Mz;
};
#define T2_QUE_SUBMIT  (1<<0)
#define T2_QUE_ALLOC   (1<<1)
#define T2_QUE_FINISH  (1<<3)

typedef struct t2sort_struct {
    int         fd;         //data file
    int         fd_keys;    //keys file, not used yet
    int64_t     trln;       //trace length in byte
    int         wioq;       //nppb, Number of Piles Per Block, TODO: rename
    t2_kdef_t * kdef;       //key definition
    int         ndef;       //number of key definition
    int         klen;       //key struct length
    int         flag;
    char        fd_name[128];
    int         nblk;       //disk block count
    int64_t     nkey;       //Total ntr count
    int64_t     bntr;       //ntr per block
    int64_t     pntr;       //ntr per pile
    t2_que_t    pool;       //IO pool queue
    t2_que_t    wait;       //IO wait queue
    t2_que_t    done;       //finished queue
    uint32_t    head;       //IO head index
    uint32_t    tail;       //IO tail index
    uint32_t    disk;       //IO on disk index
    uint32_t    nfly;       //IO flying
    uint32_t    wrap;       //ring buffer size pntr*(wioq+1)
//////////////////////////////////////////////
    int  (*func_cmp_key)(const void*,const void*);
    void (*func_cpy_key)(void*,int,int,const t2_kdef_t*,void*);
//////////////////////////////////////////////
    void      *_base;
    t2_que_t  *_xque;
    int       *_imap;
    void      *_pkey,*_temp,**_pptr;
    t2_blk_t  *_rblk;
    int64_t    _wrap;
} t2sort_t;

int dbg_gen_key(int kmin, int kmax);
void dbg_gen_data(void *p, int n, size_t len, int gofs, int gmin, int gmax, int sofs, int smin, int smax);
void dbg_keys_valid(void *p, int n, int len, int gofs, int sofs);
void dbg_keys_print(void *p, int n, int len, int gofs, int sofs);
void dbg_data_valid(void *p, int n, int len, int gofs, int sofs);

#endif
