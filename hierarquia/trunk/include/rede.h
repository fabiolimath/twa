
/// -------------------------- rede.h --------------------------

#ifndef REDE_H
#define REDE_H

#include "hierarquiaGA.h"

// Defini��es:
#define GLPK_MSGLEV 0	// Nivel de verborragia do glpk.
#define GLPK_PRESOL 1	// Usar ou n�o o presolver.
#define AUX_OUT_FILE "models/out"	// Arquivo auxiliar para a sa�da do GLPK.

#define HmaxMagic_MODEL  "models/labtel-Magic.mod"	// Modelo para calcular o congestionamento.
#define HmaxLBproof_MODEL  "models/labtel-LBproof.mod"	// Modelo para calcular o congestionamento.
#define HmaxLP_API_MODEL  "models/labtel-HmaxLP-API.mod"	// Modelo para calcular o congestionamento.

// Classe que define uma instancia do problema.
class rede : public hierarquiaGA
{
  public:
    double* Magic;
    double** HmaxLB;
    int**   HmaxLBi;
    double** HmaxHLDA;
    double** HmaxRLDA;
    double** HmaxMaxA;
    double** HmaxM;
    double** HmaxD;
    int**   HmaxMn;
    int**   HmaxDn;
    
    /// FunÃ§Ãµes
    
    rede() : hierarquiaGA() {}		// Construtora trivial.
    ~rede ();				// Apaga os arreys alocados dinamicamente.
    
    void Iniciar(int argc, char** argv);
    
    // Cria o data.mod e retorna o nome do arquivo.
    string DataMod(int k, const char* s, double HmaxLB, int gl, int DemOnly);
    
    // Executa o simplex e retorna o valor da função objetivo.
    double Simplex(const char* MODEL,const  char* DATA);
    
    // Executa o HLDA e retorna o valor do congestionamento.
    double HLDA(const char* DATA, int gl, int k);
    
    // Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
    void Statistica(const char* DATA, int gl, int k);
    
    // Determina o LB a partir do LBP.
    void LBproof(double LBP, int gl, int k, const char* s);
    
    // Chama o HLDA o RLDA e estima as médias.
    void allfiles();
    
    int GLmax(int T) {return ((int)(T/2));}
    
    double round(double X, int p) {return floor(X*pow((double)10,(double)p))/pow((double)10,(double)p);}
    
    
};// class instancia


#endif
