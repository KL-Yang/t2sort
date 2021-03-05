#ifdef __cplusplus
/**
 * Public API, the rest will be hidden private API
 * */
class T2Sort 
{
    private:    //TODO need to hide this part in opaque private class
        int     flag;
        //T2Map   map;
        int     tfd;        /* Traces file descriptor */
        int     kfd;        /* Unique Keys file */
        void    init();     /* Initiation (once) before push! */

    public:
        T2Sort();
        ~T2Sort(void);
        void push(char *t, int n);      //normal push
        void sort();
        void reset();
        void pull();                    //normal pull

        char * push(int n, int *m);     //lazy push reload
        char * pull(int n, int *m);     //lazy pull reload

        //advanced setup function, must before first call of Push!
        void set_file();
        void set_key_file();            //not use key file yet! ignore it.
};
#endif

typedef struct t2sort_struct * t2sort_h;

typedef struct {
    int     offset;     //offset of the key
    int     type;       //type T2SORT_INT32_T, ...
    int     order;      //1 or -1
    int     flag;       //1 for group key
} t2sort_key_def_t;

typedef t2sort_key_def_t t2sort_key_t;

/**
 * @brief initiate the sort handle
 * @param trlen : trace length in bytes
 * @param nkey  : number of keys, maximum 3 group keys and 3 sub keys
 * @param keys  : definition of keys
 * @param bsize : memory buffer size in MB, approximated total size
 * @param wioq  : number of write IO queue
 * @param flag  : T2SORT_PUNCH_HOLE | T2SORT_GROUP_SORT | T2SORT_IO_URING
 * use DIO and io_submit (Linux AIO) by default!
 * */
t2sort_h
t2sort_init(int trlen, int nkey, const t2sort_key_def_t *keys, int bsize, int wioq, int flag);

/**
 * @brief Dump or partial dump data into the sorter
 * @param p 
 * @param ntr : number of 
 * return the actual number of trace dumpped into the sorter
 * */
int t2sort_dump(t2sort_h h, const void *p, int ntr);
/**
 * Sort if not sorted, otherwise reset of read queue
 * without reset, read/readraw can only sequentially read out once
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
 * */
void * t2sort_readraw(t2sort_h h, int *ntr);

/**
 * @brief release all the resources
 * */
int t2sort_destroy(t2sort_h h);
