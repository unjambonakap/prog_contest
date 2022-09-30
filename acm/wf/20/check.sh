#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

set -eu
data_dir=$1; shift
binary=$@;
for file in $(ls $data_dir/*.in); do
  x=${file%.in}
  echo "checking $x"
  #time $binary < $x.in > /tmp/res.out
  f1=/tmp/res.out
  f2=$x.ans
  #$DIR/check.py --file1=$f1 --file2=$f2 --precision=1e-6 --ret_syscode --actions=check_float --multiline $@
  #diff $f1 $f2
  python ../data/qcqc/attachments/testing_tool.py $x.in $binary


done;
