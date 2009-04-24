
# cluster 1:
# 40 34 42 15 35 6 23 

data;

# N�mero de n�s.
param N  := 7;

param HmaxLB := 5652.23;
param gl := 3;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  7  :=
1  0 2954.11 2939.99 2697.56 2881.82 2720.38 2805.32 
2  2915.62 0 96.1107 40.907 83.6347 67.1881 61.1573 
3  3129.35 78.1259 0 78.0245 56.8083 42.8395 93.4888 
4  2762.04 45.5502 1.03393 0 44.6364 72.3021 8.27781 
5  3005.55 66.6025 46.6453 90.6383 0 44.949 60.9363 
6  2584.94 16.7386 99.9759 60.1098 28.1961 0 8.42181 
7  2545.75 75.7806 41.1256 90.1611 21.6834 5.59588 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  7  :=
1  0 36.3116 35.8529 3.50056 31.1311 42.1025 20.4724 
2  36.3116 0 63.6301 38.0779 36.7542 36.4567 37.8366 
3  35.8529 63.6301 0 32.3719 66.7681 44.3949 55.3834 
4  3.50056 38.0779 32.3719 0 34.6259 40.6408 23.8559 
5  31.1311 36.7542 66.7681 34.6259 0 63.7618 12.0127 
6  42.1025 36.4567 44.3949 40.6408 63.7618 0 58.0165 
7  20.4724 37.8366 55.3834 23.8559 12.0127 58.0165 0 
;

end;