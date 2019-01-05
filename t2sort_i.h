#include <cstring>

using namespace std;

//T2sort, seismic sort, write in c++, make c,python wrapper!

/**
 * Internal struct, will not expose to outside
 * */
class T2Map {
    private:
        int    size;
        char * swap;
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
