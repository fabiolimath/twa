/* 
   Formulação do Modelo para Minização dos Custos de Instalação e Operação de Redes Opticas Multicaminhos.
   
   Modelagem e Descrição em MathProg por Fábio Lima (fabiolimath@gmail.com).

*/


#############################################################
########################### PARÂMETROS ######################
#############################################################

################## Identificação da Instância ###############

# 1 - Numero de nós da Rede.
param N 'Numero de nós' default 4, integer, > 0;

# 2 - Grau Físico de Saida e Entrada dos nós.
param H default 2, integer, > 0;

# 3 - Número de Comprimentos de Onda disponíveis em cada Ligação Física.
param Wc default 2, integer, >0;

# 4 - Grau Lógico.
param Gl default 0;

# 5 - Conjuntos de Indices.
set I := 1..N;
set W := 1..Wc;

# 6 - Número máximo de cores em cada ligação física.
param L default 0, integer, >=0;

# 7 - Número máximo de saltos físicos
param MB default 0, integer, >=0;

###################### Outros Parâmetros ####################

# 1 - Matriz de Trafego.
param D 'Matriz de Trafego' {i in I, j in I} default 2;

# 2 - Topologia Completa da Rede - Versão Parâmetro.
param B {s in I, i in I, j in I, w in W: s!=j and i!=j} default 1, binary;

# 3 - Ligações Físicas Direcionadas - Versão Parâmetro.
param Hd {i in I, j in I} default 1, binary;

# 4 - Multiplicidade Física.
param M default 1, integer, >= 1, <= H;

########################## Constantes #######################

# 1 - Custo por do Tráfego para a Capacidade.
param T default 1;

# 2 - Custo para cada Ligação Física Direcionada.
param C {i in I, j in I} default 0;

# 3 - Capacidade de cada Ligação Direcionada por Comprimento de Onda.

param maxin  default if (Gl != 0) 
then (max{k in I} sum{i in I, j in I: i!=j and i!=k} D[i,j]/Gl)
else (max{k in I} sum{i in I, j in I: i!=j and i!=k} D[i,j]/(H*Wc));

param maxout default if (Gl != 0) 
then (max{k in I} sum{i in I, j in I: i!=j and j!=k} D[i,j]/Gl)
else (max{k in I} sum{i in I, j in I: i!=j and j!=k} D[i,j]/(H*Wc));

param Cap default max(maxin,maxout);

#param Cap default if (Gl != 0) then ((N/((N - 1)*Gl))*sum{i in I, j in I: i!=j} D[i,j])
#			       else ((N/((N - 1)*H*Wc))*sum{i in I, j in I: i!=j} D[i,j]);

param LbT default sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T, >= 0;
param UbT default if (Gl != 0) then (((N - 1)/Gl)*sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T)
			       else (((N - 1)/H*Wc)*sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T);

param TrafMin default sum{i in I, j in I: i!=j} D[i,j];

######################## Controle ###########################

# 1 - Boolean: Topologia Física Direcionada da Rede é Passada como Parâmetro?
param Fis default 1, binary;

# 2 - Boolean: Minimizar o Custo?
param MiniC default 1, binary;

# 3 - Boolean: Limitar Capacidade?
param LimCap default 1, binary;

# 4 - Boolean: Usar Multicaminhos?
param Multi default 1, binary; 

# 5 - Boolean: Minimizar Número de Saltos Físicos?
param MinB default 0, binary;

#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Componente da ligação Lógica Iniciada em "s", na cor "w", Passando em (i,j).
var b 'b' {s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0}, integer, <= M, >=0;

# 2 - Topologia Física.
var h 'h' {i in I, j in I: i!=j}, integer, <= M, >=0;

# 3 - Fração das Demandas de "m".
var q 'q' {s in I, d in I, m in I: d!=m and s!=d}, >= 0, <=1;

# 4 - Ligações Lógicas.
var F 'F' {s in I, r in 1..H*Wc, d in I: s!=d}, binary;

# 5 - Fração do Tráfego na Ligação Lógica (s,r,w).
var f 'f' {s in I, r in 1..H*Wc, d in I: s!=d}, >= 0, <=1;


#############################################################
########################### RESTRIÇÕES ######################
#############################################################

######################## Projeto da Rede ####################

/*
Obs. 1: Estas restrições não são necessárias se a topologia daalisha keys rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

# 1 - Definição da Topologia Física ou, caso esta seja fixada, Limitação da Topologia Lógica pela Física.
s.t.  UniLog {i in I, j in I, w in W: i!=j and Hd[i,j]!=0}: sum{s in I: s!=j} b[s,i,j,w] <= if (Fis==1) then Hd[i,j] else h[i,j];

# 2 - Conservação do Percurso Lógico.
s.t.  ConservLog {s in I, i in I, w in W: s!=i}: 
sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: i!=j and j!=s and Hd[i,j]!=0} b[s,i,j,w] >= 0;

/*
Obs. 2: A não repetição de um nó no percurso de uma ligação lógica é evitada implicitamente pela minimização dos custos de instalação e operação.
*/

/*
Obs. 3: A restrição a seguir é usada para não permitir multiplos caminhos lógicos entre um mesmo par de nós.
Por default a restrição abaixo é desabilitada.
*/

