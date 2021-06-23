#!/usr/bin/bash

flag="-W -Wall -O2 -ggdb -D_GNU_SOURCE"
python3 gentype.py header > gentype_gen.h
python3 gentype.py > gentype_gen.c
gcc -c $flag t2sort.c -fPIC
#rm -f gentype_gen.c
