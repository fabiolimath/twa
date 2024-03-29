
# cluster 2 :
# 27 10 23 24 3 19 

data;

# N�mero de n�s.
param N  := 6 ;

param gl := 1 ;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  :=
1  0 882.552 1260.02 1323.05 1109.34 1225.24 
2  1031.99 0 56.674 65.0355 45.5617 83.1411 
3  1211.48 50.6886 0 85.7122 52.9455 58.87 
4  1014.87 33.3082 9.69419 0 48.337 8.22001 
5  1432.87 60.9089 93.0324 92.6283 0 62.2861 
6  1236.64 21.2935 99.0505 4.991 80.4661 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  :=
1  0 37.522 36.5177 1.87964 20.5088 18.6914 
2  37.522 0 9.62207 35.6447 44.2315 25.8133 
3  36.5177 9.62207 0 34.6819 38.6242 20.8968 
4  1.87964 35.6447 34.6819 0 20.6598 17.2098 
5  20.5088 44.2315 38.6242 20.6598 0 18.4201 
6  18.6914 25.8133 20.8968 17.2098 18.4201 0 
;


param HmaxLB := 5927.85 ;
param FTnetLB := 12928.8 ;
param Wc := 2 ;
param TIFgap := 0.4 ;
param HmaxHLDA := 0.171481 ;
param HmaxRLDA := 0.0954131 ;
param HmaxMaxA := 0.179325 ;
param HmaxM := 0.132709 ;
param HmaxD := 0.0263796 ;
param FTnetHLDA := 1.07248 ;
param FTnetRLDA := 0.883198 ;
param FTnetMaxA := 1.08961 ;
param FTnetM := 0.986282 ;
param FTnetD := 0.0556578 ;
end ;