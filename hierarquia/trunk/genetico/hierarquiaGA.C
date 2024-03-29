
#include "include/cabecalho.h"
#include "include/hierarquiaGA.h"

// #include "ga/GAStatistics.h"
enum {
    NoScores=0x00,
    Mean=0x01,
    Maximum=0x02,
    Minimum=0x04,
    Deviation=0x08,
    Diversity=0x10,
    AllScores=0xff
    };
    
// Definições:
#define default_Replacement 3
#define default_Mutation 0.1
#define default_Crossover 1.0
#define default_CENTER 10

float replacemen;
float mutate;
float crossing;



// Class hierarquiaGA - Classe que define uma hierarquia para o problema através de um algoritmo genético.

// Inicia as variáveis, gera as matrizes e seta a semente do genético.
void hierarquiaGA::IniciaGA (int argc, char** argv)
{
  if (Ma == 0) IniciaH(argc,argv);
  
  /// Leitura dos parâmetros de linha de comando:
//   cerr << "\nLeitura dos parâmetros de linha de comando:\n\n";
  
  replacemen = default_Replacement;
  mutate = default_Mutation;
  crossing = default_Crossover;
  
  for(int i=1; i<argc;) 
  {
    if(strcmp(argv[i++],"-c") == 0) 
    {
      char *CONFIG_FILE;
      CONFIG_FILE = argv [ i ] ;
      
      ifstream in(CONFIG_FILE); 
      
      if(!in) {
	cerr << "could not read config file " << CONFIG_FILE << "\n";
	exit(1);
      }
      
      do 
      {
	string buffer;
	in >> buffer;
	
	if ( buffer == "#define" )
	  {
	    in >> buffer;
	    
	    ostringstream oss;
	    oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".info";
	    string dir = oss.str();
	    
	    ofstream file( dir.c_str(), ofstream::app );
	    if ( file.is_open() )
	    {	    
	      if ( buffer == "Replacement")
	      {
		in >> replacemen;
		getline(in, buffer);
		file << "\n Lido: Replacement= " << replacemen << ", Comentário: " << buffer;
		continue;
	      }
	      
	      if ( buffer == "Mutation") 
	      {
		in >> mutate;
		getline(in, buffer);
		file << "\n Lido: Mutation= " << mutate << ", Comentário: " << buffer;
		continue;
	      }
	      
	      if ( buffer == "Crossover") 
	      {
		in >> crossing;
		getline(in, buffer);
		file << "\n Lido: Crossover= " << crossing << ", Comentário: " << buffer;
		continue;
	      }
	      
	      file.close();
	    }
	  }
      } while(!in.eof());
    }
  }
  
  CENTER = default_CENTER;
  
  /// variáveis do GA
  N_POPULATIONS = 100;	// Número de populações paralelas.
  POP_SIZE = 100;		// Tamanho das populações.
  MAX_ESTAG = 100;	// Número de gerações (critério de parada).
  GEN_SIZE = (NTOWNS + Ma);	// Tamanho do Cromossomo (NTOWNS+Ma);
  MAX_TOWNS  = GEN_SIZE;	// Igual ao Tamanho do Cromossomo.
  
  for(int i=1; i<argc;) 
  {
    if(strcmp(argv[i++],"-estag") == 0) 
    {
      MAX_ESTAG = atoi ( argv [ i ] ) ;	// Matriz de entrada;
    }
  }
  
  for(int i=1; i<argc;) 
  {
    if(strcmp(argv[i++],"-popsize") == 0) 
    {
      POP_SIZE = atoi ( argv [ i ] ) ;	// Matriz de entrada;
    }
  }
  
  for(int i=1; i<argc;) 
  {
    if(strcmp(argv[i++],"-npop") == 0) 
    {
      N_POPULATIONS = atoi ( argv [ i ] ) ;	// Matriz de entrada;
    }
  }
// 	cerr << "\n\nIniciaH fim\n\n";
  
}// ::Inicia


