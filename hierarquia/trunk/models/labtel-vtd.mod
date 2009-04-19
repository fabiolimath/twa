/* Formulação dos Modelos para a Minimização do Processamento e Congestionamento.

   Possíveis usos para este modelo:

   - Calcular o Congestionamento (Hmax) para uma topologia dada (default);
   - Calcular o Processamento (FTnet) para uma topologia dada;
   - Modelo MILP para o Congestionamento;
   - Modelo MILP para o Processamento;
   - Modelo relexado para o cálculo de Lower Bounds;
   - Distribuir* o tráfego para Hmax ou FTnet;
   - Minimizar Hmax ou FTnet;
   - Minimizar conjuntamente* Hmax e FTnet ponderando por um bound;
   - Minimizar conjuntamente* Hmax e FTnet ponderando por um fator configurável;
   - Limitação por bounds de Hmax ou FTnet;
   - Setar a topologia ou os bounds pela API;
   - Usar Restrições de Limitação de Fluxo Otimizadas;
   - Não usar Restrições de Limitação de Fluxo, para o caso LP;

   O uso desejado é definido pelos parâmetros lidos do arquivo de dados.

*: Um é calculado pelo tráfego agregado e o outro pelo distribuido.

   Descrição do modelo em MathProg por Fábio Lima (fabiolimath@gmail.com).
*/

#############################################################
########################### PARÂMETROS ######################
#############################################################

#############################################################
################## Identificação da Instância ###############
#############################################################

###### Parâmetro Obrigatório ####
# Numero de nós da rede 
param N, integer, > 0;
#################################

# Conjunto de indices
set I := 1..N;

###### Parâmetro Obrigatório ####
# Matriz de Trafego
param D{s in I, d in I};
#################################

# 4 - Matriz da topologia virtual
param B{i in I, j in I} default 0, >=0;

# 5 - Grau Lógico
param gl default 0, integer, >= 0, <= N-1;

# 6 - Constante para o cálculo do Lower Bound para o Congestionamento
param Magic default 0, >= 0;


# Matriz de Distâncias
param C{i in I, j in I} default 0, >=0;


#############################################################
########## Parâmetros de Controle de Usuário ################
#############################################################

# 1 - Inteiro: Hmax.
#	(0) - Não calcular Hmax;
#	(1) - Calcular Hmax pelo tráfego agregado;
#	(2) - Calcular Hmax pelo tráfego desagregado;
param bHmax default 0, integer, >= 0, <= 2;

# 2 - Inteiro: FTnet.
#	(0) - Não calcular FTnet;
#	(1) - Calcular FTnet pelo tráfego agregado;
#	(2) - Calcular FTnet pelo tráfego desagregado;
param bFTnet default 0, integer, >= 0, <= 2;

# 3 - Inteiro: Função Objetivo.
# 	(0) - Hmax;
#	(1) - FTnet;
#	(2) - Hmax + FTnet - CtrlHmaxUB;
#	(3) - Hmax + FTnet - CtrlFTnetUB;
#	(4) - FTnet/(N-Dec) + Hmax
param obj default 0, integer, >= 0, <= 4;

# 4 - Boolean:	(0) - Topologia como parâmetro (default); 
#		(1) - Topologia como variável;
param topology default 0, binary;

# 7 - Inteiro: Fator de ponderação para equilibrar Hmax e FTnet
param Dec default 0, integer, >= 0, < (N-1);

# 8 - Inteiro:	(0) - Sem relaxação; 
#		(1) - Topologia Relaxada Binária;
#		(2) - Topologia Relaxada até o grau lógico;
param relax default 0, integer;

# 9 - Inteiro:	Restrições de Limitação de Fluxo Otimizadas;
#	(0) - Usar Restrições de Limitação de Fluxo Clássicas;
#	(1) - Usar Restrições de Limitação de Fluxo Agregadas;
#	(2) - Não usar Restrições de Limitação de Fluxo, com topologia fixa;
param limFlow default 0, integer, >=0, <=2;

# 10 - Boolean: Usar Restrições de Conservação de Fluxo Agregadas, para o tráfego desagregado;
param aggtFlow default 0, binary;

########################## Bounds ############################

# 1 - Float: Lower Bound para FTnet.
param FTnetLB default 0, >=0;

# 2 - Float: Uper Bound para FTnet.
param FTnetUB default 0, >=0;

# 3 - Float: Lower Bound para Hmax.
param HmaxLB default if (gl!=0) then Magic/gl else 0, >=0;

