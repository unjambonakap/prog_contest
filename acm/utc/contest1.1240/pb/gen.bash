#!/bin/bash

g++ gen_test.cpp;
if [ $? -ne 0 ]; then echo "fail compile gen_test.cpp"; exit 1; fi;

cnt=1;
./a.out 1 > tests/${cnt}_sample.in; cnt=`expr $cnt + 1`;

for i in {1..5}; do
    ./a.out 2 > tests/${cnt}_log.in; cnt=`expr $cnt + 1`;
    ./a.out 3 > tests/${cnt}_log.in; cnt=`expr $cnt + 1`;
    ./a.out 4 > tests/${cnt}_ll.in; cnt=`expr $cnt + 1`;
    ./a.out 5 > tests/${cnt}_ll.in; cnt=`expr $cnt + 1`;
done;


for i in {1..30}; do
    ./a.out 6 > tests/${cnt}_rand.in; cnt=`expr $cnt + 1`;
done;

