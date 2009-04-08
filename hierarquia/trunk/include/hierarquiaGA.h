
/// -------------------------- hierarquiaGA.h --------------------------

#ifndef HIERARQUIAGA_H
#define HIERARQUIAGA_H

#include "hierarquia.h"

// Classe que define uma instancia do problema.
class hierarquiaGA : public hierarquia
{
  public:
    
    /// Arranjo para a hierarquia dada pelo GA.
    // Informações sobre a solução.
    float score;	// Fitness da solução corrente.
    double temposeg;	// Tempo de execução de genético.
    
    float FitnessDistC;	// Acumula das distâncias dos clusters.
    float FitnessDistB;	// Acumula das distâncias do backbone.
    float FitnessTraf;	// Acumula o tráfego.
    int NDC;		// Número de Distancias total dos Clusters.
    int NDB;		// Número de Distancias no Backbone.
    
    // Parâmetros do genético;    
    // Um mesmo valor (CENTER) para o número de gerações (critério de parada),
    // o número de populações paralelas  e o tamanho das populações. 
    // Ou seja, serão visitadas CENTER³ soluções.  
    int CENTER;
    
    unsigned int seed; // Semente para o genético; Se não for setada, a hora corrente será usada como semente.
    
    int N_POPULATIONS;	// Número de populações paralelas.
    int POP_SIZE;	// Tamanho das populações.
    int N_GENERATIONS;	// Número de gerações (critério de parada)
    int GEN_SIZE;	// Tamanho do Cromossomo (NTOWNS+Ma);
    int MAX_TOWNS;	// Igual ao Tamanho do Cromossomo.
    
    GAListGenome<int> best;	// Genoma da melhor solução.
    
    /// Funções
    
    hierarquiaGA() : hierarquia() 
    {CENTER = 0; NDC = 0;}			// Construtora trivial.
    ~hierarquiaGA(){};				// Apaga os arreys alocados dinamicamente.
    
    void IniciaGA (int argc, char** argv);	// Inicia as vari�veis, gera as matrizes e seta a semente do gen�tico.
    int   Evolve (int argc, char** argv);	// Executa o genético, guarda o melhor indivíduo e o tempo de execução.
    float Solucao (GAListGenome<int> & gen);	// Decodifica o cromossomo e devolve o Fitness.
    float Fitness ();				// Calcula o Fitness, dentro de "solucao()".
   
    void WriteResumoGA (char*);			// Imprime um resumo da instancia.
    void WriteFitness();			// Imprime as informações sobre a solução.
    void WriteSintaxe(char* BIN);		// Imprime a sintaxe do programa, se nada for passado em linha de comando.
    
};// class instancia

#endif
