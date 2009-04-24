
/*
Exemplo de arquivo de dados de entrada para o modelo Labtel-vtd. By fabiolimath@gmail.com

	Todos os par�metros comentados abaixo s�o opcionais e possuem um valor default.
	Se nenhum deles for setado, o modelo ir� calcular Hmax para a topologia B abaixo.
	
	Se "Traf" for setado para distribuir o tr�fego para Hmax, ele ir� calcular
	FTnet pelas vari�veis agregadas, ignorando as demais Flags. Neste caso,
	os uper bounds n�o ser�o setados.

	Para usar como fun��o objetivo, pela API, basta setar "topology". Opcionalmente 
	pode-se setar o "gl" para omitir as restri��es de grau l�gico.
	
	Todos os bounds s�o carregados em vari�veis, possibilitando a sua modifica��o em 
	tempo de execu��o.
	
Lista do que ainda falta integrar ao modelo:

###### TODO
# 7 - Boolean: (0) - Com particionamento de tr�fego (default); (1) - Sem particionamento;
#param PI default 0, binary;

# 8 - Float: (0) - Sem limita��o de atrazo (default); (>0) - Valor da limita��o;
#param alfa default 0, >= 0;

Obs.: Apenas para "Topologia inteira como Vari�vel" (para usar na API) e 
"Relaxa��o para FTnet" (para lower bound iterativo) ainda n�o h� modelo. 
Para os demais casos da lista acima existem modelos independentes.

*/

###################################
###### Par�metros Opcionais #######
###################################

###### Flags ###########
param bFTnet	:= 1;	# Boolean: Calcular o FTnet, default 0.
#param bHmax	:= 1;	# Boolean: Calcular o Hmax, default 0.
#param Ctrl	:= 1;	# Boolean: Otimizar Hmax (0) ou FTnet (1), quando ambos s�o calculados.
#param Traf	:= 2;	# Inteiro: Distribuir o tr�fego:
			# (0) - N�o distribui o tr�fego (default);
			# (1) - Distribui para Hmax (com bound);
			# (2) - Distribui para FTnet (com bound);
			# (3) - Distribui para Hmax (ponderado);
			# (4) - Distribui para FTnet (ponderado);
#param Dec	:= 2;	# Fator de pondera��o para o FTnet.
#param mult	:= 1;	# Boolean: (0) Topologia bin�ria; (1) Topologia Inteira;
#param relax	:= 1;	# Boolean: (0) Topologia Inteira; (1) Topologia Relaxada;
#param mini	:= 1;	# Boolean: Usar Restri��es de Limita��o de Fluxo Otimizadas;
#param miniLP	:= 1;	# Boolean: N�o usar Restri��es de Limita��o de Fluxo, para o caso LP;


###### MILP ou LP ######
param topology	:= 1;	 # Boolean: Usar a topologia como vari�vel, default 0.

###### Bounds ##########
#param FTnetUB	:= 17.4; # Uper Bound para FTnet.
#param HmaxUB	:= 10.9; # Lower Bound para FTnet.
#param FTnetLB	:= 17;	 # Uper Bound para Hmax.
#param HmaxLB	:= 8;	 # Lower Bound para Hmax.


###### Grau L�gico #####
param gl	:= 2;	 # 0 para n�o usar as restri��es de grau l�gico.

###################################
###### Par�metros Obrigat�rios ###
###################################

param N 	:= 6;

param Delta : 1   2   3   4   5   6  :=
	  1  0.0 3.0 2.1 6.0 0.5 0.3
	  2  0.5 0.0 0.9 0.9 0.8 0.8
	  3  3.3 0.4 0.0 0.7 0.2 0.4
	  4  0.7 0.2 0.2 0.0 0.8 0.3
	  5  0.4 6.8 0.6 1.2 0.0 0.4
	  6  0.4 0.7 0.6 0.1 0.1 0.0
;

param     B : 1   2   3   4   5   6  :=
	  1  0.0 0.0 0.0 1.0 1.0 0.0
	  2  0.0 0.0 1.0 1.0 0.0 0.0
	  3  1.0 1.0 0.0 0.0 0.0 0.0
	  4  1.0 0.0 0.0 0.0 0.0 1.0
	  5  0.0 1.0 0.0 0.0 0.0 1.0
	  6  0.0 0.0 1.0 0.0 1.0 0.0
;

end;
