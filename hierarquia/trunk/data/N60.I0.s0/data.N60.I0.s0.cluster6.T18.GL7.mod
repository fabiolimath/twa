
# cluster 6:
# 18 0 36 19 56 1 43 24 13 59 55 44 31 10 17 37 45 33 

data;

# N�mero de n�s.
param N  := 18;

param HmaxLB := 5431.93;
param gl := 7;
# Matriz de Demandas.
param D :  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  :=
1  0 2409.2 2121.91 2514.84 2024.03 2329.19 2486.82 2063.99 2414.01 2138.76 1813.07 2326.49 2464.83 2392.94 2398.25 2083.55 1714.45 2327.15 
2  2102.89 0 20.4696 15.5427 3.75469 0 46.4847 21.0406 40.1156 91.2179 53.8621 80.0462 98.6314 45.9562 43.756 57.8357 46.5909 81.0785 
3  2222.95 36.5924 0 85.3092 40.7311 51.4034 97.1802 94.8451 4.18127 20.5131 67.4352 5.26591 45.7503 2.9554 18.6284 52.9087 77.0011 59.0174 
4  1887.84 58.2642 72.1035 0 62.9645 38.1943 98.5349 82.4419 71.1772 17.1729 13.5461 17.4425 92.5449 78.2964 35.7721 15.4788 29.3129 60.9759 
5  1931.57 40.3752 97.5326 88.789 0 75.5442 1.9243 28.2905 87.8171 63.3881 30.9233 37.2575 65.1472 12.2278 75.039 41.5786 11.8659 97.6204 
6  2381.68 0 83.9318 98.6771 24.5673 0 10.169 24.2781 30.4401 95.2236 6.06616 68.1371 62.8295 12.6488 25.1033 58.0965 86.6394 92.822 
7  2052.53 36.6193 94.1292 78.6194 54.5527 81.0587 0 28.0897 22.6737 0.248295 70.2399 67.8886 55.7224 27.0995 38.7734 4.87597 90.5047 37.8849 
8  2375.96 10.6193 15.02 17.3101 38.6834 13.299 18.0793 0 65.269 59.1079 84.9603 90.7709 5.98699 17.3185 90.0142 8.74649 95.3497 76.286 
9  2097.94 95.7239 48.5664 16.9464 75.2344 96.6032 80.5651 28.7871 0 41.5485 6.21988 0.265884 1.14524 63.913 1.20958 75.2177 61.9866 46.7536 
10 2095.46 85.3905 79.7294 18.4453 39.7906 76.8341 62.8403 41.8129 70.6578 0 17.1262 89.4317 71.4082 57.9245 31.4184 29.9682 40.4343 3.46284 
11 2060.13 97.2893 1.21412 93.1668 16.0724 87.8484 40.0087 97.0368 42.525 69.0334 0 44.1187 71.5585 50.1696 1.41309 28.548 19.8755 98.4159 
12 2330.73 82.1227 42.1547 35.7471 53.479 4.19849 1.20323 28.7259 70.7614 59.7618 39.5192 0 94.6186 41.8473 30.0113 17.3661 83.5309 19.4564 
13 2262.13 95.8425 14.3003 66.9082 74.4536 73.4049 73.1577 42.1202 82.1602 51.2603 53.1314 61.9381 0 78.49 48.413 75.5366 96.3225 0.537918 
14 1879.98 90.7734 25.2118 40.0242 0.842563 99.5934 82.3902 6.8776 17.8916 5.52203 82.7113 77.9724 58.1836 0 63.8071 95.7578 53.3796 44.3233 
15 2127.08 11.8115 42.386 67.7709 13.5071 70.0889 55.8002 58.4704 34.7355 50.914 69.114 3.31447 29.9588 72.0051 0 96.5738 37.4827 51.3489 
16 2173.7 75.0864 62.4861 98.1238 33.848 76.8302 19.6064 64.3906 74.7513 60.7593 75.503 95.0537 69.9291 44.6956 71.8433 0 49.893 16.0919 
17 2203.32 19.1719 60.1737 35.767 17.023 3.85922 53.6641 75.0297 91.0236 29.5866 3.04866 50.134 90.8854 63.6945 87.8449 44.3982 0 87.4242 
18 2493.11 5.44846 82.9752 72.9772 49.808 32.3096 54.3466 36.3433 99.1411 9.26683 64.4272 54.0043 19.6727 68.7019 41.9073 90.4687 86.2684 0 
;

