
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

# 1 - Matriz de Trafego.
param D 'Matriz de Trafego' {i in I, j in I} default 2;

# 2 - Ligações Físicas Direcionadas - Versão Parâmetro.
param Hd {i in I, j in I} default 1, binary;

# 3 - Multiplicidade Física.
param M default 1, integer, >= 1;

# 4 - Total de Transceptores na rede.
param gl default 0; /*Para compatibilidade com o Labtel-VTD*/
param TT default gl*N, integer, >= 0;
param TTe default 0, integer, >= 0;

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
param Fis default 0, binary;

# 3 - Integer: Grau de Multiplicidade das Ligações Lógicas
param Multi default 0, integer; 

# 5 - Boolean: Usar formulação alternativa?
param Aut default 1, binary;

# 6 - Boolean: Usar Plano de Corte por Fluxo?
param CPF default 1, binary;

# 7 - Plano de Corte por Demanda.
param CPD default 1;

# 8 - Boolean: Relaxamento?
param relax default 0;

########################## Constantes #######################

# 1 - Custo por do Tráfego para a Capacidade.
param T default 1;

# 2 - Distancia de cada Ligação Física (em centenas de milhas).
param C {i in I, j in I} default 0;

# Custo de instalaçao da primeira fibra, por centena de milha
param Cipf default 1;

# Fator de ponderaçao da instalaçao da primeira fibra
param FpCipf default 1;

# Custo ponderado de cada Ligação Física
param Cp {i in I, j in I} := C[i,j]*Cipf*FpCipf;

# Custo de instalaçao de cada cabo, depois da 1a fibra, por centena de milha.
param Cif default 1;

# Fator de ponderaçao
param FpCif default 0;

# Custo ponderado de cada Ligação Física
param Cf {i in I, j in I} := C[i,j]*Cif*FpCif;

# Custo fisico total
param CiT default if (Fis==1) then (sum{i in I, j in I: i!=j and i<j} Hd[i,j]*C[i,j]*Cipf*FpCipf) else (sum{i in I, j in I: i!=j and i<j} 1*C[i,j]*Cipf*FpCipf);

# Fator de ponderaçao para os tranceptores.
param FpTrcp default 0;

# Fator de ponderaçao para o Hop fisico.
param FpH default 0;

# Custo do hop fisico.
param Ch{i in I, j in I: i!=j} := C[i,j]*FpH;

# Custo Maximo dos tranceptores
param CTrcptT := if (TT!=0) then TT*FpTrcp else (if (TTe!=0) then TTe*FpTrcp else 0);

# 3 - Limitação do número de Ligações Lógicas.
param CLC := if (OBJETIVO!=2) then 0 else (if (Multi!=0) then Multi else H*Wc);

param Glg := if (Gl!=0) then Gl else (if (Gle!=0) then Gle else (if (TT!=0) then TT/N else (if (TTe!=0) then TTe/N else 0)));
param Trin  {i in I} := if (Fis==1) then sum{j in I: i!=j} Hd[j,i]*Wc else (if (H!=0) then H*Wc else (N-1)*Wc);
param Trout {i in I} := if (Fis==1) then sum{j in I: i!=j} Hd[i,j]*Wc else (if (H!=0) then H*Wc else (N-1)*Wc);
param Tri   {i in I} := if (Glg!=0) then min(Glg, Trin[i]) ;
param Tro   {i in I} := if (Glg!=0) then min(Glg, Trout[i]) ;

# Controle Interno:
param CapLogIn {i in I} := if (Fis==0) then min(Tri[i],H*Wc) else (min( Tri[i], sum{j in I: i!=j} Hd[j,i]*Wc ));
param CapLogOut{i in I} := if (Fis==0) then min(Tro[i],H*Wc) else (min( Tro[i], sum{j in I: i!=j} Hd[i,j]*Wc ));
param CL{i in I, j in I} := min( CLC, CapLogOut[i], CapLogIn[j]);

# 4 - Capacidade de cada Ligação Direcionada por Comprimento de Onda.

# Fração do Tráfego Máximo aceito, por padrão.
param Frac default 0.5, >=0, <=1;

# Tráfego Máximo de Entrada
param maxin  := max{k in I} sum{i in I, j in I: i!=j and i!=k} D[i,j]/Tri[k];

# Tráfego Máximo de Saída
param maxout := max{k in I} sum{i in I, j in I: i!=j and j!=k} D[i,j]/Tro[k];

