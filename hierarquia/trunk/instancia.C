
#include "include/cabecalho.h"
#include "include/instancia.h"

// Definições:
#define LIM_low 0		// Limite Inferior para a geração das matrizes.
#define LIM_high 100		// Limite Superior para a geração das matrizes.

// Class instancia - Classe que define uma instancia do problema e conterá as matrizes de demanda e distancia.

// Inicia as variáveis, gera as matrizes e seta a semente do genético.
void instancia::IniciaI (int argc, char** argv)
{
  /// Leitura dos parâmetros de linha de comando:
  NTOWNS    = atoi ( argv [ 1 ] ) ;	// Matriz de entrada;
  Inst  = atoi ( argv [ 2 ] ) ;		// Matriz de distancias;

  Dem = new_matrix_float (NTOWNS, NTOWNS);	// Matriz de demandas que será gerada.
  Dist = new_matrix_float (NTOWNS, NTOWNS);	// Matriz de distâncias que será gerada.
  low = LIM_low;	// Limite Inferior para a geração das matrizes
  high = LIM_high;	// Limite Superior para a geração das matrizes
  
  GeraMatrizes();	// Gera as matrizes de demanda e distancia.
  
}// ::Inicia

// Gera as matrizes de demanda e distancia, dentro da construtora.
void instancia::GeraMatrizes ()
{
  if (NTOWNS == 0)
    {
      cout << "\n Instancia nao iniciada!\n";
      return;
    }
  
  // Seta a semente para gerar a instancia.
  GARandomSeed(Inst);
  
  // Coordenadas X e Y dos nós da rede.
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
  
//   cout << "\nmatriz de distâncias:\n";
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
    cout << "\n Instancia nao iniciada!\n";
    return;
  }
  
  cout << "\n";
  
  cout << "# " << "Binario utilizado: " << BIN << "\n";
  cout << "# " << "Instancia: " << Inst << "\n";
  cout << "# " << "Numero de nos: " << NTOWNS << "\n";
  
}// ::WriteResumo


