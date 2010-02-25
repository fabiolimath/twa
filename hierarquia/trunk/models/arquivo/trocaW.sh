#!/bin/bash

id="N30.I1.s1"

work=`pwd`
dados="$work/data/$id"


cd $dados

sed -i "s/Wc := [1-9]*/Wc := $1/" *W*

for i in *W*; do 
   name=`echo $i | sed "s/W[1-9]*/W$1/"`; 
   mv $i $name;  
done
   


