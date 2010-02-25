#!/bin/bash

# data/N30.I1.s1/data.N30.I1.s1.cluster5.T3.GL1.W7.mod

fonte="$1"
data=`basename $fonte | sed "s/\.mod//"`
verbose="$2"

work=`pwd`
models="$work/models"
twa="$models/labtel-twa.mod"
glpsol="$models/glpsol"
scip="$models/scip -s $models/scip.set"
out="$data.out"

# if [[ "-v" == $verbose  ]]; then echo "$glpsol -m $twa -d $fonte --wfreemps $data.mps.gz --check";fi
$glpsol -m $twa -d $fonte --wfreemps $data.mps.gz --check  | grep "=" > $out 2>&1

# if [[ "-v" == $verbose  ]]; then echo "$scip -f $data.mps.gz";fi
$scip -f $data.mps.gz >> $out 2>&1

rm -f $data.mps.gz


format()
{
   echo "param $1 := " >> $data.sol
   cat $out | grep "\[[0-9]" | grep -v "h" | grep -v "$2\[" | sed "s/$1//" | awk '$2>0.999999{print $1, 1}; $2>0.000001 && $2<=0.999999 {print $1, $2}' | sort > tmp
   
   W=`echo $data | sed "s/.*W//;s/\..*//"`
   for((j=1;j<=$W;j++)); do
      sed -i "s/$j\]/\*\] $j/" tmp
   done
   
   cat tmp >> $data.sol  
   echo ";" >> $data.sol
   rm tmp
}

   
SubRede=`echo $out | sed "s/.*cluster/c/;s/.*backbone0/bk/;s/\.TIFgap.*//;s/\.GL/ /;s/\.W/  /;s/\.T/ /"`;
head  -n 8 $out > aux
cabecalho="SR T Gl W HmDs\tHmUBp\tHmaxUB  \tTrDs\tTrUBp\tTrUB    \tTIFgap\tLimCIPF\tTime\tSTATUS "

solved=`cat $out | grep "Primal Bound" | grep -E "([1-9][0-9]* solutions)" | wc -l`

if [[ $solved == 1 ]]; then
      
   cat $fonte | sed "s/end *\;//" > $data.sol
         
   format b qw
   
   format qw b
   
   echo "end;" >> $data.sol
   if [[ "-v" == $verbose  ]]; then ls $data.sol; fi
   
   $glpsol -m $models/calc-cong.mod -d $data.sol --check >> $out
   
   cat $out | grep -E "^Solving\ Time\ +:" | sed "s/Solving.*:/Time/"  | awk '{print $1, " = ", $2}' >> aux
   echo "status = SUCCESS" >> aux
   cat $out | grep -E "^CIPF|^CustoTrafRetr|^TotalTrancpt|^CustoTotal"  | awk '{print $1, " = ", $2}' >> aux
   cat $out | grep "Congestionamento" | sed "s/:/ =/" >> aux

   if [[ "-v" == $verbose  ]]; then
      echo -e "$cabecalho\tCIPF\tTrafRetr\tTrancpt\tCustTotal\tCong"
   fi
   
   cat aux | sed "s/^.* \+= \+//" | awk '{if($1=="SUCCESS") printf ("%s\t", $1); else printf ("%.3f\t", $1)}' | sed "s/^/$SubRede /;s/\t$/\n/"
   
else

   tempo=`cat $out | grep -E "^Solving\ Time\ +:" | sed "s/Solving.*:/Time/"  | awk '{print $1, " = ", $2}'`
   
   if [[ $tempo == "" ]]; then 
      tempo=`cat $out | grep "Inf" | sed "s/s.*//" | tail -n 1`
   fi
      
   echo "Time = $tempo"  >> aux   
   
   fail=`cat $out | grep "Primal Bound     : infeasible" | wc -l`
   if [[ $fail == 1 ]]; then
      status="infeasible"
   else
      fail=`cat $out | grep "Primal Bound     :          -" | wc -l`
      if [[ $fail == 1 ]]; then
         status="time_out"
      else
         status="SCIPcrash"
      fi
   fi
   
   if [[ "-v" == $verbose  ]]; then
      echo -e "$cabecalho"
   fi
   
   cat aux | sed "s/^.* \+= \+//" | awk '{printf ("%.3f\t", $1)}' | sed "s/^/$SubRede /;s/$/$status\n/"
   
fi   

   if [[ "-v" == $verbose  ]]; then ls $out; fi

rm aux











