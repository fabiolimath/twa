
/// -------------------------- hierarquia.h --------------------------

#ifndef HIERARQUIA_H
#define HIERARQUIA_H

#include "instancia.h"

#define CALIBRAGEM 1000*5	// Valor de Calibragem para que o tráfego e as distâncias tenham a mesma ordem de grandeza
#define MinC 3			// Mínimo de super-nós.

// Classe que define uma instancia do problema.
class hierarquia : public instancia
{
  public:
    
    /// Hierarquia
    int Mi; 		// Mínimo de nó no backbone, definido no cabeçalho deste arquivo.
    int Ma; 		// Máximo de nós no backbone (NTOWNS/Mi).
    
    int Pd;		// Peso das distâncias (sem distinção entre clusters e backbone).
    int Pdc;		// Peso das distâncias dos clusters na função objetivo.
    int Pdb;		// Peso das distâncias do backbone na função objetivo.
    int Pt; 		// Peso do tráfego na função objetivo.
    
    int Sn;		// Número de super-nos.
    int *T;		// Vetor de tamanhos da solução corrente.
    int **cluster;	// Matriz que receberá os clusters, um em cada linha
    float ***demS;	// Vetor das matrizes de demanda, Separadas, para os clusters e o backbone.
    float ***distS;	// Vetor das matrizes de distancias, Separadas, para os clusters e o backbone.
    
    /// Funções
    
    hierarquia () : instancia () 
    {Ma = 0; Sn = 0;}				// Construtora trivial.
    void IniciaH (int argc, char** argv);	// Inicia as variáveis.
    ~hierarquia ();				// Apaga os arreys alocados dinamicamente.
        
    void SeparaMatrizes ();			// Separa as matrizes de demanda e distancia de cada cluster e do backbone.
    
    void WriteResumoH(char* BIN);		// Imprime um resumo sobre o problema.
    void WriteTamanhos();			// Imprime o vetor de tamanhos.
    void WriteClusters();			// Imprime os clusters
    
};// class instancia

#endif