# 5 - LB e UB para o custo de operação, por padrão.
param TrafMin := sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j];
param LbT default TrafMin*T, >= 0;
param UbT default if (Glg != 0) then (((N - 1)/Glg)*sum{i in I, j in I: i!=j and D[i,j]!=0} D[i,j]*T) else 0;

# 6 - MTB - Maximun Traffic Bound

param Out{i in I}:= sum{j in I: i!=j} D[i,j]/Tro[i];
param In {i in I}:= sum{j in I: i!=j} D[j,i]/Tri[i];
param Ma {i in I}:= max(Out[i], In[i]);

param MTB := max{i in I} Ma[i];

# 7 - LB para o trafego.

param FTnetLB default 0;
param FTnetM default 0;
param FTnetMaxA default 0;
param FTnetHLDA default 0;
param FTnetRLDA default 0;
param FTnetD default 0;

param dumpT := (FTnetM - FTnetRLDA)/FTnetD;
param dump2T := (round(dumpT) - trunc(dumpT))/2;
param dump3T := trunc(dumpT) + dump2T;
param FTnetDs := if (dump3T > 3) then 3 else dump3T;
param FTnetUB_percent := 1 + (FTnetM - FTnetDs*FTnetD);
#param FTnetUB_percent := 1 + (FTnetM - (FTnetDs - 0.5)*FTnetD);

param MT default (FTnetUB_percent)*FTnetLB;

param TLB default 0;

param TTLB default TLB + sum{i in I, j in I: i!=j} D[i,j];

# 8 - LB para o congestinamento.

param EspT := sum{i in I} (MTB - Ma[i])*Glg;

param HmaxLB default if (TLB>EspT) then (MTB + ((TLB - EspT)/N)) else MTB;

# Capacidade padrão.
param HmaxM default 0;
param HmaxD default 0;
param HmaxRLDA default 0;
param HmaxHLDA default 0;
param HmaxMaxA default 0;

param dumpH := (HmaxM - HmaxRLDA)/HmaxD;
param dump2H := (round(dumpH) - trunc(dumpH))/2;
param dump3H := trunc(dumpH) + dump2H;
param HmaxDs := if (dump3H > 3) then 3 else dump3H;
param HmaxUB_percent := 1 + (HmaxM - HmaxDs*HmaxD);
#param HmaxUB_percent := 1 + (HmaxM - (HmaxDs - 0.5)*HmaxD);

#param Cap default if (OBJETIVO==1 and HmaxM>0) then HmaxLB*(1 + HmaxM + HmaxD) else Frac*max(maxin,maxout);
param Cap default if (OBJETIVO==1 and HmaxM>0) then HmaxLB*(HmaxUB_percent) else Frac*max(maxin,maxout);

printf('\n');

printf "HmaxDs = %f\n", HmaxDs;
printf "HmaxUB_percent = %f\n", HmaxUB_percent;
printf "HmaxUB_real = %f\n", Cap;
printf "FTnetDs = %f\n", FTnetDs;
printf "FTnetUB_percent = %f\n", FTnetUB_percent;
printf "FTnetUB_real = %f\n", MT;

#printf "N = %f\n", N;
#printf "W = %f\n", Wc;
#printf "Glg = %f\n", Glg;
#printf "MTB = %f\n", MTB;

/*

#param LimUT  := sum{i in I} (Cap - Ma[i])*Glg;
#param LimUTT := sum{i in I} (Cap - Ma[i])*Glg + sum{i in I, j in I: i!=j} D[i,j];

#display: Glg;
#display: kt;
#printf "TLB = %f\n", TLB[Glg];
#printf "TTLB = %f\n", TTLB;
#printf "LimUTT = %f\n", LimUTT;
#display: EspT;
#display: MTB;


printf "HmaxLB = %f\n", HmaxLB;

#display{i in 1..N}: RT[i];

#display{l in 1..kt}: alf[l]+1;
#display{l in 1..kt}: alf[l+1];
#display{l in 1..kt}: li[l];
#display{l in 1..kt}: ls[l];

*/

#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Componente da ligação Lógica Iniciada em "s", na cor "w", Passando em (i,j).
var b 'b' {s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0}, integer, <= M, >=0;

var br 'br' {s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0}, <= M, >=0;

# 2 - Topologia Física.
var h 'h' {i in I, j in I: i!=j and i<j}, integer, <= M, >=0;

