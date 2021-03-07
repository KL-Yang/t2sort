#ifndef H_I_T2SORT_T2SORT
#define H_I_T2SORT_T2SORT

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <aio.h>

#include "t2sort.h"

#ifdef __cplusplus
#include <cstring>
using namespace std;

//T2sort, seismic sort, write in c++, make c,python wrapper!

/**
 * Internal struct, will not expose to outside
 * */
class T2Map {
    private:
        int     size;
        char  * swap;
    public:
        T2Map(int);
        ~T2Map(void);
        void map(int n, char **p, int *m);
};

/**
 * Note, in memory only save group key, unique key saves on disk.
 * if group mode, in sortall() do not touch unique key, or do not save unique key at all
 * otherwise, in sortall(), also sort the unique key.
 * thus balance the memory usage and flexibility.
 *
 * 1. Extract unique key, and sort key, and sort data.
 * 2. Extract and compress group key and keep in memory.
 * 3. Write unique key and write data to their backend.
 * 4. Global sort group key, on flag, read and sort unique keys.
 * 5. Read by group, if group fits in memory, otherwise read 
 *      unique keys to plan partial read of one group!
 * 6. Destroy the resources
 *
 * Must be careful for group mode when group is crossing the memory buffer boundary!!!
 *
 * the longer unique keys can be managed as if a shorter seismic trace, recursively!!!
 *
 * At most 3 group keys and 3 subset keys, 6keys in total.
 * */
class zkey {
    private:
        int     flag;
        int     nkey;   //maximum 2^31 keys
        int     kfid;   //optionally key may be on disk too!
    public:
        zkey();
        ~zkey();
        void push();
        void sortall();
        void restart();
        void pull();
};
#endif

typedef struct t2sort_aio_struct {
    struct aiocb    paio;
} t2sort_aio_t;

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
    t2sort_key_def_t  * key;
    int                 nkey;
    int                 klen;
    int                 bsize;      //user given buffer size
    int                 flag;
//////////////////////////////////////////////
    int                 wpile;      //how many pile processed
    int                 winst;      //how many instance write
    int                 wpntr;      //ntr capacity of write pile
    pile_t            * pile;
//    int                 iwp;        //current operating pile
    void (*func_cmp_key)(const void*,const void*);
    void (*func_cpy_key)(const void**,int,const int*,void*);
//////////////////////////////////////////////

    int         buff_size;
    void      *_base;
} t2sort_t;

#endif
