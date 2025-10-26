#!/bin/bash

g++ gen_wyspa.cpp -o gen.e
g++ wyspa.cpp -o wyspa.e
i=1
while [ true ]; do
    echo $i
    ((i++))
    ./gen.e "$1" "$2" "$i" >st.in
    ./wyspa.e <st.in >st.out
    cat st.out
done