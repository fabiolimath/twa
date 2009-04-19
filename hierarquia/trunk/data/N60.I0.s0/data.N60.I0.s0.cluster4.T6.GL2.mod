
# cluster 4:
# 25 11 38 49 52 7 

data;

# N�mero de n�s.
param N  := 6;

param HmaxLB := 6987.93;
param gl := 2;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  :=
1  0 2543.17 3006.95 2633.48 2534.36 2480.91 
2  2901.35 0 11.3781 55.2226 92.0154 54.549 
3  3045 70.9859 0 53.268 94.0105 94.9844 
4  2753.69 79.8851 20.5993 0 68.0604 54.738 
5  2439.93 39.2073 81.1277 83.2782 0 29.4096 
6  2877.93 23.9873 27.6442 57.8746 13.458 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  :=
1  0 62.9352 27.0131 38.3025 6.91075 4.45657 
2  62.9352 0 36.5249 36.6254 69.8359 59.1231 
3  27.0131 36.5249 0 17.0261 33.8942 22.9062 
4  38.3025 36.6254 17.0261 0 44.4831 33.8488 
5  6.91075 69.8359 33.8942 44.4831 0 11.0706 
6  4.45657 59.1231 22.9062 33.8488 11.0706 0 
;

end;
