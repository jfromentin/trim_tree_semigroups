#!/bin/bash

args=`ls todo | tr '\n' ' '`
parallel /nfs/home/lmpa/jfromentin/wilf/run_walk ::: $args ::: 60

