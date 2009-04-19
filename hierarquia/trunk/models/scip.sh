#!/bin/bash
MODEL=$1
DATA=$2

scip -f $MODEL > $MODEL.out
cat $MODEL.out | grep "b\[" | sed "s/b\[//;s/\].*//;s/\,/\ /g" > $MODEL.top
time=`cat $MODEL.out | grep "^F" | sed "s/s.*//;s/F\ //"`
# echo $time
obj=`cat $MODEL.out | grep "Primal Bound" | sed "s/.*\:\ [+]//;s/\ .*//" | tail -n 1`
# echo $obj
lb=`cat $MODEL.out | grep "Dual Bound" | sed "s/.*\:\ [+]//;s/\ .*//" | tail -n 1`
# echo $lb

echo -e "$time\t$obj\t$lb" > $DATA
rm -f $MODEL.out

