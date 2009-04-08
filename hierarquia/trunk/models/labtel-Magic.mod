/* Formulação do Modelo para o Calculo do Loewr Bound do Congestionamento.
   Descrição do modelo em MathProg por Fábio Lima (fabiolimath@gmail.com).
*/

#############################################################
################## Identificação da Instância ###############
#############################################################

# 1 - Numero de nós da rede 
param N, integer, > 0;

# 2 - Conjunto de indices
set I := 1..N;

# 3 - Matriz de Trafego
param D{s in I, d in I};

# 4 - Grau Lógico.
param gl default 0, integer, >= 0, <= N-1;

# 5 - Lower Bound para o Congestionamento.
param HmaxLB default 0, >= 0;

##############################################################
############## Parâmetros de controle interno ################
##############################################################


# 1 - Setando relax=2 apenas, entra em modo de cálculo do lower bond provável.
param ctrlGL, integer := N-1;

# 2 - Topologia inteira.
param mult default 1, binary;

################# Agregação do Tráfego ######################

# 1 - Somas do tráfego partindo de cada nó
param hs{s in I}  :=  sum{d in I: d!=s} D[s,d];

# 2 - Para cada nó, soma todo o tráfego partindo dos demais nós
param hts{s in I}  :=  sum{d in I: d!=s} hs[d];

#### Parâmetros para Compatibilidade com outros modelos #####

# 1 - Topologia física.
param C{s in I, d in I};

#############################################################
########################### VARIÁVEIS #######################
#############################################################

# 1 - Matriz da topologia virtual relaxada
var rb{i in I, j in I}, >= 0, <= 1 + mult*(ctrlGL-1);

# 2 - Congestionamento Máximo
var Hmax, >= 0;

# 3 - Parcela de tráfego vindo de "s" passando pelo enlece (i,j)
var h{ i in I, j in I,s in I: j!=s} >= 0, <= hs[s]*(1 + (mult)*(ctrlGL-1));

#############################################################
########################### RESTRIÇÕES ######################
#############################################################

# 1 - Restriçao de Limitaçao de Fluxo Agregado.
s.t.  LimFlow{i in I, j in I, s in I: s!=j}: h[i,j,s] <= rb[i,j] * hs[s];

# 2 - Restriçao de Conservaçao de Tráfego Agregado.
s.t.           ConservFlow{i in I, s in I}: 
      sum{j in I: j!=s and i!=j} h[i,j,s] 
    - sum{j in I: i!=s and i!=j} h[j,i,s] 
    = if (s!=i) then -D[s,i] else hs[s];

# 3 - Grau Lógico de Entrada
s.t.  graulogin{j in I}: 
ctrlGL = sum{i in I: i!=j} rb[i,j];

# 4 - Grau Lógico de Saida
s.t. graulogout{i in I}: 
ctrlGL = sum{j in I: i!=j} rb[i,j];

########################### Hmax ############################

# 5 - Congestionamento da rede
s.t. cong{i in I, j in I: i!=j}: 
Hmax >= sum{s in I:j!=s} h[i,j,s] + HmaxLB*(1 - rb[i,j]);

#############################################################
######################## FUNÇÃO OBJETIVO ####################
#############################################################

minimize objetivo: Hmax;

solve;
printf "  Hmax : %.9f\n", Hmax;
printf "HmaxLB : %.9f\n", HmaxLB;
printf "Magic : %.9f\n", ctrlGL*Hmax;

end;

























