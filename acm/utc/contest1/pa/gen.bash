g++ gen_test.cpp 
if [ $? -ne 0 ]; then echo "fail compile gen_test.cpp"; exit 1; fi;
./a.out 1 > tests/1_sample.in
./a.out 2 > tests/2_smallrand.in
./a.out 3 > tests/3_duplicate.in
./a.out 4 > tests/4_ncoprime.in
./a.out 5 > tests/5_coprime.in
./a.out 6 > tests/6_rand.in
