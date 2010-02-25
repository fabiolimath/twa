
# cluster 3 :
# 9 18 2 21 29 16 17 

data;

# N�mero de n�s.
param N  := 7 ;

param gl := 1 ;
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


param HmaxLB := 7263.71 ;
param FTnetLB := 19424.8 ;
param Wc := 1 ;
param TIFgap := 0.3 ;
param HmaxHLDA := 0.102493 ;
param HmaxRLDA := 0.0647077 ;
param HmaxMaxA := 0.136588 ;
param HmaxM := 0.10053 ;
param HmaxD := 0.014466 ;
param FTnetHLDA := 0.947345 ;
param FTnetRLDA := 0.81798 ;
param FTnetMaxA := 1.04859 ;
param FTnetM := 0.935506 ;
param FTnetD := 0.056915 ;
param b := 
[1,1,5,*] 1 1
[1,5,4,*] 1 1
[2,2,3,*] 1 1
[3,3,7,*] 1 1
[4,4,5,*] 1 1
[4,5,7,*] 1 1
[4,7,6,*] 1 1
[5,5,1,*] 1 1
[6,3,2,*] 1 1
[6,6,7,*] 1 1
[6,7,3,*] 1 1
[7,7,5,*] 1 1
;
param qw := 
[1,4,1,*] 1 1
[1,4,2,*] 1 0.0483234206000001
[1,4,3,*] 1 0.0173810863999999
[1,4,5,*] 1 0.1866854044
[1,4,6,*] 1 0.011347232
[1,4,7,*] 1 0.1528821456
[2,3,1,*] 1 0.4526626201
[2,3,2,*] 1 1
[2,3,4,*] 1 0.95977160766
[2,3,5,*] 1 0.0414435524
[2,3,6,*] 1 0.9286846474
[2,3,7,*] 1 0.0595339522
[3,7,1,*] 1 0.3146491256
[3,7,2,*] 1 0.9418673481
[3,7,3,*] 1 1
[3,7,4,*] 1 0.94531794156
[3,7,5,*] 1 0.0220209618
[3,7,6,*] 1 0.8419635808
[4,6,1,*] 1 0.8304186153
[4,6,2,*] 1 0.0201211959000001
[4,6,3,*] 1 0.0110631705
[4,6,4,*] 1 1
[4,6,5,*] 1 0.1285122149
[4,6,7,*] 1 0.1517480319
[5,1,2,*] 1 0.8578477828
[5,1,3,*] 1 0.9291418047
[5,1,4,*] 1 0.8716016555
[5,1,5,*] 1 1
[5,1,6,*] 1 0.7843030744
[5,1,7,*] 1 0.9649831011
[6,2,1,*] 1 0.6295735926
[6,2,3,*] 1 0.0080291221
[6,2,4,*] 1 0.9604003478
[6,2,5,*] 1 0.0632372265
[6,2,6,*] 1 1
[6,2,7,*] 1 0.0843899873
[7,5,1,*] 1 0.1445253183
[7,5,2,*] 1 0.8883352593
[7,5,3,*] 1 0.9305763589
[7,5,4,*] 1 0.87188929296
[7,5,6,*] 1 0.8109022449
[7,5,7,*] 1 1
;
end;
