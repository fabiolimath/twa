
# cluster 5 :
# 12 4 7 1 

data;

# N�mero de n�s.
param N  := 4 ;

param gl := 1 ;
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


param HmaxLB := 4196.12 ;
param FTnetLB := 4459.87 ;
param Wc     := 1 ;
param TIFgap := 0.1 ;
param HmaxHLDA := 0.029764 ;
param HmaxRLDA := 0.0257246 ;
param HmaxMaxA := 0.0368883 ;
param HmaxM := 0.0312585 ;
param HmaxD := 0.00337675 ;
param FTnetHLDA := 0.920794 ;
param FTnetRLDA := 0.916116 ;
param FTnetMaxA := 0.942367 ;
param FTnetM := 0.929149 ;
param FTnetD := 0.0108847 ;
end ;