# Matriz de Distancias.
param C :  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  :=
1  0 84.0693 63.6132 18.3816 64.0596 55.6923 49.475 40.521 89.3216 28.9005 69.8365 10.2396 52.4292 60.0699 39.198 36.3447 58.8301 37.5193 
2  84.0693 0 123.042 75.9365 75.3386 0 109.578 43.5809 99.8963 89.275 104.199 76.7671 74.2813 101.944 48.7879 78.0359 47.3986 93.9268 
3  63.6132 123.042 0 81.781 56.7526 71.7729 14.8604 86.5433 59.6348 38.1636 32.2006 72.9623 51.2259 25.649 76.3899 45.3083 77.9374 30.6545 
4  18.3816 75.9365 81.781 0 74.3059 60.5751 67.4224 35.0229 101.732 45.624 85.1829 8.9893 63.3624 76.0581 39.4273 49.414 61.9757 54.345 
5  64.0596 75.3386 56.7526 74.3059 0 23.1762 48.1549 54.4873 29.1022 42.199 29.9308 66.8296 11.7279 31.3904 42.4217 28.6393 28.2904 38.9644 
6  55.6923 0 71.7729 60.5751 23.1762 0 59.7539 33.6219 51.2357 44.3741 50.9497 54.9354 21.1876 49.0075 22.7301 29.943 6.17785 45.7499 
7  49.475 109.578 14.8604 67.4224 48.1549 59.7539 0 71.9702 58.1479 23.3034 30.8535 58.5241 40.4124 20.9144 62.1619 31.542 65.8178 16.0507 
8  40.521 43.5809 86.5433 35.0229 54.4873 33.6219 71.9702 0 83.5595 49.415 76.3692 33.86 47.0363 70.52 12.2311 42.1468 32.2079 55.9376 
9  89.3216 99.8963 59.6348 101.732 29.1022 51.2357 58.1479 83.5595 0 63.0708 27.781 93.6858 38.5833 37.2445 71.5221 53.0299 55.3275 56.6598 
10 28.9005 89.275 38.1636 45.624 42.199 44.3741 23.3034 49.415 63.0708 0 41.2147 36.6362 30.9679 31.2183 40.6943 14.8612 49.7639 8.72485 
11 69.8365 104.199 32.2006 85.1829 29.9308 50.9497 30.8535 76.3692 27.781 41.2147 0 76.3974 30.4875 10.6265 64.3546 36.5785 56.8103 33.1889 
12 10.2396 76.7671 72.9623 8.9893 66.8296 54.9354 58.5241 33.86 93.6858 36.6362 76.3974 0 55.6052 67.1604 35.4227 40.9784 57.0712 45.3582 
13 52.4292 74.2813 51.2259 63.3624 11.7279 21.1876 40.4124 47.0363 38.5833 30.9679 30.4875 55.6052 0 27.821 34.8147 16.9654 27.3193 28.8526 
14 60.0699 101.944 25.649 76.0581 31.3904 49.0075 20.9144 70.52 37.2445 31.2183 10.6265 67.1604 27.821 0 58.9193 28.9681 55.1383 22.8929 
15 39.198 48.7879 76.3899 39.4273 42.4217 22.7301 62.1619 12.2311 71.5221 40.6943 64.3546 35.4227 34.8147 58.9193 0 31.2523 22.8311 46.1604 
16 36.3447 78.0359 45.3083 49.414 28.6393 29.943 31.542 42.1468 53.0299 14.8612 36.5785 40.9784 16.9654 28.9681 31.2523 0 35.6158 16.1858 
17 58.8301 47.3986 77.9374 61.9757 28.2904 6.17785 65.8178 32.2079 55.3275 49.7639 56.8103 57.0712 27.3193 55.1383 22.8311 35.6158 0 51.5926 
18 37.5193 93.9268 30.6545 54.345 38.9644 45.7499 16.0507 55.9376 56.6598 8.72485 33.1889 45.3582 28.8526 22.8929 46.1604 16.1858 51.5926 0 
;

end;
