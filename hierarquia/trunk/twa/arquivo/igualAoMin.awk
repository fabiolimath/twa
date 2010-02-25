#!/usr/bin/awk -f 

BEGIN{
   ub=0.0266542
   cont=0
} 

$1<=ub{cont++}

END{print cont}