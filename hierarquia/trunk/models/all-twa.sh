#!/bin/bash

       id="N30.I1.s1"
       TIFgap=(0.8)
      Win="1"
     Wout="5"
TIFgapSn=${#TIFgap[*]}

work=`pwd`
outdir="$work/test4/$id"
mkdir -p $outdir
dados="$outdir/jobs"

success="$outdir/success"
mkdir -p $success
fail="$outdir/fail"
mkdir -p $fail

if [ ! -e $outdir/$id.success.txt ]; then
   echo -e "SR T Gl W HmDs\tHmUBp\tHmaxUB  \tTrDs\tTrUBp\tTrUB    \tTIFgap\tLimCIPF\tTime\tSTATUS \tCIPF\tTrafRetr\tTrancpt\tCustTotal\tCong" > $outdir/$id.success.txt
fi

if [ ! -e $outdir/$id.fail.txt ]; then
   echo -e "SR T Gl W HmDs\tHmUBp\tHmaxUB  \tTrDs\tTrUBp\tTrUB    \tTIFgap\tLimCIPF\tTime\tSTATUS" > $outdir/$id.fail.txt
fi

echo "
       id	TIFgapIN	TIFgapOUT	Win	Wout
$id	${TIFgap[0]}	${TIFgap[$TIFgapSn - 1]}	$Win	$Wout" >> $outdir/$id.txt


(

for((i=0;i<$TIFgapSn;i++)); do

   if [[ ! `ls $dados/*W* | wc -l` > 0  ]]; then break; fi
   
   for((W=$Win;W<=$Wout;W++)); do
         
      sed -i "s/Wc \+:= \+[0-9]\+/Wc := $W/" $dados/*W*
      sed -i "s/TIFgap \+:= \+[0-9]\+\.\+[0-9]\+/TIFgap := ${TIFgap[$i]}/" $dados/*W*

      for k in $dados/*W*; do 
         name=`echo $k | sed "s/W[0-9]\+/W$W/;s/TIFgap[0-9]\+\.[0-9]\+/TIFgap${TIFgap[$i]}/"`; 
         mv $k $name;  
      done
      
      for data in $dados/*W*; do

         ./twa.sh $data > saida
         
         out=`basename $data | sed "s/\.mod/\.out/"`
         sol=`basename $data | sed "s/\.mod/\.sol/"`
         
         check=`cat saida | grep "SUCCESS" | wc -l`
         
         if [[ $check == "1"  ]]; then
	  
	  cat saida >> $outdir/$id.success.txt
	  
	  mv $data $success/     
	  mv $out  $success/
	  mv $sol  $success/
         else
	  cat saida >> $outdir/$id.fail.txt
	  
	  mv $out $fail/
         fi
         
         rm saida
         
      done
   
      if [[ ! `ls $dados/*W* | wc -l` > 0  ]]; then break; fi 
      
   done
done

) >> $outdir/$id.txt  2>&1

echo -e "\n\n\t\t Fim do teste\n\n" >> $outdir/$id.txt


