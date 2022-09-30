#!/bin/bash


set -eu
data_dir=$1; shift
binary=$1; shift
for file in $(ls $data_dir/secret-*.in); do
  x=${file%.in}
  echo "checking $x"
  time $binary < $x.in > /tmp/res.out
  f1=/tmp/res.out
  f2=$x.ans
  ./check.py --file1=$f1 --file2=$f2 --precision=1e-6 --ret_syscode --actions=check_float $@
  #diff $f1 $f2

done;
