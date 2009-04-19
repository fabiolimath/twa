
# cluster 2:
# 22 5 9 30 57 2 41 26 51 16 48 32 27 14 50 54 20 

data;

# N�mero de n�s.
param N  := 17;

param HmaxLB := 11844.8;
param gl := 3;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  :=
1  0 2368.29 1757.13 2252.89 2164.95 2188.51 2406.65 2384.19 2336.56 2387.46 2197.51 2409.76 2515.12 1914.69 2006.74 2355.53 2033.34 
2  2016.62 0 62.5844 17.6398 62.5305 55.1069 48.6562 84.8563 17.4074 12.7358 20.6873 68.8268 73.217 62.1348 50.8198 60.7486 95.0728 
3  2230.43 32.1898 0 7.8181 5.17519 32.5222 37.0812 66.9934 25.7031 90.5019 89.9469 68.4999 88.7404 36.5283 65.9767 23.4173 10.0597 
4  2129.69 18.6021 61.2356 0 33.1119 77.1121 3.98336 64.212 48.5387 45.6697 46.0647 82.7263 89.3811 84.667 66.3708 4.58963 96.9455 
5  2627.83 60.3399 89.3058 91.4435 0 94.7615 71.0671 83.9771 3.5162 4.97736 86.2487 62.6859 77.4974 8.86515 95.7581 41.556 20.0238 
6  2014.57 36.9997 59.0057 35.0966 12.576 0 47.8752 33.9066 43.8317 7.42642 2.22546 29.7589 15.4053 31.2771 60.695 53.4805 95.6193 
7  2073.93 58.5801 88.075 31.4563 61.8077 5.23416 0 51.6856 44.334 60.1305 52.1248 24.4926 45.5282 38.0878 59.339 24.9484 32.6696 
8  1914.02 35.7905 35.4854 43.3204 60.4807 90.3294 35.3664 0 2.91968 40.7337 98.0576 81.791 50.7 13.9755 11.5437 12.0656 49.6827 
9  2174.68 20.7767 38.0382 9.81157 34.4321 76.7638 75.8669 81.0878 0 87.4545 33.868 17.8218 29.744 70.1714 64.328 97.619 0.83382 
10 2026.71 22.8821 50.0153 3.45967 84.5707 60.0972 94.0029 28.4209 76.7815 0 23.9995 93.7548 95.4783 82.6236 39.2401 34.9296 14.9434 
11 2179.82 12.6268 0.779312 3.82839 48.5011 4.84487 9.64238 3.36705 99.4873 60.838 0 65.8588 63.4972 51.0832 78.7423 55.6748 17.7248 
12 2183.4 8.7167 37.4883 59.0184 93.1805 31.2067 75.7975 18.5124 69.2772 89.7235 31.0727 0 64.7837 90.6032 80.9969 14.6946 30.2303 
13 2268.89 68.3356 10.8341 86.2406 15.8183 84.6794 3.56036 42.2306 66.476 79.972 16.4007 61.6459 0 58.8617 76.7427 7.80808 67.5462 
14 2368.64 9.75387 86.3063 55.7716 60.7644 24.511 29.8526 48.0688 15.811 59.7314 10.444 24.4664 44.4875 0 0.334168 79.845 3.41355 
15 2026.15 68.6165 70.6709 53.5606 31.7869 17.6502 4.77073 65.0442 8.84327 62.1328 0.571662 16.9106 24.7585 2.68993 0 14.9322 9.28716 
16 2570.63 37.5599 20.1259 83.7453 16.8548 61.7036 8.46778 29.4939 48.0751 35.495 55.6858 73.7426 62.0994 17.6542 32.9766 0 32.1164 
17 2373.76 78.7584 15.7646 15.0613 6.37629 25.5905 84.9539 45.5681 93.1267 24.7124 97.0768 92.8418 75.1413 89.6479 38.165 78.6473 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  :=
1  0 27.0828 60.1162 36.586 68.8571 32.9857 23.4538 47.7108 49.8723 58.3485 13.0314 63.624 12.7583 80.4973 22.3776 56.5956 19.1422 
2  27.0828 0 48.2485 53.8029 43.1421 39.8043 42.2631 56.1318 37.7171 59.8029 16.3497 73.2477 35.6619 61.4564 29.0538 29.7398 28.1953 
3  60.1162 48.2485 0 54.2764 42.1015 35.9442 53.145 39.8896 10.7469 28.8051 58.6633 50.513 72.8275 26.2674 39.7417 45.998 42.8372 
4  36.586 53.8029 54.2764 0 83.4955 19.5765 13.1471 19.0922 48.5462 35.1534 47.3428 29.7497 44.7624 80.2959 25.4503 76.8167 25.6529 
5  68.8571 43.1421 42.1015 83.4955 0 64.2675 76.1245 75.7653 39.1159 69.3136 59.4749 89.9389 78.7039 32.6607 59.6542 15.6717 61.096 
6  32.9857 39.8043 35.9442 19.5765 64.2675 0 17.6333 16.4959 29.1718 25.4413 39.0472 33.6203 44.8538 61.4214 11.8484 58.7487 14.4524 
7  23.4538 42.2631 53.145 13.1471 76.1245 17.6333 0 26.94 45.2774 40.9072 34.3704 41.1917 32.3358 77.9282 16.4852 67.6069 15.2576 
8  47.7108 56.1318 39.8896 19.0922 75.7653 16.4959 26.94 0 37.2859 16.2453 55.1893 17.1396 58.5106 66.0727 28.2115 72.5816 30.477 
9  49.8723 37.7171 10.7469 48.5462 39.1159 29.1718 45.2774 37.2859 0 30.4834 47.9403 50.826 62.5105 32.6614 30.5408 39.4329 33.4371 
10 58.3485 59.8029 28.8051 35.1534 69.3136 25.4413 40.9072 16.2453 30.4834 0 63.0876 21.7962 70.2927 53.6545 36.371 69.5047 39.4102 
11 13.0314 16.3497 58.6633 47.3428 59.4749 39.0472 34.3704 55.1893 47.9403 63.0876 0 71.9709 19.347 75.6305 27.2209 45.9299 24.7161 
12 63.624 73.2477 50.513 29.7497 89.9389 33.6203 41.1917 17.1396 50.826 21.7962 71.9709 0 73.5155 75.3768 45.2434 88.3256 47.3426 
13 12.7583 35.6619 72.8275 44.7624 78.7039 44.8538 32.3358 58.5106 62.5105 70.2927 19.347 73.5155 0 92.6476 34.8889 65.273 31.6095 
14 80.4973 61.4564 26.2674 80.2959 32.6607 61.4214 77.9282 66.0727 32.6614 53.6545 75.6305 75.3768 92.6476 0 62.986 44.8158 65.7188 
15 22.3776 29.0538 39.7417 25.4503 59.6542 11.8484 16.4852 28.2115 30.5408 36.371 27.2209 45.2434 34.8889 62.986 0 51.6503 3.29128 
16 56.5956 29.7398 45.998 76.8167 15.6717 58.7487 67.6069 72.5816 39.4329 69.5047 45.9299 88.3256 65.273 44.8158 51.6503 0 52.3572 
17 19.1422 28.1953 42.8372 25.6529 61.096 14.4524 15.2576 30.477 33.4371 39.4102 24.7161 47.3426 31.6095 65.7188 3.29128 52.3572 0 
;

end;
