
# cluster 1 :
# 6 8 15 25 26 

data;

# N�mero de n�s.
param N  := 5 ;

param gl := 1 ;
# Matriz de Demandas.
param D :  1  2  3  4  5  :=
1  0 1393.28 1180.22 1445.56 1188.72 
2  1411.71 0 86.3691 29.4669 21.3532 
3  1148.21 78.7985 0 76.0851 64.6574 
4  1529.94 49.7523 31.7869 0 95.4915 
5  1473.49 89.1347 37.0482 24.1299 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  :=
1  0 38.7279 24.6848 44.6714 29.9551 
2  38.7279 0 24.0556 11.7121 20.0719 
3  24.6848 24.0556 0 34.7819 30.6941 
4  44.6714 11.7121 34.7819 0 18.1877 
5  29.9551 20.0719 30.6941 18.1877 0 
;


param HmaxLB := 5563.35 ;
param FTnetLB := 8471.66 ;
param Wc     := 1 ;
param TIFgap := 0.1 ;
param HmaxHLDA := 0.0653532 ;
param HmaxRLDA := 0.0525261 ;
param HmaxMaxA := 0.0815911 ;
param HmaxM := 0.0649768 ;
param HmaxD := 0.00747102 ;
param FTnetHLDA := 1.02826 ;
param FTnetRLDA := 0.947989 ;
param FTnetMaxA := 1.10855 ;
param FTnetM := 1.02957 ;
param FTnetD := 0.0424041 ;
end ;