# 4 - Float: Uper Bound para Hmax.
param HmaxUB default 0, >=0;

##############################################################
############## Fim dos Parâmetros de Controle ################
##############################################################

##############################################################
############## Parâmetros de controle interno ################
##############################################################

# Simplificam a interface com o usuário.

# Setando relax=2 apenas, entra em modo de cálculo do lower bond provável.
param ctrlGL, integer := if (gl!=0) then gl else
			 if (relax=2) then N-1 else 0;
param mult, binary :=    if (relax=2) then 1 else 0;

# Controla se a topologia é fixa ou variável.
param ctrlTopology, binary:= if (ctrlGL!=0 and (topology=1 or relax>0)) then 1 else 0;

# Se nada for setado, otimiza Hmax. Se apenas FTnet for setado, otimiza FTnet.
# Se algum objetivo for setado, prevalece.
param ctrlObj, integer, >= 0, <= 4 := if (obj>0) then 
				       (if (obj=1) then 1 else (if (ctrlTopology=0) then obj)) else
				       if (bHmax=0 and bFTnet>0) then 1 else 
				       if (Dec>0) then 4 else 0;

# Controla se o Tráfego será Distribuido ou Agregado e se será otimizado ou só calculado.
#	(0) - Otimizar Tráfego Agregado;
#	(1) - Otimizar o Tráfego Distribuido;
#	(2) - Otimizar Tráfego Agregado e Distribuir o Tráfego;
param ctrlTraf, integer, >=0, <=2 := if (bHmax<2 and bFTnet<2) then 0 else
				     if (bHmax=0 or  bFTnet=0) then 1 else 2;

# Controla se e como a Limitação de Fluxo, para tráfego agregado, será definida;
#	(0) - Limitação de Fluxo não será definida;
#	(1) - Será definida com topologia binária;
#	(2) - Será definida com topologia relaxada;
#	(3) - Será definida com topologia constante;
#	(4) - Será definida com topologia binária e equações agregadas por liagação;
#	(5) - Será definida com topologia relaxada e equações agregadas por liagação;
#	(6) - Será definida com topologia constante e equações agregadas por liagação;
param ctrlLimFlow, integer, >=0, <=6 := if (limFlow=2 or ctrlTraf=1) then 0 else
					if (limFlow=0) then
					(if (ctrlTopology=1) then 
					(if (relax=0) then 1 else 2) else 3)
					else
					(if (ctrlTopology=1) then
					(if (relax=0) then 4 else 5) else 6);

# Controla se e como a Limitação de Fluxo, para tráfego distribuido, será definida;
#	(0) - Limitação de Fluxo não será definida;
#	(1) - Será definida com topologia binária;
#	(2) - Será definida com topologia relaxada;
#	(3) - Será definida com topologia constante;
#	(4) - Será definida com topologia binária e equações agregadas por liagação;
#	(5) - Será definida com topologia relaxada e equações agregadas por liagação;
#	(6) - Será definida com topologia constante e equações agregadas por liagação;
param ctrlLimFlowDstrb, integer, >=0, <=6 := if (limFlow=2 or ctrlTraf=0) then 0 else
					if (limFlow=0) then
					(if (ctrlTopology=1) then 
					(if (relax=0) then 1 else 2) else 3)
					else
					(if (ctrlTopology=1) then
					(if (relax=0) then 4 else 5) else 6);

# Controla se e como o FTnet será definido;
#	(0) - FTnet não será definido;
#	(1) - FTnet será definido pelo tráfego agregado;
#	(2) - FTnet será definido pelo tráfego desagregado;
#	(3) - FTnet será definido pelo tráfego agregado, sem limitação de fluxo;
#	(4) - FTnet será definido pelo tráfego desagregado, sem limitação de fluxo;
param ctrlFTnet, integer, >= 0, <= 4 := if (bFTnet=0 and obj=0) then 0 else
					if (limFlow<2) then
					(if (bFTnet=2) then 2 else 1) 
					else
					if (ctrlTopology=0) then
					(if (bFTnet=2) then 4 else 3);

