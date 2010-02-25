/* 
Formulação do Modelo Aggregate MILP [Ramaswami, 96]

   Descrição do modelo em MathProg por Fábio Lima (fabiolimath@gmail.com).
*/


#############################################################
########################### PARÂMETROS ######################
#############################################################

# 1 - Numero de nós da rede 
param N 'Numero de nós' , integer, > 0;

# 2 - Conjunto de indices
set I := 1..N;

# 3 - Matriz de Trafego
param Delta 'Matriz de Trafego' {s in I, d in I};

# 4 - Topologia Virtual
param B{i in I, j in I}, integer, >= 0;

# 5 - Somas do tráfego partindo de cada nó
param hs{s in I}  :=  sum{d in I: d!=s} Delta[s,d];

# 6 - Lowerbound para o congestionamento
param HmaxL default 0;

# 7 - Multiplicidade das ligações
set L{i in I, j in I} := 1..B[i,j];

#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Parcela de tráfego vindo de "s" passando pelo enlece (i,j)
var h{ i in I, j in I,s in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0} >= 0;

# 2 - Congestionamento Máximo
var Hmax >=HmaxL;


#############################################################
########################### RESTRIÇÕES ######################
#############################################################

# 1 - Restriçao de limitaçao de fluxo
s.t.  limit{i in I, j in I, k in L[i,j]: i!=j and B[i,j]!= 0}: Hmax >= sum{s in I: j!=s} h[i,j,s,k];

# 4 - Restriçao de limitaçao de fluxo tipo 2
s.t.  limit2{i in I, j in I, s in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0}: h[i,j,s,k] <= hs[s];

# 5 - Restriçao de conservaçao de trafego tipo 2
s.t.  conserv2{i in I, s in I}: 
      sum{j in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0} h[i,j,s,k] - sum{j in I, k in L[j,i]: i!=j and i!=s and B[j,i]!= 0} h[j,i,s,k] =
	if (s!=i) then -Delta[s,i] else hs[s];


#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

minimize congestionamento: Hmax;

end;

























