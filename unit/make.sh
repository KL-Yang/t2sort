#!/bin/bash

flag="-W -Wall -O0 -ggdb"

python3 ../gentype.py header > ../gentype_gen.h
python3 ../gentype.py debug  > ../gentype_gen.c

gcc $flag unit5_test1.c -o unit5 -lm -lrt ../t2sort.o 
#./unit5 1223 60 4 gendata2.dat xsort1.dat 0 0
#rm -f xsort1.dat
#./unit5 1223 240 5 gendata2.dat xsort1.dat 0 0
#rm -f xsort1.dat
exit

########## unit test-4
gcc $flag unit4_gendata.c -o unit4 -lm
./unit4 1223 100231 111 gendata2.dat
exit

########## unit test-2
g++ $flag -Wno-pointer-arith unit2_sort.cpp -o unit2
time ./unit2 50000000 0
time ./unit2 50000000 1
time ./unit2 50000000 2
#c99 qsort is faster
exit


gcc $flag unit5_test1.c -o unit5_test1 -lm ../t2sort.o
./unit5_test1