# Controla se e como o Hmax será definido;
#	(0) - Hmax não será definido;
#	(1) - Hmax será definido pelo tráfego agregado;
#	(2) - Hmax será definido pelo tráfego desagregado;
#	(3) - Hmax será definido pelo tráfego agregado, sem limitação de fluxo;
#	(4) - Hmax será definido pelo tráfego desagregado, sem limitação de fluxo;
param ctrlHmax, integer, >= 0, <= 4 := if (bHmax=0 and ctrlObj=1) then 0 else
					if (limFlow<2) then
					(if (bHmax=2) then 2 else 1) 
					else
					if (ctrlTopology=0) then
					(if (bHmax=2) then 4 else 3);

################# Agregação do Tráfego ######################

# Somas do tráfego partindo de cada nó
param hs{s in I}  :=  sum{d in I: d!=s} D[s,d];

# Para cada nó, soma todo o tráfego partindo dos demais nós
param hts{s in I}  :=  sum{d in I: d!=s} hs[d];

###### TODO
# 1 - Boolean: (0) - Com particionamento de tráfego (default); (1) - Sem particionamento;
#param PI default 0, binary;

# 2 - Float: (0) - Sem limitação de atrazo (default); (>0) - Valor da limitação;
#param alfa default 0, >= 0;

# 3 - Modelo com suporte a multiplicidade de ligações;

#############################################################
########################### VARIÁVEIS #######################
#############################################################

########################### TOPOLOGIA #####################

# Matriz da topologia virtual inteira
var b{i in I, j in I}, integer, >= 0, <= 1 + (mult)*(ctrlGL-1);

# Matriz da topologia virtual relaxada
var rb{i in I, j in I}, >= 0, <= 1 + mult*(ctrlGL-1);

########################### FTnet ###########################

# Tráfego Retransmitido na Rede
var FTnet, >= 0;

# Tráfego Retransmitido em cada nó
var FT{i in I}, >=0;

########################### Hmax ############################

# Congestionamento Máximo
var Hmax, >= 0;

# Tráfego em cada ligação
var Trafego{i in I, j in I: i!=j}, >=0;

######################## FUNÇÃO OBJETIVO ####################

# 1 - Controle de FTnet
var CtrlFTnetUB, >= 0;
var CtrlFTnetLB, >= 0;

# 2 - Controle de Hmax
var CtrlHmaxUB, >= 0;
var CtrlHmaxLB, >= 0;

# 2 - Função Objetivo
var Z, >= 0;

#################### COMPONENTES DE TRÁFEGO #################

# Parcela de tráfego vindo de "s" passando pelo enlece (i,j)
var h{ i in I, j in I,s in I: j!=s} >= 0, <= hs[s]*(1 + (mult)*(ctrlGL-1));

# Porcentágem do tráfego vindo de "s" passando pelo enlece (i,j)
var q{ i in I, j in I,s in I: j!=s} >= 0, <=1;

# Parcela de tráfego vindo de "s", indo para "d", passando pelo enlece (i,j)
var H{ i in I, j in I, s in I, d in I: j!=s and i!=d} >= 0, <= D[s,d]*(1 + (mult)*(ctrlGL-1));

# Porcentágem do tráfego vindo de "s", indo para "d", passando pelo enlece (i,j)
var qq{ i in I, j in I, s in I, d in I: j!=s and i!=d} >= 0, <=1;

#############################################################
########################### RESTRIÇÕES ######################
#############################################################

#################### CONSERVAÇÃO E LIMITAÇÃO ################

######################## Tráfego Agregado ###################
# Restriçao de Limitaçao de Fluxo Agregado.
s.t.  LimFlow{i in I, j in I, s in I: s!=j and ctrlLimFlow < 4 and ctrlLimFlow > 0}: 
h[i,j,s] <= if (ctrlLimFlow=1) then (b[i,j] * hs[s]) else
	    if (ctrlLimFlow=2) then (rb[i,j] * hs[s]) else
	    if (ctrlLimFlow=3) then (B[i,j] * hs[s]);

s.t.  LimFlowAggt{i in I, j in I: ctrlLimFlow > 3}:
sum{s in I: s!=j} h[i,j,s] <= 
				if (ctrlLimFlow=4) then (b[i,j] * hts[j]) else
				if (ctrlLimFlow=5) then (rb[i,j] * hts[j]) else
				if (ctrlLimFlow=6) then (B[i,j] * hts[j]);

# Restriçao de Conservaçao de Tráfego Agregado.
s.t.           ConservFlow{i in I, s in I: ctrlTraf!=1 and limFlow<2}: 
      sum{j in I: j!=s and i!=j} h[i,j,s] 
    - sum{j in I: i!=s and i!=j} h[j,i,s] 
    = if (s!=i) then -D[s,i] else hs[s];
	
