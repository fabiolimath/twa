
# cluster 3:
# 32 13 28 21 

data;

# N�mero de n�s.
param N  := 4;

# Matriz de Demandas.
param D :  1  2  3  4  :=
1  0 1974.49 1685.1 2063.63 
2  1576 0 74.2157 33.3088 
3  2149.9 37.1492 0 69.3219 
4  2017.11 44.293 69.4445 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  :=
1  0 59.7039 51.896 22.0551 
2  59.7039 0 47.8583 66.5678 
3  51.896 47.8583 0 71.6332 
4  22.0551 66.5678 71.6332 0 
;

end;
