#!/bin/bash

ne=1
timeout=60

function wait_todo_empty(){
    until [ "$(echo todo/*)" == "todo/*" ]
    do 
	sleep 2
    done
}
function run_epoch(){
    echo
    echo "-----------------"
    echo " Launch epoch $ne"
    echo "-----------------"
    n=`ls todo | wc -l`
    echo " There is $n tasks"
    echo -n " > filtering ... "
    sh filter.sh &
    wait_todo_empty
    echo "done"
    if [ ! -z "$(ls next)" ]; then
       mv next/* todo
       n=`ls todo | wc -l`
       echo " We get $n new tasks"
       echo -n " > runing all with timeout $timeout ... "
       sh run_all.sh $timeout &
       wait_todo_empty
       echo "done"
       if [ ! -z "$(ls next)" ]; then
	   mv next/* todo
       fi
    fi
}

function main(){
    gmax=$gmax
    echo "========================="
    echo " Launch tree exploration "
    echo "========================="
    echo " Maximum genus is $gmax."
    echo -n " > cleaning ... "
    sh ./clean_all.sh > /dev/null 2>&1
    echo "done"
    echo -n " > compiling ... "
    cd src
    if ! (make GMAX=$gmax>/dev/null) then
       exit -1
    fi
    echo "done"
    cd ..
    echo -n " > init files ... "
    if ! (./init_files>/dev/null) then
       exit -1
    fi
    echo "done"

    ne=1
    timeout=1
    until [ "$(echo todo/*)" == "todo/*" ]
    do
	run_epoch
	ne=$((ne+1))
	timeout=$(($timeout+$timeout))
    done
}

if [ "$#" -ne 1 ]; then
    echo "You must specify max genus"
    exit -1
fi
gmax=$1
main
