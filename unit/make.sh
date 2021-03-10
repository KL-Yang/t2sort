#!/bin/bash

flag="-W -Wall -O0 -ggdb"

gcc $flag unit5_test1.c -o unit5_test1 -lm -lrt ../t2sort.o 
#./unit5_test1
exit

########## unit test-1
gcc -c $flag unit1_map.c 
gcc $flag -o unit1_map unit1_map.o -lm
./unit1_map 1234 2000
exit

########## unit test-2
python3 ../gentype.py header > x_del_unit3_type.h
python3 ../gentype.py debug  > x_del_unit3_type.c
gcc $flag unit3_type.c -o unit3
#./unit3

gcc $flag unit4_gendata.c -o unit4_gendata -lm
#./unit4_gendata

gcc $flag unit5_test1.c -o unit5_test1 -lm ../t2sort.o
./unit5_test1
