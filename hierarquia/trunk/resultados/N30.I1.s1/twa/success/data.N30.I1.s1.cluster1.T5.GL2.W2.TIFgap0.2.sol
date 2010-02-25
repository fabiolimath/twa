
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
param b := 
[1,1,3,*] 1 1
[1,1,3,*] 2 1
[1,2,4,*] 1 1
[1,3,2,*] 1 1
[1,3,2,*] 2 1
[1,4,5,*] 1 1
[1,5,4,*] 1 1
[2,2,3,*] 1 1
[2,2,4,*] 2 1
[3,3,1,*] 1 1
[4,2,3,*] 2 1
[4,3,1,*] 2 1
[4,4,2,*] 1 1
[4,4,2,*] 2 1
[4,4,5,*] 2 1
[5,5,4,*] 2 1
;
param qw := 
[1,2,1,*] 2 0.494164500192021
[1,2,3,*] 2 0.057611729
[1,4,1,*] 1 0.5058355
[1,4,3,*] 1 0.1029006742
[2,3,1,*] 1 0.2266263168
[2,3,2,*] 1 0.967189537545621
[2,3,4,*] 1 0.0186218198858337
[2,3,5,*] 1 0.0228157015
[2,4,2,*] 2 0.0328104631000002
[3,1,2,*] 1 0.911427936045621
[3,1,3,*] 1 1
[4,1,4,*] 2 0.8962895497
[4,1,5,*] 2 0.9074316167
[4,2,4,*] 1 0.0477683658858337
[4,2,5,*] 1 0.077708266
[4,5,1,*] 2 0.2282584902
[4,5,2,*] 2 0.0137860488
[4,5,3,*] 2 0.0472727858000001
[4,5,4,*] 2 0.055942085
[5,4,5,*] 2 1
;
end;
