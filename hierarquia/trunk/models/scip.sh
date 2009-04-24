#!/bin/bash
DATA=$1
INFO=$2

IsMpsGz=`echo $DATA | grep ".mps.gz" | sed -n "$="`

if [[ "$IsMpsGz" != "1" ]]; then
  MODEL="labtel-twa.mod"
  glpsol -m $MODEL -d $DATA --wfreemps $DATA.mps.gz --check
  DATA="$DATA.mps.gz"
fi

scip -f $DATA > $DATA.out
cat $DATA.out | grep "b\[" | sed "s/b\[//;s/\].*//;s/\,/\ /g" > $DATA.top
time=`cat $DATA.out | grep "Primal Bound" | grep "nodes" | sed "s/.*nodes. //;s/ .*//"`
# echo $time
obj=`cat $DATA.out | grep "Primal Bound" | sed "s/.*\:\ [+]//;s/\ .*//" | tail -n 1`
# echo $obj
lb=`cat $DATA.out | grep "Dual Bound" | sed "s/.*\:\ [+]//;s/\ .*//" | tail -n 1`
# echo $lb

echo -n -e "$time\t$obj\t$lb" >> $INFO
rm -f $DATA.out

