#!/bin/bash

cid=5;

for a in {a..e}; do
    u=p$a;
    echo $u;
    cd $u
    pwd;
    rm tests/*
    ./gen.bash $a
    if [ $? -ne 0 ]; then
        echo "gen.bash failed, returned";
        exit 0;
    fi;


    res=$(../scripts/check_input.bash $a)
    if [ $? -ne 0 ]; then
        echo "check_input failed, returned :$res";
        exit 0;
    fi;

    res=$(../scripts/gen_sol.bash $a)
    if [ $? -ne 0 ]; then
        echo "gen_sol failed, returned :$res";
        exit 0;
    fi;


    echo "GET $res";
    res=$(python -c "from math import *; print max(3,ceil(5*$res));");
    if [ $? -ne 0 ]; then
        echo "python failed, returned :$res";
        exit 0;
    fi;
    cd ..
    res=$(./scripts/add_problem.bash $a $cid $res);
    if [ $? -ne 0 ]; then
        echo "FAIL at add_problem: $res";
        exit 0;
    fi;

    cd $u 
    ../scripts/add_tests.bash $res;
    cd ..
done;


