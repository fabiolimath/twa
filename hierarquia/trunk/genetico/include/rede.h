
/// -------------------------- rede.h --------------------------

#ifndef REDE_H
#define REDE_H

#include "hierarquiaGA.h"

// Classe que define uma instancia do problema.
class rede : public hierarquiaGA
{
  public:
/*    double** HmaxLB;
    double** HmaxHLDA;
    double** HmaxRLDA;
    double** HmaxMaxA;
    double** HmaxM;
    double** HmaxD;
    double** TimeS;
	 int**   HmaxMn;
	 int**   HmaxDn;
	 double*** Hmax;
	 int**   FTnetMn;
	 int**   FTnetDn;
	 double*** FTnet;
	 double** FTnetRLDA;
	 double** FTnetMaxA;
	 double** FTnetM;
	 double** FTnetD;
	 double** FTnetLB;
	 double** TimeSFTnet;*/
	 
    /// FunÃ§Ãµes
    
    rede() : hierarquiaGA() {}		// Construtora trivial.
    ~rede (){};				// Apaga os arreys alocados dinamicamente.
    
    void Iniciar(int argc, char** argv);
    
    // Cria o data.mod e retorna o nome do arquivo.
   string DataMod(int k, int gl, const char* s, double HmaxLB, double FTnetLB, int W, double HmaxM, double FTnetM);
    
/*    // Executa o simplex e retorna o valor da função objetivo.
    double Simplex(string MODEL,const  char* DATA);
    
    // Executa o HLDA e retorna o valor do congestionamento.
    double HLDA(const  char* DATA, int gl, int k);
	 
	 // Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
	 void Statistica(const char* DATA, int gl, int k);
	 
	 // Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
	 void StatisticaFTnet(const char* DATA, int gl, int k);
	 
    // Determina o LB a partir do LBP.
    void LBproof(double LBP, int gl, int k, const char* s);*/
    
    // Chama o HLDA o RLDA e estima as médias.
    void allfiles(int argc, char** argv);
    
    int GLmax(int T) {return ((int)(T/2));}
    
/*    double round(double X, int p) {return floor(X*pow((double)10,(double)p))/pow((double)10,(double)p);}
	 
	 float MTB(int k,  int gl);
	 float FTB(int k,  int gl);*/
    
};// class instancia


#endif