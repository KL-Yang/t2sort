#include "../t2sort.h"
#include "../gentype_gen.h"

#define TRLEN   (1223*sizeof(float))
#define GKOFS   0
#define SKOFS   4
#define MB      (1024L*1024L)
int main()
{
    int trlen = TRLEN, nkey = 2, bsize=60*MB, wioq = 4;
    int flag = 0;
    t2sort_key_def_t keys[] = {
        {.offset=GKOFS, .type=T2SORT_INT32_T, .order=1},
        {.offset=SKOFS, .type=T2SORT_INT32_T, .order=1}
    }; 
    t2sort_h sort;
    sort = t2sort_init(trlen, nkey, keys, bsize, wioq, flag);

    //open and read file, call t2sort_dump()

    t2sort_destroy(sort);
    return 0;
}
