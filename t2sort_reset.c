#ifndef C_T2SORT_RESET_T2SORT
#define C_T2SORT_RESET_T2SORT

int t2sort_reset(t2sort_h h)
{
    if(h->pile->ntr!=0) {
        //manually flush the last block!
    }
    //wait all pile write finishes.
    //read keys to the buffer for sorting!
    return 0;
}

#endif
