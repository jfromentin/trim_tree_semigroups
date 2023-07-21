#!/bin/bash

ne=1
timeout=60

wait_todo_empty(){
    until [ -z "$(ls todo)" ]
    do 
	sleep 2
    done
}

run_epoch(){
    echo
    echo "-----------------"
    echo " Launch epoch $ne"
    echo "-----------------"
    n=`ls todo | wc -l`
    echo " There is $n tasks"
    echo -n " > filtering ... "
    oarsub -S /nfs/home/lmpa/jfromentin/wilf/filter_oar.sh > /dev/null
    wait_todo_empty
    echo "done"
    if [ ! -z "$(ls next)" ]; then
       mv next/* todo
       n=`ls todo | wc -l`
       echo " We get $n new tasks"
       echo -n " creating parameters ..."
       rm -f parameters
       cd todo
       for file in `ls *`
       do
	   echo "$file" >> ../parameters
       done
       cd ..
       echo "done"
       echo -n " > runing all with timeout $timeout ... "
       oarsub -S /nfs/home/lmpa/jfromentin/wilf/run_all_oar.sh > /dev/null
       wait_todo_empty
       echo "done"
       if [ ! -z "$(ls next)" ]; then
	   mv next/* todo
       fi
    fi
}

main(){
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
       exit 0
    fi
    echo "done"
    cd ..
    echo -n " > init files ... "
    if ! (./init_files>/dev/null) then
       exit 0
    fi
    echo "done"

    ne=1
    timeout=1
    until [ -z "$(ls todo)" ]
    do
	run_epoch
	ne=$((ne+1))
    done
}

if [ "$#" -ne 1 ]; then
    echo "You must specify max genus"
    exit 0
fi
gmax=$1
main
