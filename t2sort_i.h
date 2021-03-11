#ifndef H_I_T2SORT_T2SORT
#define H_I_T2SORT_T2SORT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <aio.h>

#define MIN(a,b)    ((a)>(b)?(b):(a))
#define MAX(a,b)    ((a)>(b)?(a):(b))

#include "t2sort.h"

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
    int             ntr;
    int             blk;    //read from which disk block
    //additional information for later aligned operation.
    off_t           seek;   //trace index of seeking
    int             mblk;   //build which block in memory
    t2sort_aio_t  * aio;
    t2sort_que_t  * next;
    int             flag;
    int             id;     //for debug
};
#define T2SORT_RQUE_SUBMIT  (1<<0)
#define T2SORT_RQUE_SPLIT   (1<<1)
#define T2SORT_RQUE_FINISH  (1<<2)

//pile: use shifted buffer for DIO
//  pile align at 4K : must
//  pile align trace : must for in memory sort.
//
//p1->_base begin@4K with nptr, pad end@4k
//  ->p begin@4k, with nptr, r1=nptr*trlen%4K
//  ->x begin@4k for dio write
//p2->_base begin@4K with nptr, pad end@4k
//  ->p=_base+r1, so lead (4K-r1) merge into p1 after sort for write
//    r2=(r1+nptr*trlen)%4K
//  ->x=_base+4K for dio write
//p3->_base begin@4K with nptr, pad end@4k
//  ->p=_base+r1*2
//
typedef struct pile_struct_t pile_t;
struct pile_struct_t {
    void          * base;   //disk operation base
    void          * p;      //memory operation base
    int             ntr;    //number of trace in pile
    int             status; //pile status
    int             ri;     //residual of this pile
    //some aio context should be kept here!
    int             bpid;   //block pid
    t2sort_aio_t    cb;
//////////////////////////////////////////////////
    int         pid;    //pile id
    pile_t    * prev;
    pile_t    * next;
};

typedef struct t2sort_struct {
    int                 fd;         //data file
    int                 fd_keys;    //keys file, not used yet
    int                 trlen;
    int                 wioq;
    t2sort_key_def_t  * kdef;
    int                 ndef;
    int                 klen;
    int                 bsize;      //user given buffer size
    int                 flag;
//////////////////////////////////////////////
    int                 wpile;      //how many pile processed
    int                 nblk;
    int64_t             nkey;   //todo remove
    int64_t             bntr;
    int64_t             pntr;

    pile_t            * pile;
//////////////////////////////////////////////
    int                 rpos;       //read position wrap @ wrap
    int                 slot;       //read slots available
    t2sort_que_t      * read;       //waiting que
    t2sort_que_t        wait_head;  //waiting que
    t2sort_que_t      * wait;       //initiate to &wait_head;

    t2sort_que_t      * xque;
    int                 nxque;
    int                 xhead;
    int                 xtail;

//////////////////
    int                 rslot;
    int64_t             rhead;       //read key index
    int64_t             rtail;      //because of 2nd pass sort
                                    //increase at multiple of bntr
    int64_t             rdone;      //read already given to user
//////////////////////

    int64_t             rdfly;      //readraw on the fly
    int64_t             nsort;
    int64_t             nwrap;      //pntr*(wioq+1)
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
