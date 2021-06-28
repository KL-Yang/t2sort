#!/usr/bin/bash

flag="-W -Wall -O0 -ggdb"

########## unit test-4
rm -f core unit4

gcc $flag unit4_gendata.c -o unit4 -lm
if [ ! -f unit5 ]; then
    echo "Compile Error, exit..."
    exit
fi
trlen=1223
ninst=500231
rseed=111
./unit4 $trlen $ninst $rseed gendata2.dat
exit


