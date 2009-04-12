
/// -------------------------- instancia.h --------------------------

#ifndef INSTANCIA_H
#define INSTANCIA_H

// Classe que define uma instancia do problema.
class instancia 
{
  public:
    
    /// Caracteriza��o da Inst�ncia.
    int NTOWNS;		// N�mero de n�s da rede.
    int Inst;		// Identifica��o da Inst�ncia, usada como semente para a gera��o das matrizes.
    
    float low;		// Limite Inferior para a gera��o das matrizes, definido no cabe�alho deste arquivo.
    float high;		// Limite Superior para a gera��o das matrizes, definido no cabe�alho deste arquivo.
    
    float **Dem;	// Matriz de demandas que ser� gerada.
    float **Dist;	// Matriz de dist�ncias que ser� gerada.
    
    /// Fun��es
    
    instancia () {NTOWNS = 0;}	// Construtora trivial.
    void IniciaI (int argc, char** argv);	// Inicia as vari�veis, gera as matrizes e seta a semente do gen�tico.
    void GeraMatrizes ();	// Gera as matrizes de demanda e distancia, dentro da construtora.
    virtual ~instancia ();	// Apaga os arreys alocados dinamicamente.
    void WriteResumoI (char*);	// Imprime um resumo da instancia.
    
};// class instancia

#endif
