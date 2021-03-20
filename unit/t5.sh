#!/usr/bin/bash

flag="-W -Wall -O0 -ggdb"
python3 ../gentype.py header > ../gentype_gen.h
python3 ../gentype.py debug  > ../gentype_gen.c

rm -f core
rm -f unit5
gcc $flag unit5_test1.c -o unit5 -lm -lrt ../t2sort.o 
if [ ! -f unit5 ]; then
    echo "Compile Error"
    exit
fi

dio=1
chk=1
for buff in 60 160 260; do
    for wioq in 4 5 6 7 9; do
        ./unit5 1223 $buff $wioq gendata2.dat xsort1.dat $dio $chk
        if [ $? -ne 0 ]; then
            echo "error"
            exit
        fi
        rm -f delete_*
    done
done
exit
./unit5 1223 60 7 gendata2.dat xsort1.dat $dio $chk
./unit5 1223 60 9 gendata2.dat xsort1.dat $dio $chk
./unit5 1223 360 4 gendata2.dat xsort1.dat $dio $chk
