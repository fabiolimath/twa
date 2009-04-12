
#include "include/cabecalho.h"
#include "include/hierarquia.h"

#define default_CALIBRAGEM 5000	// Valor de Calibragem para que o tráfego e as distâncias tenham a mesma ordem de grandeza
#define default_MinC 3			// Mínimo de super-nós.
#define default_Pd 1
#define default_Pt 1

// Class hierarquia - Classe que define uma hierarquia para o problema e conterá as matrizes de demanda e distancia separadas por sub rede.

// Inicia as variáveis.
void hierarquia::IniciaH (int argc, char** argv)
{
  if (NTOWNS == 0) IniciaI(argc,argv);
  
  /// Leitura dos parâmetros de linha de comando:
  
  double calibre = default_CALIBRAGEM;
  Pd = default_Pd;
  Pt = default_Pt;
  Mi = default_MinC;
  
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
	    if ( buffer == "CALIBRAGEM") 
	    {
	      in >> calibre;
	      getline(in, buffer);
	      cout << "\n Lido: CALIBRAGEM= " << calibre << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "Pd") 
	    {
	      in >> Pd;
	      getline(in, buffer);
	      cout << "\n Lido: Pd= " << Pd << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "Pt") 
	    {
	      in >> Pt;
	      getline(in, buffer);
	      cout << "\n Lido: Pt= " << Pt << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "MinC") 
	    {
	      in >> Mi;
	      getline(in, buffer);
	      cout << "\n Lido: MinC,= " << Mi << " Comentário: " << buffer;
	      continue;
	    }
	    
	  }
      } while(!in.eof());
    }
  }
  
  Pdb = calibre*Pd;			// Peso das distâncias do backbone na função objetivo.
  Pdc = Pdb;				// Peso das distâncias dos clusters na função objetivo.  
  Ma = (int)(NTOWNS/Mi);		// Máximo de nós no backbone (NTOWNS/Mi).
  
  Sn = 0;					// Número de super-nos
  T = (int*) calloc (Ma+2, sizeof(int));	// Vetor de tamanhos
  cluster = new_matrix_int (Ma + 1, Ma + 1 );		// Matriz que receberá os clusters, um em cada linha
  demS = new_cube_float (Ma + 1, Ma, Ma);	// Matrizes de demanda, Separadas, para os clusters e o backbone.
  distS = new_cube_float (Ma + 1, Ma, Ma);	// Matrizes de distancias, Separadas, para os clusters e o backbone.
  
}// ::Inicia

