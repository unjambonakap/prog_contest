#!/bin/bash

#javac Main.java
#if [ $? -ne 0 ]; then echo "fail compile "; exit 1; fi;

echo > timelist
best=0.0;
for i in `ls tests/*.in`; do
    a=`echo $i | awk -F[.] '{print $1}' -`;
    echo "GOGO TEST  $i";
    res=`(/usr/bin/time -f '%e' python sol.py < $a.in > res.out) 2>&1`;
    if [ $(bc <<< "$res > $best") -eq 1 ]; then 
        best=$res; 
    fi;
    diff res.out $a.out
    if [ $? -ne 0 ]; then 
        echo "FAIL ON TESTCASE $a";
        exit 0;
    fi;
done;
echo $best;


