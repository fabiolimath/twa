#!/bin/bash

id="30.I1.s1"

work=`pwd`
dados="$work/data/N$id"
mkdir -p $dados


if [ ! -e $dados/$id.Estatisticas.Hmax.txt ]; then
   echo -e "id T gl  nm\ttnm\tns\ttns\tLB\tHLDA\tRLDA\tMaxA\tMed\tDP" > $dados/$id.Estatisticas.Hmax.txt
fi

if [ ! -e $dados/$id.Estatisticas.FTnet.txt ]; then
   echo -e "id T gl  nm\ttnm\tns\ttns\tLB\tHLDA\tRLDA\tMaxA\tMed\tDP" > $dados/$id.Estatisticas.FTnet.txt
fi

(

for data in $dados/*.mod; do

   ./estatisticas $data -v > saida
   
   cat saida | grep "Hmax" | sed "s/Hmax \+//" >> $dados/$id.Estatisticas.Hmax.txt
   cat saida | grep "FTnet" | sed "s/FTnet \+//" >> $dados/$id.Estatisticas.FTnet.txt
   
   rm saida
   
done

) > $dados/$id.txt  2>&1


