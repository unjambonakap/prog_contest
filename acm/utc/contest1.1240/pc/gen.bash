#!/bin/bash

g++ gen_test.cpp
if [ $? -ne 0 ]; then echo "fail compile gen_test.cpp"; exit 1; fi;
cp sample.in tests/1_sample.in
./a.out > tests/2_all.in

