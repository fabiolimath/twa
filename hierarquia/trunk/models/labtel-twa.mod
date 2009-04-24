
/* 
  Formulação do Modelo TWA - Trafic over Wavelength Assignment.
   
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
param Gle default 0;

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

# 5 - Total de Transceptores na rede.
param TT default 0, integer, >= 0;
param TTe default 0, integer, >= 0;

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

param HmaxLB default 0;

#############################################################
#############################################################
###############  Integer: Função Objtivo. ###################

# (0) = Função Zero;
# (1) = Custo;
# (2) = Congestionamento;
# (3) = Saltos Físicos;
param OBJETIVO default 1, integer;

######################## Controle ###########################

# 1 - Boolean: Topologia Física Direcionada da Rede é Passada como Parâmetro?
param Fis default 1, binary;

# 3 - Integer: Grau de Multiplicidade das Ligações Lógicas
param Multi default 0, integer; 

# 5 - Boolean: Usar formulação alternativa?
param Aut default 0, binary;

# 9 - Limita a Capacidade nas Ligações Lógicas Utilizadas e anula nas não utilizadas.
# (0) = Anular e Limitar;
# (1) = Anular Explícitamente;
param NullTraf default 0, integer, >=0, <=1;

# 7 - Boolean: Usar Plano de Corte por Fluxo?
param CPF default 0, binary;

# 8 - Plano de Corte por Demanda.
param CPD default 0;


#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Componente da ligação Lógica Iniciada em "s", na cor "w", Passando em (i,j).
var b 'b' {s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0}, integer, <= M, >=0;

# 2 - Topologia Física.
var h 'h' {i in I, j in I: i!=j}, integer, <= M, >=0;

# 3 - Fração das Demandas de "m".
var q 'q' {s in I, d in I, m in I: d!=m and s!=d}, >= 0, <=1;

# 4 - Fração das Demandas de "m", para a Formulação Auternativa.
var qw 'qw' {s in I, d in I, m in I, w in W: d!=m and s!=d and Aut==1}, >= 0, <=1;

#############################################################
########################### RESTRIÇÕES ######################
#############################################################

#############################################################
######################## Projeto da Rede ####################

/*
Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

# 1 - Definição da Topologia Física ou, caso esta seja fixada, Limitação da Topologia Lógica pela Física.
s.t.  UniLog {i in I, j in I, w in W: i!=j and Hd[i,j]!=0}: sum{s in I: s!=j} b[s,i,j,w] <= if (Fis==1) then Hd[i,j] else h[i,j];

# 2 - Conservação do Percurso Lógico.
s.t.  ConservLog {s in I, i in I, w in W: s!=i and Aut = 0}: 
sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: i!=j and j!=s and Hd[i,j]!=0} b[s,i,j,w] >= 0;

#############################################################
#################### Controle de Fluxo ######################

# 1 - Conservação de Fluxo.
s.t.  ConsevFlow {i in I, m in I: i!=m and Aut==0}: sum{s in I: s!=i} q[s,i,m] - sum{d in I: i!=d and d!=m} q[i,d,m] = D[m,i]/(sum{n in I: m!=n} D[m,n]);

# Versão Auternativa
s.t.  ConsevFlowAut {i in I, m in I: i!=m and Aut==1}: 
sum{s in I, w in W: s!=i} qw[s,i,m,w] - sum{d in I, w in W: i!=d and d!=m} qw[i,d,m,w] = D[m,i]/(sum{n in I: m!=n} D[m,n]);

# 2 - Atendimento às Demandas de Tráfego.
s.t.  AtDem {m in I: Aut==0}: sum{d in I: d!=m} q[m,d,m] = 1;

# Versão Auternativa
s.t.  AtDemAut {m in I: Aut==1}: sum{d in I, w in W: d!=m} qw[m,d,m,w] = 1;

########################################################################################
## Limitação de Capacidade e Anulamento do Tráfego em Ligações Lógicas não Utilizadas ##

# 1 - Limitação do número de Ligações Lógicas.
param CLC := if (OBJETIVO!=2) then 0 else (if (Multi!=0) then Multi else H*Wc);

s.t.  CapAndNullFlow {s in I, i in I: s!=i and CLC<2 and Aut==0 and NullTraf==0}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] <= 
Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# Versão com Anulamento Explícito.
s.t.  NullFlowExpl {s in I, i in I, m in I: s!=i and m!=i and CLC<2 and Aut==0 and NullTraf==1}: 
q[s,i,m] <= (sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# 2 - Formulação Auternativa

s.t.  CapAndNullFlowAut {s in I, i in I, w in W: s!=i and CLC<2 and Aut==1 and NullTraf==0}: 
sum{m in I, n in I: m!=n and i!=m} qw[s,i,m,w]*D[m,n] <= 
Cap*(sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# Versão com Anulamento Explícito.
s.t.  NullFlowAutExpl {s in I, i in I, w in W, m in I: s!=i and i!=m and CLC<2 and Aut==1 and NullTraf==1}: 
qw[s,i,m,w] <= (sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);


#############################################################
############ Formulação para o Congestionamento #############

# Controle Interno:
param CapLog{i in I} := if (Fis==0) then min(CLC,H*Wc) else (min( CLC, sum{j in I: i!=j} D[i,j]*Wc ));
param CL{i in I, j in I} := min( CapLog[i], CapLog[j]);

# 2 - Ligações Lógicas (s,d,r).
var F 'F' {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}, binary;

# 3 - Fração do Tráfego na Ligação Lógica (s,d,r).
var f 'f' {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}, >= 0, <=1;

# 4 - Definição das Ligações Lógicas (s,d,r).
s.t.  DefLog {s in I, i in I: i!=s and CLC>1}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] = sum{r in 1..CL[s,i]} F[s,i,r];

# 5 - Definição da Fração do Tráfego na Ligação Lógica (s,d,r).
s.t.  DefTraf {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}: F[s,d,r] >= f[s,d,r]; 

# 6 - Limita a Capacidade nas Ligações Lógicas Utilizadas e anula nas não utilizadas.
s.t.  CapAndNullFlowCong {s in I, i in I: s!=i and CLC>1}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] = Cap*sum{r in 1..CL[s,i]} f[s,i,r];

# 7 - Definição do Congestionamento.
var Hmax 'Hmax', >= HmaxLB, <= Cap;

s.t. DefCon {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>0} : 
Hmax >= if (CLC>1) then 
	f[s,d,r]*Cap 
	else 
	( if (Aut==0) then 
	    sum{m in I, n in I: m!=n and d!=m} q[s,d,m]*D[m,n]
	    else
	    sum{m in I, n in I, w in W:m!=n and d!=m} qw[s,d,m,w]*D[m,n]
	);

#############################################################
###### Limitaçao da Multiplicidade de Ligações lógicas.######

param Ml := if (CLC==1) then 1 else Multi;

s.t.  MultControl {s in I, i in I: i!=s and Ml!=0 and CLC<2}: sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - 
sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= Ml;

#############################################################
################## Número de Transceptores ##################

# 1 - Conservação do Grau Lógico de Saída.
s.t. LogDegreeOut {s in I: Gl!=0}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] <= Gl;  

# Versão com Igualdade:
s.t. LogDegreeOutEq {s in I: Gle!=0}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] = Gle;  

# 2 - Conservação do Grau Lógico de Entrada.
s.t. LogDegreeIn {i in I: Gl!=0}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} b[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} b[s,i,j,w] <= Gl;  

# Versão com Igualdade:
s.t. LogDegreeInEq {i in I: Gle!=0}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} b[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} b[s,i,j,w] = Gle;  

# 3 - Total de Transceptores na rede.
s.t. TotalTranscep {k in 1..1: TT>0}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] <= TT;  

# Versão com Igualdade:
s.t. TotalTranscepEq {k in 1..1: TTe>0}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] = TTe;  

/*
######################## Topologia Física ###################


Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.



Obs. 2: A topologia física é determinada pelas restrições acima. 
A variável h[i,j] apenas foi introduzida para fins de contabilização do custo de instalação
de cada ligação física.



Obs. 3: Se o custo de instalação física não estiver sendo minimizado,
pode ser necessário esta restrição abaixo, para garantir que não fique 
mapeada nenhuma ligação física não utilizada. Se o custo de instalação 
física for minimizado,então essas variáveis devem der implicitamente eliminadas.
Por default a restrição abaixo é desabilitada.


# 2 - Anula as Ligações Físicas Não Utilizadas.
s.t. NullFis {i in I, j in I: i!=j and MinCustoFis=0}: 
sum{s in I, w in W: s!=j} b[s,i,j,w] >= h[i,j];
*/

