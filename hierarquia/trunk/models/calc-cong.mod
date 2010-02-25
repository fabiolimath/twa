
#################### Parâmetros ###################

# 1 - Numero de nós da Rede.
param N 'Numero de nós' default 4, integer, > 0;

# 2 - Número de Comprimentos de Onda disponíveis em cada Ligação Física.
param Wc default 2, integer, >0;

# 3 - Conjuntos de Indices.
set I := 1..N;
set W := 1..Wc;

# 4 - Matriz de Demandas.
param D{s in I, d in I} default 0;

# 5 - Tráfego Agregado.
param A{s in I} default sum{d in I} D[s,d];

# 6 - Grau Lógico.
param gl default 1;

###################### Solução ####################

# 1 - Componente da ligação Lógica Iniciada em "i", na cor "w", Passando em (m,n).
param b 'b' {i in I, m in I, n in I, w in W} default 0;

# 2 - Fração das Demandas de "m", para a Formulação Auternativa.
param qw 'qw' {i in I, j in I, s in I, w in W} default 0;

###################### Cálculo ####################

# 1 - Ligação Lógica.
param LigLog{i in I, j in I: i!=j} := (sum{m in I, w in W} b[i,m,j,w]) - (sum{n in I, w in W} b[i,j,n,w]);

# 2 - tráfego.
param TrafMedio{i in I, j in I: i!=j and LigLog[i,j]!=0} := (sum{s in I, w in W} qw[i,j,s,w]*A[s]) / LigLog[i,j];

# 3 - Congestionamento.
param Cong := max{i in I, j in I: i!=j and LigLog[i,j]!=0} TrafMedio[i,j];

###################### Imprimir ###################

printf("\n");
display{s in I} A[s];

printf("\n");
display{i in I, j in I: i!=j and LigLog[i,j]!=0} LigLog[i,j];

printf("\n");
display{i in I, j in I: i!=j and LigLog[i,j]!=0} TrafMedio[i,j];

printf("\n");
printf("Congestionamento: ");
printf(Cong);
printf("\n");

############## MTB - Maximun Traffic Bound #############

# 1 - Saída Total.
param Out{i in I}:= sum{j in I: i!=j} D[i,j]/gl;

# 2 - Entrada Total.
param In {i in I}:= sum{j in I: i!=j} D[j,i]/gl;

# 3 - Máximo por nó.
param Ma {i in I}:= max(Out[i], In[i]);

# 4 - MTB - Maximun Traffic Bound
param MTB := max{i in I} Ma[i];

printf("\n");
printf("MTB: ");
printf(MTB);
printf("\n");


#################### Outros dados #####################
# Obs.: Sem uso, para compatibilidade com o modelo TWA

## Congestionamento
# 1 - Louwer Bound para o Congestionamento.
param HmaxLB  default 0;

# 2 - Média para o Congestionamento.
param HmaxM  default 0;

# 3 - Desvio Padrão para o Congestionamento.
param HmaxD  default 0;

# 4 - RLDA para o Congestionamento.
param HmaxRLDA  default 0;

# 5 - HLDA para o Congestionamento.
param HmaxHLDA  default 0;

# 6 - Máximo Amostral para o Congestionamento.
param HmaxMaxA  default 0;

## Processamento
# 1 - Louwer Bound para o Processamento.
param FTnetLB  default 0;

# 2 - Média para o Processamento.
param FTnetM  default 0;

# 3 - Desvio Padrão para o Processamento.
param FTnetD  default 0;

# 4 - RLDA para o Processamento.
param FTnetRLDA  default 0;

# 5 - Máximo Amostral para o Processamento.
param FTnetMaxA  default 0;

# 6 - HLDA para o Processamento.
param FTnetHLDA  default 0;

## Outros

# 1 - Matriz de Distancias.
param C{s in I, d in I} default 0;

# 1 - Matriz de Distancias.
param TIFgap default 0;

printf("\n");

end;
