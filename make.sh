#!/usr/bin/bash

flag="-W -Wall -O0 -ggdb -D_GNU_SOURCE -std=gnu99"
python3 gentype.py header > gentype_gen.h
python3 gentype.py > gentype_gen.c
gcc -c $flag t2sort.c -fPIC
ar cr libt2sort.a t2sort.o
#rm -f gentype_gen.c
