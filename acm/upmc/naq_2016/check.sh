#!/bin/bash


set -eux
dir=$1; shift
for file in $(ls $dir/*.in); do
  x=${file%.in}
  ./a.out < $x.in > /tmp/res.out
  diff /tmp/res.out $x.ans

done;
