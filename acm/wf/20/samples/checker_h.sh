#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

rm -f /tmp/fin; mkfifo /tmp/fin
rm -f /tmp/fout; mkfifo /tmp/fout
g++ -DLOCAL ./h.cpp
pushd ../data/qcqc/tools
javac QcqcInteractionFormatChecker.java
F1="java QcqcInteractionFormatChecker ../data/sample/1.interaction"
F2=$DIR/a.out
ulimit -c unlimited
$F2 & < /tmp/fin > /tmp/fout 
echo start1
$F1 < /tmp/fout > /tmp/fin
echo done
