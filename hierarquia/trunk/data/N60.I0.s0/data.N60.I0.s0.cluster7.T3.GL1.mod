
# cluster 7:
# 58 21 46 

data;

# Número de nós.
param N  := 3;

param HmaxLB := 5892.41;
param gl := 1;
# Matriz de Demandas.
param D :  1  2  3  :=
1  0 2673.06 2812.94 
2  2760.1 0 66.6343 
3  3132.31 15.5076 0 
;

# Matriz de Distancias.
param C :  1  2  3  :=
1  0 9.8935 98.6481 
2  9.8935 0 102.347 
3  98.6481 102.347 0 
;

end;
