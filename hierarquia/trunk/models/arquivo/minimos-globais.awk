#!/usr/bin/awk -f

BEGIN{
   Db=1000000000;
   Dc=1000000000;
   T=1000000000;
   F=1000000000
}     

$1<Db{Db=$1;} 
$2<Dc{Dc=$2;} 
$3<T{T=$3;} 
$4<F{F=$4;} 

END{print Db, Dc, T, F;}