var hr 'hr' {i in I, j in I: i!=j}, <= M, >=0;

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
s.t.  UniLog {i in I, j in I, w in W: i!=j and Hd[i,j]!=0 and relax==0}: 
sum{s in I: s!=j} b[s,i,j,w] <= 
  if (Fis==1) then 
	 Hd[i,j] 
	 else
		(if (i<j) then h[i,j] else h[j,i]);

	 s.t.  UniLogR {i in I, j in I, w in W: i!=j and Hd[i,j]!=0 and relax==1}: sum{s in I: s!=j} br[s,i,j,w] <= if (Fis==1) then Hd[i,j] else hr[i,j];

#var hp{i in I, j in I}, binary;
#s.t. DefHp {i in I, j in I: i!=j and relax==0 and M>1}: h[i,j] <= hp[i,j]*M;

# 2 - Conservação do Percurso Lógico.
s.t.  ConservLog {s in I, i in I, w in W: s!=i and Aut = 0 and relax==0}: 
sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: i!=j and j!=s and Hd[i,j]!=0} b[s,i,j,w] >= 0;

s.t.  ConservLogR {s in I, i in I, w in W: s!=i and Aut = 0 and relax==1}: 
sum{j in I: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I: i!=j and j!=s and Hd[i,j]!=0} br[s,i,j,w] >= 0;

#############################################################
#################### Controle de Fluxo ######################

# 1 - Conservação de Fluxo.
s.t.  ConservFlow {i in I, m in I: i!=m and Aut==0}: sum{s in I: s!=i} q[s,i,m] - sum{d in I: i!=d and d!=m} q[i,d,m] = D[m,i]/(sum{n in I: m!=n} D[m,n]);

# Versão Auternativa
s.t.  ConsevFlowAut {i in I, m in I: i!=m and Aut==1}: 
sum{s in I, w in W: s!=i} qw[s,i,m,w] - sum{d in I, w in W: i!=d and d!=m} qw[i,d,m,w] = D[m,i]/(sum{n in I: m!=n} D[m,n]);
#if ( (sum{n in I: m!=n} D[m,n])!= 0 ) then (D[m,i]/(sum{n in I: m!=n} D[m,n])) else 0;

# 2 - Atendimento às Demandas de Tráfego.
s.t.  AtDem {m in I: Aut==0}: sum{d in I: d!=m} q[m,d,m] = 1;

# Versão Auternativa
s.t.  AtDemAut {m in I: Aut==1}: sum{d in I, w in W: d!=m} qw[m,d,m,w] = 1;

########################################################################################
## Limitação de Capacidade e Anulamento do Tráfego em Ligações Lógicas não Utilizadas ##

s.t.  CapAndNullFlow {s in I, i in I: s!=i and CLC<2 and Aut==0 and relax==0}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] <= 
Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

s.t.  CapAndNullFlowR {s in I, i in I: s!=i and CLC<2 and Aut==0 and relax==1}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] <= 
Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]);

# 2 - Formulação Auternativa

s.t.  CapAndNullFlowAut {s in I, i in I, w in W: s!=i and CLC<2 and Aut==1 and relax==0}: 
sum{m in I, n in I: m!=n and i!=m} qw[s,i,m,w]*D[m,n] <= 
Cap*(sum{j in I: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

s.t.  CapAndNullFlowAutR {s in I, i in I, w in W: s!=i and CLC<2 and Aut==1 and relax==1}: 
sum{m in I, n in I: m!=n and i!=m} qw[s,i,m,w]*D[m,n] <= 
Cap*(sum{j in I: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]);


#############################################################
############ Formulação para o Congestionamento #############

# 2 - Ligações Lógicas (s,d,r).
var F 'F' {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}, binary;
var Fr 'F' {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}, >=0, <=1;

# 3 - Fração do Tráfego na Ligação Lógica (s,d,r).
var f 'f' {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1}, >= 0, <=1;

# 4 - Definição das Ligações Lógicas (s,d,r).
s.t.  DefLog {s in I, i in I: i!=s and CLC>1 and relax==0}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] = sum{r in 1..CL[s,i]} F[s,i,r];

s.t.  DefLogR {s in I, i in I: i!=s and CLC>1 and relax==1}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} br[s,i,j,w] = sum{r in 1..CL[s,i]} Fr[s,i,r];

