
#include "include/cabecalho.h"
#include "include/instancia.h"

// Defini��es:
#define default_Inst 0
#define default_LIM_low 0		// Limite Inferior para a gera��o das matrizes.
#define default_LIM_high 100		// Limite Superior para a gera��o das matrizes.

// Class instancia - Classe que define uma instancia do problema e conter� as matrizes de demanda e distancia.

// Inicia as vari�veis, gera as matrizes e seta a semente do gen�tico.
void instancia::IniciaI (int argc, char** argv)
{
  /// Leitura dos par�metros de linha de comando:
  
  if( argc > 2 )
  {
    Inst = atoi ( argv [ 2 ] ) ;	// Matriz de entrada;
  }
  else
  {
    Inst = default_Inst;
  }
  
  NTOWNS = atoi ( argv [ 1 ] ) ;	// Matriz de entrada;
  Dem = new_matrix_float (NTOWNS, NTOWNS);	// Matriz de demandas que ser� gerada.
  Dist = new_matrix_float (NTOWNS, NTOWNS);	// Matriz de dist�ncias que ser� gerada.
  
  GARandomSeed(time((time_t *)NULL));	// Semante default para o genetico.
  
  seed = 0; // Default SEED_NUMBER
  for(int ii=1; ii<argc;) 
  {
    if(strcmp(argv[ii++],"-s") == 0) 
    { // Verifica se uma seed foi fornecida e a seta.
    seed = atoi(argv[ii]);
    GARandomSeed(seed);
    }      
  }
  
  ostringstream oss;
  oss << "rm -rf data/N" << NTOWNS << ".I" << Inst << ".s" << seed;
  string dir = oss.str();
  system( dir.c_str() );
  
  ostringstream oss2;
  oss2 << "mkdir -p data/N" << NTOWNS << ".I" << Inst << ".s" << seed;
  dir = oss2.str();
  system( dir.c_str() );
  
//   WriteResumoI( argv [ 0 ] );	// Imprime um resumo da instancia.
  
  low = default_LIM_low;	// Limite Inferior para a gera��o das matrizes
  high = default_LIM_high;	// Limite Superior para a gera��o das matrizes
  
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
	      if ( buffer == "LIM_low")
	      {
		in >> low;
		getline(in, buffer);
		file << "\n Lido: LIM_low= " << low << ", Comentário: " << buffer;
		continue;
	      }
	      
	      if ( buffer == "LIM_high") 
	      {
		in >> high;
		getline(in, buffer);
		file << "\n Lido: LIM_high= " << high << ", Comentário: " << buffer;
		continue;
	      }
	      
	      file.close();
	    }
	  }
      } while(!in.eof());
    }
  }
  
  GeraMatrizes();	// Gera as matrizes de demanda e distancia.
  
}// ::Inicia

// Gera as matrizes de demanda e distancia, dentro da construtora.
void instancia::GeraMatrizes ()
{
  if (NTOWNS == 0)
    {
      cerr << "\n Instancia nao iniciada!\n";
      return;
    }
  
  // Seta a semente para gerar a instancia.
  GARandomSeed(Inst);
  
  // Coordenadas X e Y dos n�s da rede.
  float **Coord = new_matrix_float (NTOWNS, 2);
  //cout << "\n Low : " << low;
  //cout << "\n high : " << high;
  // Gera as coordenadas.
  for(int i = 0; i < NTOWNS; i++) 
  {
    Coord[i][0] = GARandomFloat(low,high);
    Coord[i][1] = GARandomFloat(low,high);
    //cout << Coord[i][0] << " " << Coord[i][1] << " - ";
  }
  
  // Calcula as distancias e gera as demandas de trafego.
  for(int i=0; i < NTOWNS-1; i++)
  {
    Dist[i][i] = 0;
    Dem[i][i] = 0;
    
    for(int j=1+1; j< NTOWNS; j++)
    {
      float aux = sqrt( (Coord[i][0] - Coord[j][0])*(Coord[i][0] - Coord[j][0]) + (Coord[i][1] - Coord[j][1])*(Coord[i][1] - Coord[j][1]) );
      Dist[i][j] = aux;
      Dist[j][i] = aux;
      
      Dem[i][j] = GARandomFloat(low,high);
      Dem[j][i] = GARandomFloat(low,high);
      
    }
    // 	  cout << "\n";
  }
  Dist[NTOWNS-1][NTOWNS-1] = 0;
  Dem[NTOWNS-1][NTOWNS-1] = 0;
  
  Coord = del_matrix_float (NTOWNS, 2, Coord);
  
//   cout << "\nmatriz de dist�ncias:\n";
//   for(int i = 0;i<NTOWNS;i++)
//     {for(int j = 0 ; j< NTOWNS; j++)
//       cout << " " << Dist[i][j];
//     cout << "\n";}
//   
//   cout << "\nmatriz de demandas:\n";
//   for(int i = 0;i<NTOWNS;i++)
//     {for(int j = 0 ; j< NTOWNS; j++)
//       cout << " " << Dem[i][j];
//     cout << "\n";}
    
}// ::GeraMatrizes()

// Apaga os arreys alocados dinamicamente.
instancia::~instancia ()
{
  if (NTOWNS!=0)
    {
      Dem = del_matrix_float (NTOWNS, NTOWNS, Dem);		// Matriz de demandas.
      Dist = del_matrix_float (NTOWNS, NTOWNS, Dist);	// Matriz de distancias.

    }
}// ~instancia

// Imprime um resumo da instancia, dentro da construtora.
void instancia::WriteResumoI(char* BIN)
{
  if (NTOWNS == 0)
  {
    cerr << "\n Instancia nao iniciada!\n";
    return;
  }
  
  ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".info";
  string dir = oss.str();
  
  ofstream file( dir.c_str(), ofstream::app );
  if ( file.is_open() )
  {
    file << "\n\n";
    file << "# " << "Binario utilizado: " << BIN << "\n";
    file << "# " << "Instancia: " << Inst << "\n";
    file << "# " << "Numero de nos: " << NTOWNS << "\n";
    
    file.close();
  }
  
}// ::WriteResumo


