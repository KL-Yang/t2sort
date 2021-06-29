#!/usr/bin/bash

rm -f unit1
python3 ../gentype.py header > gentype_gen.h
python3 ../gentype.py debug  > gentype_gen.c

flag="-W -Wall -O3 -ggdb -std=gnu99"
########## unit test-1 #########################
gcc -c $flag -Wno-unused-function unit1_map.c 
gcc $flag -o unit1 unit1_map.o -lm

for ninst in {2001..10000..1333}; do
    for trlen in {1120..6666..400}; do
        echo "./unit1 $trlen $ninst"
        ./unit1 $trlen $ninst
	if [ $? -ne 0 ]; then
		exit
	fi
    done
done

