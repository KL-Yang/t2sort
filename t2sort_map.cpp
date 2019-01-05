/**
 * T2Map: map data according to presorted keys
 *
 * seems no need to make it a class, over kill, anyway, just for excerse
 * */
#include "t2sort_i.h"
#include <cstring>

/**
 * @brief map data according to pre-sorted keys
 * @param size : unit length of data being mapped
 * */
T2Map::T2Map(int size)
{
    this->size = size;
    this->swap = new char [size];
}

T2Map::~T2Map()
{
    delete [] this->swap;
}

/**
 * Note: no need for the from/to buffer as in old implementation
 * just use a single map! 
 * in place mapping p to p according to m, where there are n items in total
 * in place map makes it difficult, out of place map make this really easy
 * @param m : from where map into target
 * */
void T2Map::map(int n, char **p, int *m)
{
    for(register int i=0; i<n; )
    {
        while(i<n && m[i]==i)  //find next out of order item
            i++;

        if(i==n)
            break;

        memcpy(this->swap, p[i], this->size); //backup to swap

        for(register int j=i, src=m[j]; j!=src; src=m[j])
            if(src<=i) {
                memcpy(p[j], this->swap, this->size);   //must be in swap
                m[j] = j;   //mark item done
                break;      //restart the link
            } else {
                memcpy(p[j], p[src], this->size);
                m[j] = j;   //mark item done
                j = src;    //follow the source
            }
    }
}
