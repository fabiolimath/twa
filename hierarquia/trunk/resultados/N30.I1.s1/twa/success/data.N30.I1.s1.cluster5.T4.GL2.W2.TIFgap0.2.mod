
# cluster 5 :
# 12 4 7 1 

data;

# N�mero de n�s.
param N  := 4 ;

param gl := 2 ;
# Matriz de Demandas.
param D :  1  2  3  4  :=
1  0 1415.36 1345.3 1435.46 
2  1396.53 0 28.1463 26.8897 
3  1332.21 58.0406 0 50.9733 
4  1418.51 15.2497 81.4976 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  :=
1  0 17.3146 52.4324 12.101 
2  17.3146 0 35.344 19.5501 
3  52.4324 35.344 0 53.5653 
4  12.101 19.5501 53.5653 0 
;


param HmaxLB := 2098.06 ;
param FTnetLB := 1438.41 ;
param Wc := 2 ;
param TIFgap := 0.2 ;
param HmaxHLDA := 1e-06 ;
param HmaxRLDA := 1e-06 ;
param HmaxMaxA := 1.05226 ;
param HmaxM := 0.350145 ;
param HmaxD := 0.457191 ;
param FTnetHLDA := 1.04695 ;
param FTnetRLDA := 0.89073 ;
param FTnetMaxA := 2.93563 ;
param FTnetM := 1.40953 ;
param FTnetD := 0.660994 ;
end ;