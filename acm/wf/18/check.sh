#!/bin/bash


set -eu
data_dir=$1; shift
binary=$1; shift
for file in $(ls $data_dir/*-{3,4,5,6}*.in); do
  x=${file%.in}
  echo "checking $x"
  time $binary --noinit_primes < $x.in > /tmp/res.out
  f1=/tmp/res.out
  f2=$x.ans
  #./check.py --file1=$f1 --file2=$f2 --precision=1e-6 --ret_syscode --verbosity=INFO --actions=check_float
  diff $f1 $f2

done;
