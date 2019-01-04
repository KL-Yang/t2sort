#!/bin/bash

flag="-W -Wall -O0 -g"
g++ -c $flag common.cpp
g++ -c $flag map_test1.cpp
g++ $flag -o unit1 common.o map_test1.o