# 5 - Definição da Fração do Tráfego na Ligação Lógica (s,d,r).
s.t.  DefTraf {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1 and relax==0}: F[s,d,r] >= f[s,d,r]; 

s.t.  DefTrafR {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>1 and relax==1}: Fr[s,d,r] >= f[s,d,r]; 

# 6 - Limita a Capacidade nas Ligações Lógicas Utilizadas e anula nas não utilizadas.
s.t.  CapAndNullFlowCong {s in I, i in I: s!=i and CLC>1}: 
sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n] = Cap*sum{r in 1..CL[s,i]} f[s,i,r];

# 7 - Definição do Congestionamento.
var Hmax 'Hmax', >= HmaxLB, <= Cap;

s.t. DefCon {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>0 and relax==0} : 
Hmax >= if (CLC>1) then 
f[s,d,r]*Cap
else 
  ( if (Aut==0) then 
  sum{m in I, n in I: m!=n and d!=m} q[s,d,m]*D[m,n]
  else
    sum{m in I, n in I, w in W:m!=n and d!=m} qw[s,d,m,w]*D[m,n]
    );
  
s.t. DefConR {s in I, d in I, r in 1..CL[s,d]: s!=d and CLC>0 and relax==1} : 
Hmax >= if (CLC>1) then 
	f[s,d,r]*Cap + HmaxLB*(1 - Fr[s,d,r])
	else 
	( if (Aut==0) then 
	HmaxLB*(1 - (sum{j in I, w in W: d!=j and Hd[j,d]!=0} br[s,j,d,w] - sum{j in I, w in W: j!=d and s!=j and Hd[d,j]!=0} br[s,d,j,w])) 
	+ sum{m in I, n in I: m!=n and d!=m} q[s,d,m]*D[m,n]
	    else
	    HmaxLB*(1 - (sum{j in I, w in W: d!=j and Hd[j,d]!=0} br[s,j,d,w] - sum{j in I, w in W: j!=d and s!=j and Hd[d,j]!=0} br[s,d,j,w])) 
	    + sum{m in I, n in I, w in W:m!=n and d!=m} qw[s,d,m,w]*D[m,n]
	);

#############################################################
###### Limitaçao da Multiplicidade de Ligações lógicas.######

param Ml := if (CLC==1) then 1 else Multi;

s.t.  MultControl {s in I, i in I: i!=s and Ml!=0 and CLC<2 and relax==0}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0 and relax==0} b[s,j,i,w] - 
sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= Ml;

s.t.  MultControlR {s in I, i in I: i!=s and Ml!=0 and CLC<2 and relax==1}: 
sum{j in I, w in W: i!=j and Hd[j,i]!=0 and relax==0} br[s,j,i,w] - 
sum{j in I, w in W: j!=s and i!=j and Hd[i,j]!=0} br[s,i,j,w] <= Ml;

#############################################################
################## Número de Transceptores ##################

# 1 - Conservação do Grau Lógico de Saída.
s.t. LogDegreeOut {s in I: Gl!=0 and relax==0}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] <= Gl;  

s.t. LogDegreeOutR {s in I: Gl!=0 and relax==1}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} br[s,s,j,w] <= Gl;  

# Versão com Igualdade:
s.t. LogDegreeOutEq {s in I: Gle!=0 and relax==0}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] = Gle;  

s.t. LogDegreeOutEqR {s in I: Gle!=0 and relax==1}: sum{w in W, j in I: s!=j and Hd[s,j]!=0} br[s,s,j,w] = Gle;  

# 2 - Conservação do Grau Lógico de Entrada.
s.t. LogDegreeIn {i in I: Gl!=0 and relax==0}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} b[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} b[s,i,j,w] <= Gl;  

s.t. LogDegreeInR {i in I: Gl!=0 and relax==1}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} br[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} br[s,i,j,w] <= Gl;  

# Versão com Igualdade:
s.t. LogDegreeInEq {i in I: Gle!=0 and relax==0}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} b[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} b[s,i,j,w] = Gle;  

s.t. LogDegreeInEqR {i in I: Gle!=0 and relax==1}: 
sum{s in I, j in I, w in W: i!=j and Hd[j,i]!=0 and s!=i} br[s,j,i,w] - 
sum{s in I, j in I, w in W: i!=j and Hd[i,j]!=0 and s!=i and s!=j} br[s,i,j,w] = Gle;  

# 3 - Total de Transceptores na rede.
s.t. TotalTranscep {k in 1..1: TT>0 and relax==0}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] <= TT;  

