#!/bin/bash

flag="-W -Wall -O0 -g"
g++ -c $flag common.cpp
g++ -c $flag map_test1.cpp
g++ -c $flag ../t2sort_map.cpp
g++ $flag -o unit1 common.o map_test1.o t2sort_map.o
./unit1 200 100 | tee log

########## unit test-2
python3 ../gentype.py debug > x_unit3_type.c
gcc $flag unit3_type.c -o unit3
