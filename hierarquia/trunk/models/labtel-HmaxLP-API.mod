/* Formulação do Modelo Aggregate MILP [Ramaswami, 96]

   Descrição do modelo em MathProg por Fábio Lima (fabiolimath@yahoo.com.br).
*/

#############################################################
########################### PARÂMETROS ######################
#############################################################

# 1 - Numero de nós da rede 
param N, integer, > 0;

# 2 - Conjunto de indices
set I := 1..N;

# 3 - Matriz de Trafego
param D{s in I, d in I};

# 4 - Somas do tráfego partindo de cada nó
param hs{s in I}  :=  sum{d in I: d!=s} D[s,d];

# 5 - Plano de Corte inicial (MFT bound, por exemplo)
param HmaxLB default 0;
param gl default 0;
param C{s in I, d in I} default 1;
#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Matriz da topologia virtual
var B{i in I, j in I}, >=0, <=1;

# 2 - Parcela de tráfego vindo de "s" passando pelo enlece (i,j)
var h{ i in I, j in I,s in I: j!=s} >= 0;

# 3 - Congestionamento Máximo
var Hmax >=HmaxLB;

#############################################################
########################### RESTRIÇÕES ######################
#############################################################

# 1 - Restriçao de limitaçao de fluxo tipo 1.
s.t.  limit{i in I, j in I}: Hmax >= sum{s in I: j!=s} h[i,j,s];

# 4 - Restriçao de limitaçao de fluxo tipo 2.
s.t.  limit2{i in I, j in I, s in I: j!=s}: h[i,j,s] <= (B[i,j] * hs[s]);

# 6 - Restriçao de conservaçao de trafego tipo 3.
s.t.  conserv2{i in I, s in I}: 
      sum{j in I: j!=s} h[i,j,s] - sum{j in I: i!=s} h[j,i,s] =
	if (s!=i) then -D[s,i] else hs[s];


#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

minimize congestionamento: Hmax;

end;
