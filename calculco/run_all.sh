#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "You must specify timeout"
    exit -1
fi
timeout=$1
cd todo
inputs=`ls *`
cd ..

for i in $inputs
do
    ./run_walk $i $timeout
done
	     