// Executa o genético, guarda o melhor indivíduo e retorna o tempo de execução.
int hierarquiaGA::Evolve (int argc, char** argv) 
{
  if (CENTER == 0) IniciaGA(argc,argv);
  
  
//   cerr << "\nConfiguracao do genetico.\n\n";
  GAListGenome<int> genome(Objective);	/// Cromossomo.
  genome.initializer(::Initializer);	// Função que gera a população inicial.
  genome.mutator(::Mutator);		// Função que faz a mutacao.
  genome.comparator(::Comparator);		// Função que faz a comparacao entre cromossomos.
  genome.crossover(XOVER);			// Função que faz o cruzamento de cromossomos.
  
  GADemeGA ga(genome);			/// Algoritmo Genetico utilizado.
  //GASteadyStateGA ga(genome);		// Algoritmo Genetico alternativo. 
  
  ga.nPopulations(N_POPULATIONS);		//N_POPULATIONS Seta o número de populações paralelas.
  //GADemeGA::ALL;
  
  ga.minimize();				// Seta o sentido de otimização.
  ga.nReplacement(replacemen);
  ga.populationSize(POP_SIZE);		//POP_SIZE Seta o tamanho das populações.
//   ga.nGenerations(N_GENERATIONS);		// Seta o número de gerações (critério de parada).
//   ga.pConvergence(0.90);
//   ga.nConvergence(10);

  ga.pMutation(mutate);			// Probabilidade de mutação.
  ga.pCrossover(crossing);			// Probabilidade de cruzamento.
  ga.selectScores(GAStatistics::AllScores);
  ga.parameters(argc, argv);  
  ga.terminator(GAGeneticAlgorithm::TerminateUponConvergence);
  
  //Seta o Criterio de parada.
/*  ga.terminator(GATerminateUponScore);
  STOP_CRITERION = 0.01;*/
  	cerr << "\n\nInicia a evolução\n\n";

   cout << "DistB" << "\t" << "DistC" << "\t" << "Traf" << "\t" << "Score" << "\n";

  ga.initialize(seed);			// Seta a semente.
  
  double tempo = clock();			// Marca o inicio do algoritmo.
  
//   ga.evolve();				// Executa o genético.

ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".GAStatistics";
  string dir = oss.str();
  
  ofstream file( dir.c_str(), ofstream::app );
  if ( file.is_open() )
  {

  ga.initialize();
  
  file << "gen\tcMean\tcMax\tcMin\tcDev\tMedG\tMedMin\tMedMax\tMaxG\tBest\tEstag\n"  ;
  
  int estag = 0;
  
  while(!ga.done()){
   
   float prev = ga.statistics().minEver();
     
   ++ga;
   
   float next = ga.statistics().minEver();
   
   file << " "  << ga.statistics().generation();
   file << "\t"  << ga.statistics().current(Mean);
   file << "\t"  << ga.statistics().current(Maximum);
   file << "\t"  << ga.statistics().current(Minimum);
   file << "\t"  << ga.statistics().current(Deviation);
   file << "\t"  << ga.statistics().online();
   file << "\t"  << ga.statistics().offlineMin();
   file << "\t"  << ga.statistics().offlineMax();
   file << "\t"  << ga.statistics().maxEver();
   file << "\t"  << ga.statistics().minEver();

   
   if ( (prev/next) == 1.0 )
      estag++;
   else
      estag = 0;
   
   file << "\t"  << estag << "\n" ;
   cerr << " "  << ga.statistics().generation() << "\t" << estag << "\t" << (clock() - tempo)/CLOCKS_PER_SEC << "\n"; 
//    cerr << "MAX_ESTAG = " << MAX_ESTAG << "\n";
   if (estag > MAX_ESTAG) break;

  }


   file.close();
  }
  
  tempo = clock() - tempo;			// Marca o fim do algori­tmo.
  temposeg = tempo/CLOCKS_PER_SEC;
  
//   cerr << "\nCaptura o melhor indivíduo visitado pelo genético.\n\n";
  best = (GAListGenome<int> &)ga.statistics().bestIndividual();
  
  if(best.head()) 
  {
    score = Solucao(best);
    return 0;
  }
  else
  {
    return 1;
  }
  
  
}// ::Evolve()

