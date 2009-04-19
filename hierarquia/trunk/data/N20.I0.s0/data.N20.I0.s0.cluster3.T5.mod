
# cluster 3:
# 6 1 15 5 17 

data;

# N�mero de n�s.
param N  := 5;

# Matriz de Demandas.
param D :  1  2  3  4  5  :=
1  0 681.455 731.521 799.081 700.963 
2  733.14 0 37.6135 61.5945 45.616 
3  928.761 95.6681 0 49.2277 92.187 
4  864.807 85.8377 79.9377 0 7.63415 
5  724.266 16.5546 15.9861 85.046 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  :=
1  0 37.9395 13.7769 50.5693 28.912 
2  37.9395 0 40.1689 22.9261 29.4403 
3  13.7769 40.1689 0 46.1981 20.1834 
4  50.5693 22.9261 46.1981 0 27.1879 
5  28.912 29.4403 20.1834 27.1879 0 
;

end;
