#!/usr/bin/bash

flag="-W -Wall"
python3 gentype.py > gentype_gen.h
gcc -c $flag t2sort.c
