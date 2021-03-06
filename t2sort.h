#ifndef H_T2SORT_T2SORT
#define H_T2SORT_T2SORT

#define T2SORT_DIO      (1<<0)
#define T2SORT_DEBUG	(1<<2)

typedef struct t2sort_struct * t2sort_h;

typedef struct {
    int     offset;     //offset of the key
    int     type;       //type T2SORT_INT32_T, ...
    int     order;      //1 or -1
    int     flag;       //1 for group key
} t2sort_key_def_t;

typedef t2sort_key_def_t t2sort_key_t;

/**
 * @brief open the sort handle, opaque handle like return from open(2)
 * @param tlen : trace length in bytes
 * @param ndef : number of keys, maximum 3 group keys and 3 sub keys
 * @param kdef : definition of keys
 * @param bsiz : memory buffer size in MB, approximated total size
 * @param wioq : number of write IO queue
 * @param flag : T2SORT_PUNCH_HOLE | T2SORT_GROUP_SORT | T2SORT_IO_URING
 * use DIO and io_submit (Linux AIO) by default!
 * */
t2sort_h
t2sort_open(int tlen, int ndef, const t2sort_key_def_t *kdef, int bsize, int wioq, int flag);

/**
 * @brief zero copy write io, exposed internal buffer
 * @param h   : sorter handle
 * @param ntr : [IO] number of trace expected and actually exposed
 * return exposed buffer, which is only guarantee valid till next write/writeraw.
 * user is expect to write the buff for ntr traces.
 * exposed ntr must be less or equal to expected.
 * */
void * t2sort_writeraw(t2sort_h h, int *ntr);
/**
 * @brief write or partial write data into the sorter
 * @param p   : buffer of data to be write
 * @param ntr : number of trace to write
 * return the actual number of trace written into the sorter
 * partial write will expect further call to wirte the rest
 * */
int t2sort_write(t2sort_h h, const void *p, int ntr);
/**
 *   Reset the sort data flow, which is sort everything if not 
 * sorted to prepare for read, otherwise reset the read queue.
 * Without reset, read/readraw can only sequentially read out 
 * once, with reset, can read again start from beginning.
 * */
int t2sort_sort(t2sort_h h);
/**
 * Read or partial read data from the sorter
 * return the actually read number of trace
 * */
int t2sort_read(t2sort_h h, void *p, int ntr);
/**
 * @brief zero copy read io, exposed internal buffer
 * @param h   : sorter handle
 * @param ntr : [IO] number of trace expected and actually exposed
 * return exposed buffer, which is only guarantee valid till next read/readraw.
 * user is expect to read from the buff for ntr traces.
 * exposed ntr must be less or equal to expected.
 * */
void * t2sort_readraw(t2sort_h h, int *ntr);

/**
 * @brief release all the resources
 * */
int t2sort_close(t2sort_h h);
#endif
