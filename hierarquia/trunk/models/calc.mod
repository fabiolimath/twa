
# 1 - Numero de nós da Rede.
param N 'Numero de nós' default 4, integer, > 0;

# 2 - Grau Físico de Saida e Entrada dos nós.
param H default 0, integer, >= 0;

# 3 - Número de Comprimentos de Onda disponíveis em cada Ligação Física.
param Wc default 2, integer, >0;

# 4 - Grau Lógico.
param Gl default 0;
param Gle default 0;

# 5 - Conjuntos de Indices.
set I := 1..N;
set W := 1..Wc;

# 6 - Número máximo de cores em cada ligação física.
param L default 0, integer, >=0;

# 7 - Número máximo de saltos físicos
param MB default 0, integer, >=0;

###################### Outros Parâmetros ####################


param HmaxLB default 0;
param HmaxM default 0;
param gl default 0;
param rCIPF default 0;

# 1 - Matriz de Trafego.
param D 'Matriz de Trafego' {i in I, j in I} default 2;

# 2 - Ligações Físicas Direcionadas - Versão Parâmetro.
param Hd {i in I, j in I} default 1, binary;

# 1 - Matriz de Trafego.
param C {i in I, j in I} default 2;

param mediaD default (sum{i in I, j in I: i!=j} D[i,j])/(N*N - N);
param mediaC default (sum{i in I, j in I: i!=j} C[i,j])/(N*N - N);
param razaoDC default (mediaD*(N*N - N)/2)/(mediaC*N*gl);

# param razaoFis default (sum{i in I, j in I} Hd[i,j]*C[i,j])/(sum{i in I, j in I} C[i,j]);

printf("\n");
printf("Média D: ");
printf(mediaD);
printf("\n");
printf("\n");
printf("Média C: ");
printf(mediaC);
printf("\n");
printf("\n");
printf("Razão D/C: ");
printf(razaoDC);
printf("\n");
printf("\n");
/**/

end;