// Decodifica o cromossomo e devolve o Fitness.
float hierarquiaGA::Solucao (GAListGenome<int> & gen)
{
  // Vetor temporário, que quardará os nós da hierarquia antes de separá-los em clusters.
  int *Vtmp = (int*) calloc (NTOWNS+1, sizeof(int));
  
  for (int i = 0, j = 0, l = 0, k = NTOWNS, aux = 0; i < GEN_SIZE; i++) 
  {// Varre todo o cromossomo.
    
    if ( *gen.warp(i) < NTOWNS ) 
    {// Se o gene é menor que NTOWNS, ele é será um nó da hierarquia...
      Vtmp[j++] = *gen.warp(i);
    }
    else 
    {// Caso contrário, tentaremos interpretá-lo como tamanho dos clusters
      if (!Sn) 
	{// Se todos os tamanhos ainda não foram definidFitnessos...
  
	  // Capitura o próximo candidato a tamanho.
	  aux = ( *gen.warp(i)%(Mac - Mic) ) + Mic;
	  
	  // Se o candidato não esgotar a possibilidade de outros clusters...
	  if ( (k - aux) >= Mic ) 
	  {
	    T[l++] = aux; 	// registra o tamanho do cluster,
	    k -= aux; 		// e decrementa o número de nós.
	  }
	  else 		  
	  {			// ... do contrário,
	    T[l] = k;  		// registra o restante dos nós como tamanho do cluster,
	    Sn = l + 1;		// Garda a quantidade total de clusters
	    k = 0;		// e finaliza a busca por tamanhos.
	  }// if( (k-aux)>=Mic ) 
	}// if (!Sn)
      }// if ( *gen.warp(i)<NTOWNS ) 
  }//i
  
  for (int k = 0, h = 0; k < Sn; k++) 
  {
    //     cout << "\n" << k << " => ";
    cluster[Sn][k] = Vtmp[h];
    for ( int j = 0; j < T[k]; j++ )
    {// copia os nós do cluster para a matriz de clusters
      cluster[k][j] = Vtmp[ h + j ];
      // cout << " - " << cluster[k][j] << " " << Vtmp[ h + j ];
    }//j
    h += T[k];
  }//i
  T[Sn]=Sn;
  
  free (Vtmp);
  
  //   cout << "\nFO - score = " << score;
  return Fitness();
}// ::solucao

// Calcula o Fitness, dentro de "solucao()".
float hierarquiaGA::Fitness ()
{ 
  /// //////////////////////////////////////////////////////////////////////////
  /// Calcula o Fitness.
  
  FitnessDistC = 0;	// Acumula das distâncias dos clusters.
  FitnessDistB = 0;	// Acumula das distâncias do backbone.
  FitnessTraf = 0;	// Acumula o tráfego.
  
  NDC = 0;			// Número de Distancias total dos Clusters.
  NDB = (Sn*Sn - Sn)/2;	// Número de Distancias no Backbone.
  
  // Para cada cluster...
  for ( int k = 0; k < Sn; k++ ) 
  {
    // Acumula o Número de Distancias no Cluster atual.
    NDC += (T[k]*T[k] - T[k])/2;
    
    // Distancias dentro do cluster.
    for (int i = 0; i < T[k] - 1; i++ ) 
    {
      for ( int j = i +1; j < T[k]; j++ ) 
      {
	FitnessDistC += Dist [ cluster[k][i] ][ cluster[k][j] ];
      }//j
    }//i
    
    // Para cada um dos demais clusters...
    for ( int l = k + 1; l < Sn; l++ ) 
    {      
      // Distancias dentro do backbone.
      FitnessDistB += Dist [ cluster[k][0] ][ cluster[l][0] ];
      
      for ( int i = 1; i < T[k]; i++ ) 
      {// Para os não-super-nós do cluster atual...
      
      // Trafego entre os não-super-nos do cluster atual e os super-nos dos demais clusters.
      FitnessTraf += Dem [ cluster[k][i] ][ cluster[l][0] ];
      FitnessTraf += Dem [ cluster[l][0] ][ cluster[k][i] ];
      }
      
      // Para os não-super-nós dos outros clusters ...
      for ( int i = 1; i < T[l]; i++ ) 
      {      
	// Trafego entre o super-no atual e os não-super-nos dos demais clusters.
	FitnessTraf += Dem [ cluster[k][0] ][ cluster[l][i] ];
	FitnessTraf += Dem [ cluster[l][i] ][ cluster[k][0] ];
	
	// Para os não-super-nós do cluster atual...
	for ( int j = 1; j < T[k]; j++ ) 
	{	
	  // Trafego entre os não-super-nós do cluster atual e os os não-super-nós dos outros clusters.
	  FitnessTraf += 2 * Dem [ cluster[k][i] ][ cluster[l][j] ];
	  FitnessTraf += 2 * Dem [ cluster[l][j] ][ cluster[k][i] ];
	  
	}//j
      }//i      
    }//l
  }//k
  
  float totalobjetivo = (FitnessDistB * Pdb + FitnessDistC * Pdc)/(NDB + NDC) + (FitnessTraf * Pt);
  
  cout << FitnessDistB << "\t" << FitnessDistC << "\t" << FitnessTraf << "\t" << totalobjetivo << "\n";
  
  
  return (FitnessDistB * Pdb + FitnessDistC * Pdc)/(NDB + NDC) + (FitnessTraf * Pt);
}// ::Fitness()

