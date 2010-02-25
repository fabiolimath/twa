
# cluster 1 :
# 6 8 15 25 26 

data;

# N�mero de n�s.
param N  := 5 ;

param gl := 2 ;
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


param HmaxLB := 2781.67 ;
param FTnetLB := 2703.22 ;
param Wc := 2 ;
param TIFgap := 0.2 ;
param HmaxHLDA := 0.0358158 ;
param HmaxRLDA := 1e-06 ;
param HmaxMaxA := 1.07892 ;
param HmaxM := 0.158938 ;
param HmaxD := 0.349931 ;
param FTnetHLDA := 1.72912 ;
param FTnetRLDA := 0.930212 ;
param FTnetMaxA := 3.30632 ;
param FTnetM := 1.42234 ;
param FTnetD := 0.572689 ;
end ;