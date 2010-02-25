#!/bin/bash

tipe="Hmax"
data="data/N30.I1.s1"

files=`ls $data/*$tipe.a*` 

echo -e "SR T Gl UB\tp_LessUB"


for file in $files; do
   
   min=`min.awk $file`
   ub=`echo $min | awk '{print $1 + 0.01}'`

   sed -i "s/ub=.*/ub=$ub/" igualAoMin.awk
   cont=`igualAoMin.awk $file`
   
   id=`echo $file | sed "s/.*cluster/c/;s/.*backbone0/bk/;s/\.mod.*/ /;s/\.GL/ /;s/\.T/ /"`;

   ln=`wc -l $file`
   percent=`echo "$cont $ln" | awk '{printf("%.2f", $1/$2)}'`
   
   echo -e "$id $ub\t$percent"

done
