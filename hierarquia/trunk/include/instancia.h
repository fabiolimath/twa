
/// -------------------------- instancia.h --------------------------

#ifndef INSTANCIA_H
#define INSTANCIA_H

// Classe que define uma instancia do problema.
class instancia 
{
  public:
    
    /// Caracterização da Instância.
    int NTOWNS;		// Número de nós da rede.
    int Inst;		// Identificação da Instância, usada como semente para a geração das matrizes.
    
    float low;		// Limite Inferior para a geração das matrizes, definido no cabeçalho deste arquivo.
    float high;		// Limite Superior para a geração das matrizes, definido no cabeçalho deste arquivo.
    
    float **Dem;	// Matriz de demandas que será gerada.
    float **Dist;	// Matriz de distâncias que será gerada.
    
    /// Funções
    
    instancia () {NTOWNS = 0;}	// Construtora trivial.
    void IniciaI (int argc, char** argv);	// Inicia as variáveis, gera as matrizes e seta a semente do genético.
    void GeraMatrizes ();	// Gera as matrizes de demanda e distancia, dentro da construtora.
    virtual ~instancia ();	// Apaga os arreys alocados dinamicamente.
    void WriteResumoI (char*);	// Imprime um resumo da instancia.
    
};// class instancia

#endif
