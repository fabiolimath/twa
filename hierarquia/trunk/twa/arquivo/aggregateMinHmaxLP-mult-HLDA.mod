/* 
Formula��o do Modelo Aggregate MILP [Ramaswami, 96]

   Descri��o do modelo em MathProg por F�bio Lima (fabiolimath@gmail.com).
*/


#############################################################
########################### PAR�METROS ######################
#############################################################

# 1 - Numero de n�s da rede 
param N 'Numero de n�s' , integer, > 0;

# 2 - Conjunto de indices
set I := 1..N;

# 3 - Matriz de Trafego
param Delta 'Matriz de Trafego' {s in I, d in I};

# 4 - Topologia Virtual
param B{i in I, j in I}, integer, >= 0;

# 5 - Somas do tr�fego partindo de cada n�
param hs{s in I}  :=  sum{d in I: d!=s} Delta[s,d];

# 6 - Lowerbound para o congestionamento
param HmaxL default 0;

# 7 - Multiplicidade das liga��es
set L{i in I, j in I} := 1..B[i,j];

#############################################################
########################### VARI�VEIS #######################
#############################################################

# 1 - Parcela de tr�fego vindo de "s" passando pelo enlece (i,j)
var h{ i in I, j in I,s in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0} >= 0;

# 2 - Congestionamento M�ximo
var Hmax >=HmaxL;


#############################################################
########################### RESTRI��ES ######################
#############################################################

# 1 - Restri�ao de limita�ao de fluxo
s.t.  limit{i in I, j in I, k in L[i,j]: i!=j and B[i,j]!= 0}: Hmax >= sum{s in I: j!=s} h[i,j,s,k];

# 4 - Restri�ao de limita�ao de fluxo tipo 2
s.t.  limit2{i in I, j in I, s in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0}: h[i,j,s,k] <= hs[s];

# 5 - Restri�ao de conserva�ao de trafego tipo 2
s.t.  conserv2{i in I, s in I}: 
      sum{j in I, k in L[i,j]: i!=j and j!=s and B[i,j]!= 0} h[i,j,s,k] - sum{j in I, k in L[j,i]: i!=j and i!=s and B[j,i]!= 0} h[j,i,s,k] =
	if (s!=i) then -Delta[s,i] else hs[s];


#############################################################
######################## FUN��O OBJETIVO ####################
#############################################################

minimize congestionamento: Hmax;

end;

























