
# cluster 1:
# 13 3 19 

data;

# Número de nós.
param N  := 3;

param HmaxLB := 1862.34;
param gl := 1;
# Matriz de Demandas.
param D :  1  2  3  :=
1  0 856.726 1005.61 
2  984.843 0 53.0378 
3  711.418 50.903 0 
;

# Matriz de Distancias.
param C :  1  2  3  :=
1  0 38.8593 29.9715 
2  38.8593 0 23.7648 
3  29.9715 23.7648 0 
;

end;