// Separa as matrizes de demanda e distancia de cada cluster e do backbone.
void hierarquia::SeparaMatrizes ()
{
  if (Ma == 0)
  {
    cout << "\n Instancia nao iniciada!\n";
    return;
  }
  
  if (Sn == 0) 
    {
      cout << "\nNão há solução carregada!\n";
      return;
    }
  
   /// ///////////////////////////////////////////////////////////////////////////////////////////////
  /// Separação das matrizes de demandas dos clusters e do backbone.

  //cout << "\nSeparando as matrizes das sub redes...\t";

  // Seta as entradas originais das matrizes de demandas e distancias...
  
  // Nos clusters...
  for (int k = 0; k < Sn; k++ )
  {
    for (int i = 0; i < T[k] - 1; i++ ) 
    {
      // diagonal...
      demS[k][i][i] = 0; 
      distS[k][i][i] = 0;
      
      for ( int j = i +1; j < T[k]; j++ ) 
      {// Pastes superior e inferior...
      demS[k][i][j] = Dem[ cluster[k][i] ][ cluster[k][j] ];
      demS[k][j][i] = Dem[ cluster[k][j] ][ cluster[k][i] ];

      distS[k][i][j] = Dist[ cluster[k][i] ][ cluster[k][j] ];
      distS[k][j][i] = Dist[ cluster[k][j] ][ cluster[k][i] ];
      }//j
    }//i
    // Último elemento na diagonal.
    demS[k][T[k] - 1][T[k] - 1] = 0;
    distS[k][T[k] - 1][T[k] - 1] = 0;
  }//k
      
  // No Backbone...
  for (int i = 0; i < Sn-1; i++ )
  {
    // diagonal...
    demS[Sn][i][i] = 0;
    distS[Sn][i][i] = 0;
    
    for ( int j = i +1; j < Sn; j++ ) 
    {// Pastes superior e inferior...
    demS[Sn][i][j] = Dem[ cluster[i][0] ][ cluster[j][0] ];
    demS[Sn][j][i] = Dem[ cluster[j][0] ][ cluster[i][0] ];

    distS[Sn][i][j] = Dem[ cluster[i][0] ][ cluster[j][0] ];
    distS[Sn][j][i] = Dem[ cluster[j][0] ][ cluster[i][0] ];
    }//j
  }//i
  // Último elemento na diagonal.
  demS[Sn][Sn - 1][Sn - 1] = 0;
  distS[Sn][Sn - 1][Sn - 1] = 0;
  
 // cout << "Agregando o trafego nas sub redes...\t";
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // Acumula as entradas dos super-nos nas matrizes de demandas...
  
  for ( int k = 0; k < Sn - 1; k++ ) 
  {// Para cada cluster...
    for ( int l = k + 1; l < Sn; l++ ) 
    {// Para cada um dos demais clusters...      
      for ( int i = 1; i < T[k]; i++ ) 
      {// Para os não-super-nós do cluster atual...
      
	// Trafego entre os não-super-nos do cluster atual e os super-nos dos demais clusters.
	 demS[k][i][0] += Dem [ cluster[k][i] ][ cluster[l][0] ];
	demS[Sn][k][l] += Dem [ cluster[k][i] ][ cluster[l][0] ];
	
	 demS[k][0][i] += Dem [ cluster[l][0] ][ cluster[k][i] ];
	demS[Sn][l][k] += Dem [ cluster[l][0] ][ cluster[k][i] ];
      }
	
      for ( int i = 1; i < T[l]; i++ ) 
      {// Para os não-super-nós dos outros clusters ...
      
	// Trafego entre o super-no atual e os não-super-nos dos demais clusters.
	 demS[l][i][0] += Dem [ cluster[l][i] ][ cluster[k][0] ];
	demS[Sn][l][k] += Dem [ cluster[l][i] ][ cluster[k][0] ];

	 demS[l][0][i] += Dem [ cluster[k][0] ][ cluster[l][i] ];
	demS[Sn][k][l] += Dem [ cluster[k][0] ][ cluster[l][i] ];
	
	for ( int j = 1; j < T[k]; j++ ) 
	{// Para os não-super-nós do cluster atual...
	
	  // Trafego entre os não-super-nós do cluster atual e os os não-super-nós dos outros clusters.
	   demS[k][j][0] += Dem [ cluster[k][j] ][ cluster[l][i] ];
	  demS[Sn][k][l] += Dem [ cluster[k][j] ][ cluster[l][i] ];
	   demS[l][0][i] += Dem [ cluster[k][j] ][ cluster[l][i] ];

	   demS[l][i][0] += Dem [ cluster[l][i] ][ cluster[k][j] ];
	  demS[Sn][l][k] += Dem [ cluster[l][i] ][ cluster[k][j] ];
	   demS[k][0][j] += Dem [ cluster[l][i] ][ cluster[k][j] ];
	}//j
      }//i      
    }//l
  }//k
  //cout << "\nMatrizes das sub redes separadas com sucesso!...\n";
}// ::SeparaMatrizes ()

// Apaga os arreys alocados dinamicamente.
hierarquia::~hierarquia ()
{
  if (NTOWNS!=0)
  {
    cluster = del_matrix_int (Ma , Ma, cluster);		// Clusters.
    free(T);						// Tamanhos.
    demS = del_cube_float (Sn + 1, Ma, Ma, demS);		// Matrizes de demanda Separadas.
    distS = del_cube_float (Sn + 1, Ma, Ma, distS);	// Matrizes de distancias Separadas.
  }
}// ~hierarquia

// Imprime um resumo da instancia, dentro da construtora.
void hierarquia::WriteResumoH(char* BIN)
{
  if (Ma == 0)
  {
    cout << "\n Instancia nao iniciada!\n";
    return;
  }
  
  WriteResumoI(BIN);
  
  cout << "# " << "Peso das distancias: " << Pd << "\n";
  cout << "# " << "Peso do trafego na funcao objetivo: " << Pt << "\n";
  cout << "# " << "Minimo de nos no backbone: " << Mi << "\n";
  
}// ::WriteResumo

// Imprime o vetor de tamanhos.
void hierarquia::WriteTamanhos()
{
  if (Sn == 0) 
  {
    cout << "\nNão há solução carregada!\n";
    return;
  }
  
  cout << "Tamanhos: ";
  for (int i=0;i<Sn;i++) cout << T[i] << " ";
  cout << "\n";
  
}// ::WriteTamanhos

// Imprime os clusters.
void hierarquia::WriteClusters()
{
  if (Sn == 0) 
  {
    cout << "\nNão há solução carregada!\n";
    return;
  }
  
  cout << "\n Clusters:\n";
  for (int i=0;i<Sn;i++) 
  {
    cout << i+1 << " :";
    for(int j=0;j<T[i];j++)
    {
      cout << cluster[i][j] << " ";
    }
    cout << "\n";
  }
}// ::WriteClusters