// Imprime um resumo da instancia, dentro da construtora.
void hierarquiaGA::WriteResumoGA(char* BIN)
{
  if (CENTER == 0)
  {
    cerr << "\n Instancia nao iniciada!\n";
    return;
  }
  
  WriteResumoH(BIN);
  
  ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".info";
  string dir = oss.str();
  
  ofstream file( dir.c_str(), ofstream::app );
  if ( file.is_open() )
  {
    file << "# " << "Semente do Genético: " << seed << "\n";
    file << "# " << "Tamanho da populacao: " << POP_SIZE << "\n";
    file << "# " << "Numero de populações: " << N_POPULATIONS << "\n";
    file << "# " << "Estagnação Máxima: " << MAX_ESTAG<< "\n";
    file << "# " << "Fator de Calibragem: " << 2*(NTOWNS*NTOWNS - NTOWNS) << "\n";
    file << "\n\n";
    
    file.close();
  }
    
}// ::WriteResumo

// Imprime as informações sobre a solução.
void hierarquiaGA::WriteFitness()
{
  if (NDC == 0) 
  {
    cerr << "\nNão há solução carregada!\n";
    return;
  }
  
  ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".info";
  string dir = oss.str();
  
  ofstream file( dir.c_str(), ofstream::app );
  if ( file.is_open() )
  {
    file << "\nFitnessDistC = " << FitnessDistC << "\t"; // Acumula das distâncias dos clusters.
    file << "FitnessDistB = " << FitnessDistB << "\t"; // Acumula das distâncias do backbone.
    file << "FitnessTraf = " << FitnessTraf << "\n\n"; // Acumula o tráfego.
    
    file << "A = " << (FitnessDistB * Pdb + FitnessDistC * Pdc)/(NDB + NDC) << " = (FitnessDistB * Pdb + FitnessDistC * Pdc)/(NDB + NDC)" << "\n"; // Acumula das distâncias do backbone.
    file << "B = " << FitnessTraf * Pt << " =  FitnessTraf * Pt" << "\n"; // Acumula o tráfego.
    
    file << "\nScore = A + B = " << score << "\t\t";
    file << "Tempo em segundos: " << temposeg << "\n";
    
    file.close();
  }
    
}// ::WriteFitness

// Imprime a sintaxe do programa, se nada for passado em linha de comando.
void hierarquiaGA::WriteSintaxe(char* BIN)
{
  cout << "\n	Formato para os parametros de linha de comando.\n";
  cout << "\n";
  cout << " Usar:\t" << BIN << " N [I] [-g CENTER] [-c file.conf] [-s SEED_NUMBER]\n";
  cout << "\n";
  cout << " NOTACAO:\n";
  cout << " 1 - N			= Numero de nos da rede (obrigatorio);\n";
  cout << " 2 - [I]			= Identificacao da instancia: semente para gerar as matrizes de demandas e distancias (opicional, default: 0);\n";
  cout << " 3 - [-estag MAX_ESTAG]	= Parametro do genetico (opicional, default: 100);\n";
  cout << " 3 - [-popsize POP_SIZE]	= Parametro do genetico (opicional, default: 100);\n";
  cout << " 3 - [-npop N_POPULATIONS]	= Parametro do genetico (opicional, default: 100);\n";
  cout << " 4 - [-c file.conf]		= Arquivo de Configuracao (opicional);\n";
  cout << " 5 - [-s seed SEED_NUMBER]	= Semente para o genetico (opicional, default: time);\n";
  cout << "\n";
}// ::Sintaxe



