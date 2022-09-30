#!/bin/bash


set -eu
dir=$1; shift
for file in $(ls $dir/*.in); do
  x=${file%.in}
  echo "checking $x"
  ./a.out < $x.in > /tmp/res.out
  ./check.py --file1=/tmp/res.out --file2=$x.ans --precision=1e-8 --ret_syscode --verbosity=INFO --actions=check_float
  #diff /tmp/res.out $x.ans

done;