s.t.  ConservFlowNoLimFlow{i in I, s in I:ctrlTraf!=1 and  limFlow=2 and ctrlTopology=0}: 
      sum{j in I: j!=s and i!=j} q[i,j,s]*hs[s]*B[i,j] 
    - sum{j in I: i!=s and i!=j} q[j,i,s]*hs[s]*B[j,i] 
    = if (s!=i) then -D[s,i] else hs[s];

######################## Tráfego Distribuido ################
# Restriçao de Limitaçao de Fluxo Distribuido.

s.t.  LimFlowDstrb{i in I, j in I, s in I, d in I: s!=j and d!=i and ctrlLimFlowDstrb>0 and ctrlLimFlowDstrb<4}: 
H[i,j,s,d] <= if (ctrlLimFlowDstrb=1) then (b[i,j] * D[s,d]) else
	    if (ctrlLimFlowDstrb=2) then (rb[i,j] * D[s,d]) else
	    if (ctrlLimFlowDstrb=3) then (B[i,j] * D[s,d]);

s.t.  LimFlowDstrbAggt{i in I, j in I: ctrlLimFlowDstrb > 3}:
sum{s in I, d in I: d!=i and s!=j} H[i,j,s,d] <= 
				if (ctrlLimFlowDstrb=4) then (b[i,j] * hts[j]) else
				if (ctrlLimFlowDstrb=5) then (rb[i,j] * hts[j]) else
				if (ctrlLimFlowDstrb=6) then (B[i,j] * hts[j]);

# 1 - Restriçao de conservaçao de trafego
s.t. ConservFlowDstrb{i in I, s in I, d in I:i!=d and ctrlTraf!=0 and limFlow<2 and aggtFlow=0}: 
	  sum{j in I: j!=s and i!=d and i!=j} H[i,j,s,d] 
	- sum{j in I: j!=d and i!=s and i!=j} H[j,i,s,d] 
	= (if (s!=i and d!=i) then 0 else (if (s==i) then D[s,d] else -D[s,d]));

s.t. ConservFlowDstrbNoLimFlow{i in I, s in I, d in I:i!=d and ctrlTraf!=0 and limFlow=2 and ctrlTopology=0 and aggtFlow=0}: 
	  sum{j in I: j!=s and i!=d and i!=j} qq[i,j,s,d]*D[s,d]*B[i,j] 
	- sum{j in I: j!=d and i!=s and i!=j} qq[j,i,s,d]*D[s,d]*B[j,i] 
	= (if (s!=i and d!=i) then 0 else (if (s==i) then D[s,d] else -D[s,d]));

s.t. aggtConservFlowDstrb{i in I, s in I:ctrlTraf!=0 and limFlow<2 and aggtFlow=1}: 
	  sum{j in I, d in I:i!=d and j!=s and i!=j and s!=d} H[i,j,s,d] 
	- sum{j in I, d in I:j!=d and i!=s and i!=j and s!=d} H[j,i,s,d] 
	= if (s!=i) then -D[s,i] else hs[s];

s.t. aggtConservFlowDstrbNoLimFlow{i in I, s in I:ctrlTraf!=0 and limFlow=2 and aggtFlow=1 and ctrlTopology=0}: 
	  sum{j in I, d in I:i!=d and j!=s and i!=j} qq[i,j,s,d]*D[s,d]*B[i,j] 
	- sum{j in I, d in I:j!=d and i!=s and i!=j} qq[j,i,s,d]*D[s,d]*B[j,i] 
	= if (s!=i) then -D[s,i] else hs[s];

###################### Desagregação ########################
s.t.     Unaggt{ i in I, j in I, s in I: j!=s and i!=j and ctrlTraf=2 and limFlow<2}: 
	h[i,j,s] = (sum{d in I: d!=i} H[i,j,s,d]);

s.t. UnaggtNoLimFlow{ i in I, j in I, s in I: j!=s and i!=j and ctrlTraf=2 and limFlow=2 and ctrlTopology=0}: 
	q[i,j,s]*hs[s]*B[i,j] = (sum{d in I: d!=i} qq[i,j,s,d]*D[s,d]*B[i,j]);


########################### FTnet ###########################