#############################################################
################# Controle de Grau Físico ###################

/*
Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

# 1- Limitação para o Grau Físico de Saída.
s.t.  FisOut {i in I: Fis==0}: sum{j in I: i!=j} h[i,j] = H;

# 2 - Limitação para o Grau Físico de Entrada.
s.t.  FisIn {i in I: Fis==0}: sum{j in I: i!=j} h[j,i] = H;


#############################################################
##################### Planos de Corte ########################

# 1 - Plano de corte por Fluxo.
s.t.  CotingPlaneFlow {s in I, i in I: s!=i and Aut==0 and CPF==1}: 
1 + (sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# Versão Auternativa
s.t.  CotingPlaneFlowAut {s in I, i in I: s!=i and Aut==1 and CPF==1}: 
1 + (sum{m in I, n in I, w in W: m!=n and i!=m} qw[s,i,m,w]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

# Saída:
s.t. CotingPlaneDemOut {s in I: CPD==1} :
sum{j in I: j!=s} D[s,j] <= 
sum{i in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]));

# Entrada:
s.t. CotingPlaneDemIn {i in I: CPD==1} :
sum{j in I: j!=i} D[j,i] <= 
sum{s in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]));

#############################################################
################### Controle da Coloração ###################

# 1 - Carga Máxima de Ligações lógicas passando em cada ligação física (L).
s.t. LimCharge {i in I, j in I: i!=j and Hd[i,j]!=0 and L!=0} : 
L >= sum{s in I, w in W: s!=j} b[s,i,j,w];

# 2 - Número Máximo de Saltos Físicos.
s.t. LimHolps {k in 1..1: MB!=0} : 
sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= MB;


#############################################################
#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

# 1 -  Definição do Tráfego Retrasmitido Ponderado.

var TRP 'TRP', >= LbT, <= UbT;

s.t. DefTRP {k in 1..1: OBJETIVO==1}: TRP >= sum{i in I, j in I: i!=j and C[i,j]!=0} C[i,j]*h[i,j] + 
					 sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T +
					 sum{i in I,j in I, m in I: j!=m and i!=m and i!=j} T*q[i,j,m]*(sum{n in I: m!=n} D[m,n]);

# 2 - Número de Saltos Físicos.

param BUP 'BUP' , default if (MB!=0) then MB else 10000;
var MBv 'MBv', >= 0, integer, <= BUP;
			
#s.t. DefMBv {k in 1..1: MinB!=0}: MBv >= sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w];

# 3 - Zero.

var Zero 'Zero', >= 0;

s.t. ZeroDef{k in 1..1: OBJETIVO==0} : Zero = 0;
			
# 4 - FUNÇÃO OBJETIVO

var Obj 'Obj', >= 0;

s.t. DefObj : Obj = if (OBJETIVO==0) then
			Zero
		      else
		        (if (OBJETIVO==3) then 
			    (sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w]) 
			    else 
			      (if (OBJETIVO==2) then 
				Hmax 
			      else 
				TRP));

minimize OBJTV: Obj;

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

























