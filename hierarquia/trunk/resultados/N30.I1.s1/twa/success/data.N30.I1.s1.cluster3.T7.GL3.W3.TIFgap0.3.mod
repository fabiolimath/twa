
# cluster 3 :
# 9 18 2 21 29 16 17 

data;

# N�mero de n�s.
param N  := 7 ;

param gl := 3 ;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  7  :=
1  0 1285.03 1002.49 1231.79 1049.79 1458.88 1235.73 
2  1241.5 0 89.1532 43.2514 46.7561 30.8582 82.0977 
3  1103.3 9.71585 0 7.64516 1.73592 3.67143 84.0079 
4  1093.26 0.788636 18.1294 0 0.360787 49.6703 92.1024 
5  1122.17 30.0698 26.7983 80.2644 0 90.0631 30.3834 
6  867.577 80.0454 97.337 12.7363 29.8553 0 34.8637 
7  1021.29 31.2587 74.8693 1.42625 44.0369 84.7088 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  7  :=
1  0 46.3513 46.162 36.5538 21.1302 25.7717 36.7315 
2  46.3513 0 8.03556 16.0934 25.5216 23.6394 13.6378 
3  46.162 8.03556 0 21.9549 26.7019 21.1612 9.75847 
4  36.5538 16.0934 21.9549 0 16.2697 22.3602 19.7689 
5  21.1302 25.5216 26.7019 16.2697 0 11.6707 18.5127 
6  25.7717 23.6394 21.1612 22.3602 11.6707 0 11.4113 
7  36.7315 13.6378 9.75847 19.7689 18.5127 11.4113 0 
;


param HmaxLB := 2421.24 ;
param FTnetLB := 3678.7 ;
param Wc := 3 ;
param TIFgap := 0.3 ;
param HmaxHLDA := 2 ;
param HmaxRLDA := 1e-06 ;
param HmaxMaxA := 2.13359 ;
param HmaxM := 0.143028 ;
param HmaxD := 0.345897 ;
param FTnetHLDA := 3.58872 ;
param FTnetRLDA := 0.838783 ;
param FTnetMaxA := 4.13243 ;
param FTnetM := 1.27124 ;
param FTnetD := 0.403314 ;
end ;