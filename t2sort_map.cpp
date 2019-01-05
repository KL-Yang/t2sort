/**
 * T2Map: map data according to order determined by presorted keys
 * */
#include "t2sort_i.h"

/**
 * @brief Initiate the map with size in Byte and temporal storage
 * @param size : unit length of data being mapped in Byte
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
 * @brief In place map p according to m, use only one extra memory
 * @param n : total items in buffer
 * @param p : pointer of items being mapped
 * @param m : from where map into target
 * */
void T2Map::map(int n, char **p, int *m)
{
    for(register int i=0; i<n; /*no action*/ ) {
        while(i<n && m[i]==i)
            i++;

        if(i==n)
            break;

        memcpy(this->swap, p[i], this->size);

        for(register int j=i, src=m[j]; j!=src; src=m[j])
            if(src<=i) {
                memcpy(p[j], this->swap, this->size);   //must be in swap
                m[j] = j;
                break;
            } else {
                memcpy(p[j], p[src], this->size);
                m[j] = j;
                j = src;
            }
    }
}