# Definição do tráfego retransmitido em cada nó
s.t. defTraf{i in I: ctrlFTnet > 0}: 
FT[i] = if (ctrlFTnet=1) then
	   (sum{j in I, s in I: j!=s and i!=s and i!=j} h[i,j,s]) else
	if (ctrlFTnet=2) then
	   (sum{j in I, s in I, d in I: j!=s and i!=d and j!=d and i!=j} H[i,j,s,d]) else
	if (ctrlFTnet=3) then
	   (sum{j in I, s in I: j!=s and i!=s and i!=j} q[i,j,s]*hs[s]*B[i,j]) else
	if (ctrlFTnet=4) then
	   (sum{j in I, s in I, d in I: j!=s and i!=d and j!=d and i!=j} qq[i,j,s,d]*D[s,d]*B[i,j]);

# Definição do tráfego retransmitido na rede
s.t. defFTnet{k in 1..1 : ctrlFTnet > 0}: 
FTnet = sum{i in I} FT[i];

########################### Hmax ############################

# Tráfego de cada liagação
s.t. Traf{i in I, j in I: i!=j and ctrlHmax>0}: 
Trafego[i,j]= if (ctrlHmax=1) then (sum{s in I:j!=s} h[i,j,s]) else
	      if (ctrlHmax=2) then (sum{s in I, d in I:j!=s and i!=d} H[i,j,s,d]) else
	      if (ctrlHmax=3) then (sum{s in I:j!=s} q[i,j,s]*hs[s]*B[i,j]) else
	      if (ctrlHmax=4) then (sum{s in I, d in I:j!=s and i!=d} qq[i,j,s,d]*D[s,d]*B[i,j]);

# Congestionamento da rede
s.t. cong{i in I, j in I: i!=j and ctrlHmax>0}: 
Hmax >= if (relax>0) then 
	   (Trafego[i,j] + HmaxLB*(1 - rb[i,j])) else 
	   Trafego[i,j];

########################### GRAU LÓGICO #####################

# 1 - Grau Lógico de Entrada
s.t.  graulogin{j in I: ctrlTopology=1}: 
ctrlGL = if (relax=0) then 
	(sum{i in I: i!=j} b[i,j]) else 
	(sum{i in I: i!=j} rb[i,j]);

# 2 - Grau Lógico de Saida
s.t. graulogout{i in I: ctrlTopology=1}: 
ctrlGL = if (relax=0) then 
	(sum{j in I: i!=j} b[i,j]) else 
	(sum{j in I: i!=j} rb[i,j]);

############################# LIMITAÇÃO ######################

# 1 - Controle de FTnet
s.t. controlFTnetUB {k in 1..1 : ctrlFTnet>0 and FTnetUB>0}: CtrlFTnetUB = FTnetUB;
s.t. controlFTnetLB {k in 1..1 : ctrlFTnet>0 and FTnetLB>0}: CtrlFTnetLB = FTnetLB;
s.t. controlFTnetUB2{k in 1..1 : ctrlFTnet>0 and FTnetUB>0 and ctrlObj!=3}: CtrlFTnetUB >= FTnet;
s.t. controlFTnetLB2{k in 1..1 : ctrlFTnet>0 and FTnetLB>0}: CtrlFTnetLB <= FTnet;

# 2 - Controle de Hmax
s.t. controlHmaxUB {k in 1..1 : ctrlHmax>0 and HmaxUB>0}: CtrlHmaxUB = HmaxUB;
s.t. controlHmaxLB {k in 1..1 : ctrlHmax>0 and HmaxLB>0}: CtrlHmaxLB = HmaxLB;
s.t. controlHmaxUB2{k in 1..1 : ctrlHmax>0 and HmaxUB>0 and ctrlObj!=2}: CtrlHmaxUB >= Hmax;
s.t. controlHmaxLB2{k in 1..1 : ctrlHmax>0 and HmaxLB>0 and relax=0}: CtrlHmaxLB <= Hmax;


#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

s.t. chobj: Z = if (ctrlObj = 0) then Hmax else
		if (ctrlObj = 1) then FTnet else
		if (ctrlObj = 2) then (FTnet + Hmax - CtrlHmaxUB ) else
		if (ctrlObj = 3) then (FTnet + Hmax - CtrlFTnetUB) else
		if (ctrlObj = 4) then (FTnet/(N-Dec) + Hmax);

minimize objetivo: Z;

solve;
printf "FTnet: %.9f\n", FTnet;
printf "  Hmax : %.9f\n", Hmax;
printf "HmaxLB : %.9f\n", HmaxLB;
printf "ctrlGL*Hmax : %.9f\n", ctrlGL*Hmax;

end;

























