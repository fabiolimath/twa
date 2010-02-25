#!/usr/bin/awk -f 

BEGIN{min=10^100} 
$1<min{min=$1} 
END{print min}