s.t. TotalTranscepR {k in 1..1: TT>0 and relax==1}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} br[s,s,j,w] <= TT;  

# Versão com Igualdade:
s.t. TotalTranscepEq {k in 1..1: TTe>0 and relax==0}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w] = TTe;  

s.t. TotalTranscepEqR {k in 1..1: TTe>0 and relax==1}: sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} br[s,s,j,w] = TTe;  

#############################################################
################# Controle de Grau Físico ###################

/*
Obs. 1: Estas restrições não são necessárias se a topologia da rede for um parâmetro,
ou seja, quando o modelo é um LP e não um MILP.
*/

# 1- Limitação para o Grau Físico de Saída.
s.t.  FisOut {i in I: Fis==0 and H!=0}: H = sum{j in I: i!=j and relax==0} (if (i<j) then h[i,j] else h[j,i]);

s.t.  FisOutR {i in I: Fis==0 and H!=0}: sum{j in I: i!=j and relax==1} hr[i,j] = H;

# 2 - Limitação para o Grau Físico de Entrada.
s.t.  FisIn {i in I: Fis==0 and H!=0}: H = sum{j in I: i!=j and relax==0} (if (i<j) then h[i,j] else h[j,i]);

s.t.  FisInR {i in I: Fis==0 and H!=0}: sum{j in I: i!=j and relax==1} hr[j,i] = H;


#############################################################
##################### Planos de Corte ########################

# 1 - Plano de corte por Fluxo.
s.t.  CotingPlaneFlow {s in I, i in I: s!=i and Aut==0 and CPF==1 and relax==0}: 
1 + (sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

s.t.  CotingPlaneFlowR {s in I, i in I: s!=i and Aut==0 and CPF==1 and relax==1}: 
1 + (sum{m in I, n in I: m!=n and i!=m} q[s,i,m]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]);

# Versão Auternativa
s.t.  CotingPlaneFlowAut {s in I, i in I: s!=i and Aut==1 and CPF==1 and relax==0}: 
1 + (sum{m in I, n in I, w in W: m!=n and i!=m} qw[s,i,m,w]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]);

s.t.  CotingPlaneFlowAutR {s in I, i in I: s!=i and Aut==1 and CPF==1 and relax==1}: 
1 + (sum{m in I, n in I, w in W: m!=n and i!=m} qw[s,i,m,w]*D[m,n])/Cap >= 
(sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]);

# Saída:
s.t. CotingPlaneDemOut {s in I: CPD==1 and relax==0} :
sum{j in I: j!=s} D[s,j] <= 
sum{i in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]));

s.t. CotingPlaneDemOutR {s in I: CPD==1 and relax==1} :
sum{j in I: j!=s} D[s,j] <= 
sum{i in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]));

# Entrada:
s.t. CotingPlaneDemIn {i in I: CPD==1 and relax==0} :
sum{j in I: j!=i} D[j,i] <= 
sum{s in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} b[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} b[s,i,j,w]));

s.t. CotingPlaneDemInR {i in I: CPD==1 and relax==1} :
sum{j in I: j!=i} D[j,i] <= 
sum{s in I: s!=i} (Cap*(sum{j in I, w in W: i!=j and Hd[j,i]!=0} br[s,j,i,w] - sum{j in I, w in W: j!=i and s!=j and Hd[i,j]!=0} br[s,i,j,w]));

#############################################################
################### Controle da Coloração ###################

# 1 - Carga Máxima de Ligações lógicas passando em cada ligação física (L).
s.t. LimCharge {i in I, j in I: i!=j and Hd[i,j]!=0 and L!=0 and relax==0} : 
L >= sum{s in I, w in W: s!=j} b[s,i,j,w];

s.t. LimChargeR {i in I, j in I: i!=j and Hd[i,j]!=0 and L!=0 and relax==1} : 
L >= sum{s in I, w in W: s!=j} br[s,i,j,w];

# 2 - Número Máximo de Saltos Físicos.
s.t. LimHolps {k in 1..1: MB!=0 and relax==0 and OBJETIVO!=1} : 
sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w] <= MB;

s.t. LimHolpsR {k in 1..1: MB!=0 and relax==1 and OBJETIVO!=1} : 
sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} br[s,i,j,w] <= MB;


#############################################################
#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

# 1 -  Custos.

