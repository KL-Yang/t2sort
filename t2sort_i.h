#ifndef H_I_T2SORT_T2SORT
#define H_I_T2SORT_T2SORT

#include <aio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "t2sort.h"

#define MIN(a,b)    ((a)>(b)?(b):(a))
#define MAX(a,b)    ((a)>(b)?(a):(b))

/* typedef struct {
    void      *_base;
    void      * p;
    int         ntr;
} t2_blk_t; */

typedef struct t2sort_aio_struct {
    struct aiocb    paio;
} t2sort_aio_t;

typedef union t2sort_pay_struct {
    void          * ptr;    //pointer
    int64_t         idx;    //index
    struct {
        int32_t     blk;    //block id
        int32_t     idx;    //index in the block!
    } bpi;  //Block-Pile-Information
} t2sort_pay_t;

//queue generation algorith ensure ntr aligned with block size
typedef struct t2sort_rque_struct t2sort_que_t;
struct t2sort_rque_struct {
    t2sort_que_t  * next;
    t2sort_que_t  * prev;
    int             ntr;
    int             blk;    //read from which disk block
    //additional information for later aligned operation.
    off_t           seek;   //trace index of seeking
    t2sort_aio_t    aio;
    int             flag;
    int             id;
};
#define T2SORT_RQUE_SUBMIT  (1<<0)
#define T2SORT_RQUE_SPLIT   (1<<1)
#define T2SORT_RQUE_ALLOC   (1<<2)
#define T2SORT_RQUE_FINISH  (1<<3)

typedef struct t2sort_struct {
    int                 fd;         //data file
    int                 fd_keys;    //keys file, not used yet
    int                 trln;
    int                 wioq;
    t2sort_key_def_t  * kdef;
    int                 ndef;
    int                 klen;
    int                 flag;
//////////////////////////////////////////////
    int                 nblk;
    int64_t             nkey;   //todo remove
    int64_t             bntr;
    int64_t             pntr;
//////////////////////////////////////////////
    t2sort_que_t        read2;       //waiting que
    t2sort_que_t        wait2;      //replace one first!

//for t2sort_write, this is used as ring buffer.
//for t2sort_read, this is used as linear list. Note read may
//need split, and cannot use array!!!
    t2sort_que_t      * xque;
    int                 nxque;
    int                 xhead;
    int                 xtail;

//////////////////
    int64_t             rhead;       //read key index
    int64_t             rtail;      //because of 2nd pass sort
    int64_t             rdone;      //read already given to user
//////////////////////

    int64_t             rdfly;      //readraw on the fly
    int64_t             wrap;      //pntr*(wioq+1)
//////////////////////////////////////////////
    int  (*func_cmp_key)(const void*,const void*);
    void (*func_cpy_key)(void*,int,int,const t2sort_key_def_t*,void*);
//////////////////////////////////////////////
    void              *_base;
} t2sort_t;

int dbg_gen_key(int kmin, int kmax);
void dbg_gen_data(void *p, int n, size_t len, int gofs, int gmin, int gmax, int sofs, int smin, int smax);
void dbg_keys_valid(void *p, int n, int len, int gofs, int sofs);
void dbg_keys_print(void *p, int n, int len, int gofs, int sofs);
void dbg_data_valid(void *p, int n, int len, int gofs, int sofs);

#endif
