
# cluster 5:
# 3 7 14 

data;

# Número de nós.
param N  := 3;

# Matriz de Demandas.
param D :  1  2  3  :=
1  0 1524.02 1902.43 
2  1977.79 0 11.2556 
3  1830.9 38.9248 0 
;

# Matriz de Distancias.
param C :  1  2  3  :=
1  0 1.43053 44.2627 
2  1.43053 0 44.8334 
3  44.2627 44.8334 0 
;

end;
