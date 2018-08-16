#!/bin/bash

if [ $# -lt 3 ]; then 
    echo "nuud prob, contest id, tl"
    echo "arg $1 xx $2 xx $3";
    exit 1; 
fi;

pass=root;
l=$1;
cid=$2;
tl=$3;

perl -pi "s/[0-9]* seconds/$tl seconds/" p$l.tex


if [ ! -d p$l ]; then
    echo "do not exist dir (p$l)";
    exit 1;
fi;

file=p$l/data;
if [ ! -f $file ]; then
    echo "do not exist data ($file)";
    exit 1;
fi;

pid=$(cat $file | head -1 | tail -1);
pname=$(cat $file | head -2 | tail -1);
color=$(cat $file | head -3 | tail -1);

mysql -u root -p$pass -e "insert into problem values ('$pid',$cid,'$pname',1,1,$tl,'','','$color');" domjudge  2>&1 > res_sql_$l.out;
echo $pid;

