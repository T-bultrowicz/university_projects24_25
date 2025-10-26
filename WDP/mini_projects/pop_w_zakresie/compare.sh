#!/bin/bash

g++ @opcjeCpp main.cpp prev.cpp -o wzor.e
g++ @opcjeCpp main.cpp brut.cpp -o brut.e
g++ -std=c++20 -O2 -static gen.cpp -o gen.e

for((i=1; ; i++)); do
    echo $i
    ./gen.e $i > test.in
    ./wzor.e < test.in > wzor.out
    ./brut.e < test.in > brut.out
    diff -w wzor.out brut.out || break
done
