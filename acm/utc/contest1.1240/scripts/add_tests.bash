#!/bin/bash

if [ $# -lt 1 ]; then
    echo "need and id of problem"
    exit 0;
fi;
pass=root;
id=$1;

for i in `ls tests/*.in | sort -n -t/ -k 2.1`; do
    pos=`echo $i | awk -F[_/] '{print $2}'`;
    desc=`echo $i | awk -F[_.] '{print $2}'`;
    a=`echo $i | rev | cut -c4- | rev`;
    sa=`md5sum $a.in | cut -d' ' -f1`;
    sb=`md5sum $a.out | cut -d' ' -f1`;


    pw=`pwd`;

    mysql -u root -p$pass -e "insert into testcase values (NULL,'$sa','$sb',load_file('$pw/$a.in'),load_file('$pw/$a.out'),'$id',$pos,'$desc')" domjudge  > res_sql_$id.out;
done;



