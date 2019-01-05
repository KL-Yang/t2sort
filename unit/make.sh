#!/bin/bash

flag="-W -Wall -O0 -g"
g++ -c $flag common.cpp
g++ -c $flag map_test1.cpp
g++ -c $flag ../t2sort_map.cpp
g++ $flag -o unit1 common.o map_test1.o t2sort_map.o
./unit1 200 100 | tee log
