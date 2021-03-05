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
typedef struct {
    void   *dump;      //dump trace address
    //these two used for DIO/AIO write to disk!
    //sequential write seek location 
    void       *p_disk;     //disk align address
    size_t      d_size;     //disk data size
    int     ntr;
    int     rbyte;     //residual of this pile
    //shift between disk and dump copy to previous pile for write
} pile_t;

typedef struct t2sort_struct {
    int                 fd;         //data file
    int                 fd_keys;    //keys file, not used yet
    int                 trlen;
    int                 wioq;
    t2sort_key_def_t  * key;
    int                 nkey;
    int                 bsize;      //user given buffer size
    int                 flag;
//////////////////////////////////////////////
    int         buff_size;
    pile_t    * pile;
    void      *_base;
} t2sort_t;


