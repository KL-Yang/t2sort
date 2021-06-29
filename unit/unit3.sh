#!/usr/bin/bash

rm -f unit3
python3 ../gentype.py header > ../gentype_gen.h
python3 ../gentype.py debug  > ../gentype_gen.c

flag="-W -Wall -O0 -ggdb"

# This test will assert function array index is correct!
########## unit test-3 ###################################
gcc $flag -Wno-unused-function unit3_type.c -o unit3
./unit3
