#!/usr/bin/bash

flag="-W -Wall -O0 -ggdb"
python3 gentype.py header > gentype_gen.h
python3 gentype.py > gentype_gen.c
gcc -c $flag t2sort.c
