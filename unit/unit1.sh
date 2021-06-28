#!/usr/bin/bash

flag="-W -Wall -O0 -ggdb -std=gnu99"
rm -f unit1
########## unit test-1
gcc -c $flag unit1_map.c 
gcc $flag -o unit1 unit1_map.o -lm
for ninst in {2001..10000..1333}; do
    for trlen in {1120..6666..400}; do
        ./unit1 $trlen $ninst
    done
done

