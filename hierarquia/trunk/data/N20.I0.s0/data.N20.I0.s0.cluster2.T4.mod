
# cluster 2:
# 9 0 16 12 

data;

# N�mero de n�s.
param N  := 4;

# Matriz de Demandas.
param D :  1  2  3  4  :=
1  0 690.593 736.306 899.775 
2  755.685 0 92.0176 43.6598 
3  799.848 84.0935 0 3.90209 
4  808.272 70.042 67.7105 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  :=
1  0 71.5039 38.1196 57.0393 
2  71.5039 0 101.772 18.6392 
3  38.1196 101.772 0 84.3047 
4  57.0393 18.6392 84.3047 0 
;

end;