# 3 - Limitaçao de Apenas Uma Ligação lógica Entre Cada Par ordenado (s,d).
s.t.  MultControl {s in I, i in I: i!=s and Multi=0}: sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - 
sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= 1;

# 4 - Definição das Ligações Lógicas (s,r,d).
s.t.  DefLog {s in I, i in I: i!=s and MiniC==0}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] = sum{r in 1..H*Wc} F[s,r,i];

# 5 - Definição da Fração do Tráfego na Ligação Lógica (s,r,d).
s.t.  DefTraf {s in I, r in 1..H*Wc, d in I: s!=d and MiniC==0}: F[s,r,d] >= f[s,r,d]; 

# 6 - Conservação do Grau Lógico de Saída.
s.t. LogDegreeOut {s in I: Gl!=0}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] <= Gl;  

# 7 - Conservação do Grau Lógico de Entrada.
s.t. LogDegreeIn {i in I: Gl!=0}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} b[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} b[s,i,j,w] <= Gl;  



######################## Topologia Física ###################

/*
Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

/*
Obs. 2: A topologia física é determinada pelas restrições acima. 
A variável h[i,j] apenas foi introduzida para fins de contabilização do custo de instalação
de cada ligação física.
*/

/*
Obs. 3: Se o custo de instalação física não estiver sendo minimizado,
pode ser necessário esta restrição abaixo, para garantir que não fique 
mapeada nenhuma ligação física não utilizada. Se o custo de instalação 
física for minimizado,então essas variáveis devem der implicitamente eliminadas.
Por default a restrição abaixo é desabilitada.


# 2 - Anula as Ligações Físicas Não Utilizadas.
s.t. NullFis {i in I, j in I: i!=j and MinCustoFis=0}: 
sum{s in I, w in W: s!=j} b[s,i,j,w] >= h[i,j];
*/

################# Controle de Grau Físico ###################

/*
Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

# 1- Limitação para o Grau Físico de Saída.
s.t.  FisOut {i in I: Fis==0}: sum{j in I: i!=j} h[i,j] = H;

# 2 - Limitação para o Grau Físico de Entrada.
s.t.  FisIn {i in I: Fis==0}: sum{j in I: i!=j} h[j,i] = H;


#################### Controle de Fluxo ######################

# 1 - Conservação de Fluxo.
s.t.  ConsevFlow {i in I, m in I: i!=m}: sum{s in I: s!=i} q[s,i,m] - sum{d in I: i!=d and d!=m} q[i,d,m] = D[m,i]/(sum{n in I: m!=n} D[m,n]);

# 2 - Atendimento às Demandas de Tráfego.
s.t.  AtDem {m in I}: sum{d in I: d!=m} q[m,d,m] = 1;

# 3 - Limita a Capacidade nas Ligações Lógicas Utilizadas e anula nas não utilizadas.
s.t.  CapAndNullFlow {s in I, i in I: s!=i and LimCap==1 and MiniC==1}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] <= Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# 4 - Define a Capacidade nas Ligações Lógicas Utilizadas, para o Cálculo do Congestionamento.
s.t.  CapAndNullFlowCong {s in I, i in I: s!=i and LimCap==1 and MiniC==0}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] = Cap*sum{r in 1..H*Wc} f[s,r,i];


################### Controle da Coloração ##################

# 1 - Carga Máxima de Ligações lógicas passando em cada ligação física (L).
s.t. LimCharge {i in I, j in I: i!=j and Hd[i,j]!=0 and L!=0}: L >= sum{s in I, w in W: s!=j} b[s,i,j,w];

# 2 - Número Máximo de Saltos Físicos.
s.t. LimHolps {k in 1..1: MB!=0}: sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= MB;


#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

# 1 - Definição do Congestionamento.

var Hmax 'Hmax', >= 0;

s.t. DefCon {s in I, r in 1..H*Wc, d in I: s!=d and MiniC==0}: Hmax >= f[s,r,d]*Cap;

# 2 -  Definição do Tráfego Retrasmitido Ponderado.

var TRP 'TRP', >= LbT, <= UbT;

s.t. DefTRP {k in 1..1: MiniC==1}: TRP >= sum{i in I, j in I: i!=j and C[i,j]!=0} C[i,j]*h[i,j] + 
					 sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T +
					 sum{i in I,j in I, m in I: j!=m and i!=m and i!=j} T*q[i,j,m]*(sum{n in I: m!=n} D[m,n]);

# 3 - Número de Saltos Físicos.

var MBv 'MBv', >= 0, integer;
			
#s.t. DefMBv {k in 1..1: MinB!=0}: MBv >= sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w];

			
# 4 - FUNÇÃO OBJETIVO

var Obj 'Obj', >= 0;

s.t. DefObj : Obj = if (MinB!=0) then (sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w]) else (if (MiniC==0) then Hmax else TRP);

minimize OBJETIVO: Obj;

printf('\n');
printf('Cap: ');
printf(Cap);
printf('\n');
printf('LbT: ');
printf(LbT);
printf('\n');
printf('UbT: ');
printf(UbT);
printf('\n');
printf('\n');

























