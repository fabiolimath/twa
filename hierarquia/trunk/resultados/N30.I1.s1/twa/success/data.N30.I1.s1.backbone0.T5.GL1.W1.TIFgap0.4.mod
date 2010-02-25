
# backbone 0 :
# 6 27 9 14 12 

data;

# N�mero de n�s.
param N  := 5 ;

param gl := 1 ;
# Matriz de Demandas.
param D :  1  2  3  4  5  :=
1  0 1575.91 1877.91 2091.2 927.723 
2  1512.45 0 2183.71 2065.3 1264.17 
3  1660.95 1676.98 0 2471.37 1368.08 
4  2145.33 2627.81 2444.5 0 1679.02 
5  1051.09 1086.97 1522.74 1749.84 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  :=
1  0 80.2682 21.0871 80.1065 5.08875 
2  74.9635 0 16.0326 85.3782 55.2272 
3  0.154804 89.7782 0 16.1422 14.085 
4  93.7226 83.3196 48.9927 0 99.9212 
5  41.6251 34.152 68.9529 78.149 0 
;


param HmaxLB := 8896.66 ;
param FTnetLB := 44420.9 ;
param Wc := 1 ;
param TIFgap := 0.4 ;
param HmaxHLDA := 0.981888 ;
param HmaxRLDA := 0.969931 ;
param HmaxMaxA := 1.05793 ;
param HmaxM := 1.01345 ;
param HmaxD := 0.0310929 ;
param FTnetHLDA := 0.156725 ;
param FTnetRLDA := 0.147321 ;
param FTnetMaxA := 0.215287 ;
param FTnetM := 0.181153 ;
param FTnetD := 0.0232132 ;
end ;