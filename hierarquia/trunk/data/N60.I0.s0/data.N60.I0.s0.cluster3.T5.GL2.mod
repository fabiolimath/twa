
# cluster 3:
# 47 8 39 29 12 

data;

# N�mero de n�s.
param N  := 5;

param HmaxLB := 5621.83;
param gl := 2;
# Matriz de Demandas.
param D :  1  2  3  4  5  :=
1  0 2539.73 2783.6 2806.06 2634.13 
2  3119.81 0 50.9478 59.8428 45.8687 
3  2826.84 90.1245 0 20.5965 72.8119 
4  2784.58 26.5923 65.2038 0 53.4288 
5  2540.6 82.7082 94.8822 19.5849 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  :=
1  0 35.1482 63.8172 63.7269 65.8678 
2  35.1482 0 31.0458 29.3317 38.7119 
3  63.8172 31.0458 0 7.17553 15.8107 
4  63.7269 29.3317 7.17553 0 22.977 
5  65.8678 38.7119 15.8107 22.977 0 
;

end;
