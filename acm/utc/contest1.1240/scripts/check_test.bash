#!/bin/bash


g++ check_test.cpp
if [ $? -ne 0 ]; then echo "fail compile check_test.cpp"; exit 1; fi;
for i in `ls tests/*.in`; do
    a=`echo $i | awk -F[.] '{print $1}' -`;
    ./a.out < $a.in
    if [ $? -ne 0 ]; then 
        echo "FAIL on test $a";
        exit 1;
    fi;
done;


