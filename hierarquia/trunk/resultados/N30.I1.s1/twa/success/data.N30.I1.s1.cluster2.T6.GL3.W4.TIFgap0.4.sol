
# cluster 2 :
# 27 10 23 24 3 19 

data;

# N�mero de n�s.
param N  := 6 ;

param gl := 3 ;
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


param HmaxLB := 1975.95 ;
param FTnetLB := 2365.16 ;
param Wc := 4 ;
param TIFgap := 0.4 ;
param HmaxHLDA := 0.162903 ;
param HmaxRLDA := 1e-06 ;
param HmaxMaxA := 2.15631 ;
param HmaxM := 0.240789 ;
param HmaxD := 0.455304 ;
param FTnetHLDA := 1.54129 ;
param FTnetRLDA := 0.859554 ;
param FTnetMaxA := 4.59018 ;
param FTnetM := 1.49262 ;
param FTnetD := 0.561033 ;
param b := 
[1,1,4,*] 1 1
[1,1,4,*] 2 1
[1,1,4,*] 3 1
[1,1,4,*] 4 1
[1,2,3,*] 2 1
[1,3,2,*] 1 1
[1,3,2,*] 2 1
[1,4,6,*] 1 1
[1,4,6,*] 3 1
[1,4,6,*] 4 1
[1,6,3,*] 1 1
[1,6,5,*] 3 1
[2,2,3,*] 1 1
[2,2,3,*] 3 1
[2,2,3,*] 4 1
[2,3,6,*] 3 1
[2,3,6,*] 4 1
[3,3,6,*] 1 1
[3,3,6,*] 2 1
[3,4,1,*] 2 1
[3,5,6,*] 2 1
[3,5,6,*] 4 1
[3,6,4,*] 1 1
[3,6,4,*] 2 1
[3,6,5,*] 2 1
[3,6,5,*] 4 1
[4,4,1,*] 1 1
[4,4,6,*] 2 1
[4,6,3,*] 2 1
[5,4,1,*] 3 1
[5,5,6,*] 1 1
[5,5,6,*] 3 1
[5,6,4,*] 3 1
[6,3,2,*] 3 1
[6,4,1,*] 4 1
[6,6,3,*] 3 1
[6,6,3,*] 4 1
[6,6,4,*] 4 1
;
param qw := 
[1,2,1,*] 1 0.264640394478756
[1,2,3,*] 1 0.0750557496
[1,2,4,*] 1 0.0372641012000002
[1,4,1,*] 2 0.329174700316065
[1,4,5,*] 2 0.0531819102589344
[1,5,1,*] 3 0.1912588562
[1,5,2,*] 3 0.0355283986559572
[1,5,3,*] 3 0.0362715861
[1,5,4,*] 3 0.043373766
[1,5,6,*] 3 0.0557846695
[1,6,1,*] 4 0.214926049050512
[2,6,1,*] 4 0.112481555827034
[2,6,2,*] 3 1
[2,6,3,*] 3 0.0403303071
[2,6,4,*] 4 0.0073759809
[3,1,3,*] 2 0.941280799261509
[3,1,6,*] 2 0.272281305140213
[3,4,2,*] 1 0.0507138049050665
[3,4,3,*] 1 0.0587192007414238
[3,4,6,*] 1 0.0034601066
[4,1,4,*] 1 0.9913012076
[4,3,1,*] 2 0.101070575716065
[4,3,4,*] 2 0.0086987924
[5,1,5,*] 3 0.8758545045
[5,6,5,*] 1 0.1241454955
[6,1,2,*] 4 0.840260267850891
[6,1,6,*] 4 0.640827798659787
[6,2,5,*] 3 0.0349704319
[6,2,6,*] 3 0.0147621279
[6,3,1,*] 4 0.116166685977546
[6,3,2,*] 4 0.0949074250050665
[6,3,5,*] 4 0.0534139216
[6,3,6,*] 4 0.34441007350954
;
end;