
# cluster 2:
# 0 24 38 27 8 5 20 11 35 19 

data;

# N�mero de n�s.
param N  := 10;

param HmaxLB := 6810.76;
param gl := 2;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  7  8  9  10  :=
1  0 1739.73 1587.57 1403.41 1338.58 1541 1505.15 1514.49 1362.62 1670.23 
2  1568.12 0 93.0268 31.5949 17.7419 55.3311 2.6355 72.584 88.1552 69.4118 
3  1547.01 67.3887 0 51.9903 92.1789 3.41136 67.4994 21.1857 65.5819 68.5047 
4  1496.31 95.5465 70.8133 0 45.6242 52.9395 7.72088 59.1843 93.2048 31.825 
5  1775.3 14.9632 10.2013 16.6652 0 76.3524 94.7559 70.6239 36.4248 52.0377 
6  1594.76 29.0394 54.6432 13.4878 63.2586 0 73.9466 87.423 38.3185 67.4856 
7  1531.43 38.0159 4.9922 96.4247 32.8552 36.6451 0 8.5161 29.2687 33.6572 
8  1519.81 78.3938 54.3402 43.3011 54.387 27.0251 37.057 0 25.0024 88.4391 
9  1381.72 17.2927 15.7985 48.7946 75.7337 69.722 75.0457 13.0877 0 19.5734 
10 1260.23 70.581 11.8209 19.939 13.0546 67.9935 34.1423 17.6572 72.096 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  7  8  9  10  :=
1  0 7.52716 82.7284 40.3679 2.85249 6.3291 46.6218 67.3184 66.5174 37.9901 
2  7.52716 0 77.5831 34.5037 7.64547 9.50802 42.7435 59.9272 59.0547 36.6248 
3  82.7284 77.5831 0 43.451 80.4552 87.0233 37.6907 47.0524 50.8044 52.7985 
4  40.3679 34.5037 43.451 0 38.4475 44.0107 16.0313 35.1824 36.3926 25.9738 
5  2.85249 7.64547 80.4552 38.4475 0 9.13641 44.0892 66.4551 65.8095 35.1647 
6  6.3291 9.50802 87.0233 44.0107 9.13641 0 51.7025 68.3234 67.1763 43.9943 
7  46.6218 42.7435 37.6907 16.0313 44.0892 51.7025 0 47.3241 49.3654 16.3404 
8  67.3184 59.9272 47.0524 35.1824 66.4551 68.3234 47.3241 0 3.83965 60.8487 
9  66.5174 59.0547 50.8044 36.3926 65.8095 67.1763 49.3654 3.83965 0 62.289 
10 37.9901 36.6248 52.7985 25.9738 35.1647 43.9943 16.3404 60.8487 62.289 0 
;

end;
