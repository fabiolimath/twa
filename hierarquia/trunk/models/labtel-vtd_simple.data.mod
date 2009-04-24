
/*
Exemplo de arquivo de dados de entrada para o modelo Labtel-vtd. By fabiolimath@gmail.com

	Todos os parâmetros comentados abaixo são opcionais e possuem um valor default.
	Se nenhum deles for setado, o modelo irá calcular Hmax para a topologia B abaixo.
	
	Se "Traf" for setado para distribuir o tráfego para Hmax, ele irá calcular
	FTnet pelas variáveis agregadas, ignorando as demais Flags. Neste caso,
	os uper bounds não serão setados.

	Para usar como função objetivo, pela API, basta setar "topology". Opcionalmente 
	pode-se setar o "gl" para omitir as restrições de grau lógico.
	
	Todos os bounds são carregados em variáveis, possibilitando a sua modificação em 
	tempo de execução.
	
Lista do que ainda falta integrar ao modelo:

###### TODO
# 7 - Boolean: (0) - Com particionamento de tráfego (default); (1) - Sem particionamento;
#param PI default 0, binary;

# 8 - Float: (0) - Sem limitação de atrazo (default); (>0) - Valor da limitação;
#param alfa default 0, >= 0;

Obs.: Apenas para "Topologia inteira como Variável" (para usar na API) e 
"Relaxação para FTnet" (para lower bound iterativo) ainda não há modelo. 
Para os demais casos da lista acima existem modelos independentes.

*/

###################################
###### Parâmetros Opcionais #######
###################################

###### Flags ###########
param bFTnet	:= 1;	# Boolean: Calcular o FTnet, default 0.
#param bHmax	:= 1;	# Boolean: Calcular o Hmax, default 0.
#param Ctrl	:= 1;	# Boolean: Otimizar Hmax (0) ou FTnet (1), quando ambos são calculados.
#param Traf	:= 2;	# Inteiro: Distribuir o tráfego:
			# (0) - Não distribui o tráfego (default);
			# (1) - Distribui para Hmax (com bound);
			# (2) - Distribui para FTnet (com bound);
			# (3) - Distribui para Hmax (ponderado);
			# (4) - Distribui para FTnet (ponderado);
#param Dec	:= 2;	# Fator de ponderação para o FTnet.
#param mult	:= 1;	# Boolean: (0) Topologia binária; (1) Topologia Inteira;
#param relax	:= 1;	# Boolean: (0) Topologia Inteira; (1) Topologia Relaxada;
#param mini	:= 1;	# Boolean: Usar Restrições de Limitação de Fluxo Otimizadas;
#param miniLP	:= 1;	# Boolean: Não usar Restrições de Limitação de Fluxo, para o caso LP;


###### MILP ou LP ######
param topology	:= 1;	 # Boolean: Usar a topologia como variável, default 0.

###### Bounds ##########
#param FTnetUB	:= 17.4; # Uper Bound para FTnet.
#param HmaxUB	:= 10.9; # Lower Bound para FTnet.
#param FTnetLB	:= 17;	 # Uper Bound para Hmax.
#param HmaxLB	:= 8;	 # Lower Bound para Hmax.


###### Grau Lógico #####
param gl	:= 2;	 # 0 para não usar as restrições de grau lógico.

###################################
###### Parâmetros Obrigatórios ###
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
