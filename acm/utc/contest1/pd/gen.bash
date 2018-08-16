#!/bin/bash

g++ gen_test.cpp;
if [ $? -ne 0 ]; then echo "fail compile gen_test.cpp"; exit 1; fi;
mkdir tests

cnt=1;
./a.out 1 > tests/${cnt}_sample.in; cnt=`expr $cnt + 1`;
./a.out 7 > tests/${cnt}_1.in; cnt=`expr $cnt + 1`;

for i in {1..5}; do
    ./a.out 2 > tests/${cnt}_small_rand.in; cnt=`expr $cnt + 1`;
    ./a.out 3 > tests/${cnt}_large_rand.in; cnt=`expr $cnt + 1`;
    ./a.out 5 > tests/${cnt}_zeropath.in; cnt=`expr $cnt + 1`;
    ./a.out 6 > tests/${cnt}_big.in; cnt=`expr $cnt + 1`;
done;


for i in {1..15}; do
    ./a.out 4 > tests/${cnt}_large_rand0.in; cnt=`expr $cnt + 1`;
done;

