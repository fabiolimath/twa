#!/bin/bash

Seta() 
{ 
  sed -i "s/param $1 .*/param $1 := $2;/;s/end;//" $DATA
  [[ "$(grep "param $1 " $DATA | wc -l)" = 1 ]] || echo "param $1 := $2;" >> $DATA
}

DATA="p1-test.mod"
N="14"
grl="2"
Wc="1"

Seta Wc $Wc
Seta Cap 85
Seta HmaxLB 84.58

INFO="p1.Gl$grl.W$Wc.txt"

# Mutuamente Excludentes
PARAMSxcld=("Gl" "TT" "Gle" "TTe")
Gl=($grl)
Gle=($grl)
TT=($(($grl*$N)))
TTe=($(($grl*$N)))

Coment() { sed -i "s/^param $1 /#param $1 /" $DATA; }
unComent() { sed -i "s/^#param $1 /param $1 /" $DATA; }

# Não Excludentes
PARAMS=("Aut" "CPD" "CPF" "NullTraf")
Aut=(0 1)
CPD=(0 1)
CPF=(0 1)
NullTraf=(0 1)

Card(){ eval echo \$\{\#$1\[*]\}; }
Valor(){ eval echo \$\{$1\[\$2]\}; }
Space()
{ 
  A=$(echo $1 | wc -c) 
  B=$(echo $2 | wc -c)
  T=$((A-B))
  
  for(( e = 0; e < $T; e++)); do echo -n "$3"; done;
} 

NaoExclud()
{
  i=$1
  VAR=$(Valor PARAMS $i)
  
  for(( j = 0; j < $(Card $VAR); j++ )); do
    
    VAL=$(Valor $VAR $j)
    unComent $VAR
    Seta $VAR $VAL
    
    Linha="${2}$VAL$(Space $VAR $VAL " ") "
#     echo "$i $j $Linha"
    
    ((i++))
    
    if [[ "$i" = "$(Card PARAMS)" ]]; then
      echo -n "$Linha" >> $INFO
      echo "$Linha"

# echo -n "scip.sh $DATA" >> $INFO
      
      scip.sh $DATA $INFO
      echo -n -e "\n" >> $INFO
      else
        NaoExclud $i "$Linha" $j
    fi
    
    ((i--))
  done;
  j=$3
  ((i--))
  VAR=$(Valor PARAMS $i)
  ((i++))
}

for(( k = 0; k < $(Card PARAMSxcld); k++ )); do
  
  VAR=$(Valor PARAMSxcld $k)
  Coment $VAR
  
done;

echo -n "Trn " > $INFO
for(( k = 0; k < $(Card PARAMS); k++ )); do echo -n "$(Valor PARAMS $k) " >> $INFO; done
echo -n -e "Time\tOBJ\tLB\n" >> $INFO


for(( k = 0; k < $(Card PARAMSxcld); k++ )); do
  
  VARx=$(Valor PARAMSxcld $k)
  unComent $VARx
  
  for(( l = 0; l < $(Card $VARx); l++ )); do
    
    VALx=$(Valor $VARx $l)
    Seta $VARx $VALx
    
    Linha="$VARx$(Space Trn $VARx " ") "
    
    NaoExclud 0 "$Linha" 0
    
  done;
  
  Coment $VARx
done;










