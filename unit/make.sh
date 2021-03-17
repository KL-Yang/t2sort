#!/bin/bash

flag="-W -Wall -O3 -ggdb"

python3 ../gentype.py header > ../gentype_gen.h
python3 ../gentype.py debug  > ../gentype_gen.c

#gcc $flag unit5_test1.c -o unit5_test1 -lm -lrt ../t2sort.o 
#./unit5_test1
#exit

########## unit test-4
gcc $flag unit4_gendata.c -o unit4 -lm
./unit4 1223 100231 111 gendata2.dat
exit

########## unit test-3
gcc $flag -Wno-unused-function unit3_type.c -o unit3
./unit3
exit

########## unit test-2
g++ $flag -Wno-pointer-arith unit2_sort.cpp -o unit2
time ./unit2 50000000 0
time ./unit2 50000000 1
time ./unit2 50000000 2
#c99 qsort is faster
exit

########## unit test-1
gcc -c $flag unit1_map.c 
gcc $flag -o unit1_map unit1_map.o -lm
for ninst in {2001..10000..1333}; do
    for trlen in {1120..6666..400}; do
        ./unit1_map $trlen $ninst
    done
done

gcc $flag unit5_test1.c -o unit5_test1 -lm ../t2sort.o
./unit5_test1
