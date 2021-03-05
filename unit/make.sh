#!/bin/bash

flag="-W -Wall -O0 -g"
gcc -c $flag common.cpp
g++ -c $flag map_test1.cpp
g++ -c $flag ../t2sort_map.cpp
g++ $flag -o unit1 common.o map_test1.o t2sort_map.o
#./unit1 200 100 | tee log

########## unit test-2
python3 ../gentype.py header > x_del_unit3_type.h
python3 ../gentype.py debug  > x_del_unit3_type.c
gcc $flag unit3_type.c -o unit3
#./unit3

gcc $flag unit4_gendata.c -o unit4_gendata -lm
#./unit4_gendata

gcc $flag unit5_test1.c -o unit5_test1 -lm ../t2sort.o
./unit5_test1
