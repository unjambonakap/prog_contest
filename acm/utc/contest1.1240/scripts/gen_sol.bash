#!/bin/bash

if [ $# -lt 1 ]; then
    echo "need arg";
    exit 0
fi

g++ $1.cpp
if [ $? -ne 0 ] then echo "fail compile $1.cpp"; exit 1; fi;

echo > timelist
best=0.0;
for i in `ls tests/*.in`; do
    a=`echo $i | awk -F[.] '{print $1}' -`;
    res=`(/usr/bin/time -f '%e' ./a.out < $a.in > $a.out) 2>&1`;
    echo $res >> timelist
    if [ $(bc <<< "$res > $best") -eq 1 ]; then 
        best=$res; 
    fi;
done;
echo $best;