param BUP default if (MB!=0) then MB else 10000;
param TUP default if (MT!=0) then MT else sum{i in I, j in I: i!=j} (N-2)*D[i,j];
param MBL default 0;
param FpBL default 0;
param BLUP default if (MBL!=0) then MBL else 1000000;

var CIPF, >= 0, <= CiT;
var CustoTrafRetr, >= 0, <= TUP;
var TotalTrancpt, >= 0, <= TT;
var CustoHop, >=0, <= BUP;
var BL, >= 0 , <= BLUP;
var CustoTotal;

s.t. DefCIPF    {k in 1..1: FpCipf!=0}: CIPF = sum{i in I, j in I: i!=j and Cp[i,j]!=0 and i<j} (Cp[i,j]*h[i,j]);

param TIF default 1.82;
param TIFgap default 0.5;
printf "TIFgap = %f\n", TIFgap;

param LimCIPF default TIF*(1 - TIFgap)*(sum{i in I, j in I: i!=j and Cp[i,j]!=0 and i<j} Cp[i,j])/(N - 1);

printf('LimCIPF = ');
printf(LimCIPF);
printf('\n');


s.t. DefLimCIPF    {k in 1..1: TIF!=0}: CIPF <= LimCIPF;

s.t. DefCTR     {k in 1..1: T!=0 and Aut==0}: CustoTrafRetr = sum{i in I,j in I, m in I: j!=m and i!=m and i!=j} T*q[i,j,m]*(sum{n in I: m!=n} D[m,n]);
s.t. DefCTRaut  {k in 1..1: T!=0 and Aut==1}: CustoTrafRetr = sum{i in I,j in I, m in I, w in W: j!=m and i!=m and i!=j} T*qw[i,j,m,w]*(sum{n in I: m!=n} D[m,n]);

s.t. DefCTrcpt  {k in 1..1: TT!=0}: TotalTrancpt = sum{s in I, w in W, j in I: s!=j and Hd[s,j]!=0} b[s,s,j,w];

s.t. DefCHop    {k in 1..1: FpH!=0}: CustoHop = sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} Ch[i,j]*b[s,i,j,w];

s.t. DefBL      {k in 1..1: FpBL!=0}: BL = sum{i in I,j in I, m in I, w in W: j!=m and i!=j} FpBL*qw[i,j,m,w]*(sum{n in I: m!=n} D[m,n])*Cp[i,j];

param bitCI  default 1;
param bitCT  default 1;
param bitCTr default 0;
param bitCH  default 0;
param bitBL  default 0;

s.t. DefCustoT  {k in 1..1: OBJETIVO==1} : 
CustoTotal = CIPF*bitCI + CustoTrafRetr*bitCT + FpTrcp*TotalTrancpt*bitCTr + CustoHop*bitCH + bitBL*BL;

# 2 - Número de Saltos Físicos.

var MBv 'MBv', >= 0, integer, <= BUP;
			
#s.t. DefMBv {k in 1..1: MinB!=0}: MBv >= sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w];

# 3 - Zero.

var Zero 'Zero', >= 0;

s.t. ZeroDef{k in 1..1: OBJETIVO==0} : Zero = 0;
			
# 4 - FUNÇÃO OBJETIVO

var Obj 'Obj', >= 0;

s.t. DefObj{k in 1..1: relax==0} : Obj = if (OBJETIVO==0) then
			Zero
		      else
		        (if (OBJETIVO==3) then 
			    (sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} b[s,i,j,w]) 
			    else 
			      (if (OBJETIVO==2) then 
				Hmax 
			      else 
					  CustoTotal));

s.t. DefObjR{k in 1..1: relax==1} : Obj = if (OBJETIVO==1) then
			Zero
		      else
		        (if (OBJETIVO==3) then 
			    (sum{s in I, i in I, j in I, w in W: s!=j and i!=j and Hd[i,j]!=0} br[s,i,j,w]) 
			    else 
			      (if (OBJETIVO==2) then 
				Hmax 
			      else 
					  CustoTotal));


minimize OBJTV: Obj;


/*
printf('\n');
printf('CiT: ');
printf(CiT);
printf('\n');
printf('\n');
#printf('TLB: ');
#printf(TLB);
display{g in 2..13}: TLB[g];
printf('\n');
printf('LbT: ');
printf(LbT);
printf('\n');
printf('UbT: ');
printf(UbT);
printf('\n');
printf('\n');
*/
printf('\n');






















