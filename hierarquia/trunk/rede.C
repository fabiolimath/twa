
#include "include/cabecalho.h"
#include "include/rede.h"

// Inicia as variáveis.
void rede::Iniciar(int argc, char** argv)
{
  if (NDC == 0) Evolve(argc,argv);

  Magic = (double*) calloc (Sn+1, sizeof(double));	// ;
  HmaxLB = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxLBi = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  HmaxHLDA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxRLDA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxMaxA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxM = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxD = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxMn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  HmaxDn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
}// ::Inicia

// Libera a memória dos vetores alocados dinamicamente.
rede::~rede()
{
  free(Magic);
  HmaxLB = del_matrix_double(Sn+1,GLmax(Ma),HmaxLB );	// ;
  HmaxLBi = del_matrix_int(Sn+1,GLmax(Ma), HmaxLBi);	// ;
  HmaxHLDA = del_matrix_double(Sn+1,GLmax(Ma), HmaxHLDA);	// ;
  HmaxRLDA = del_matrix_double(Sn+1,GLmax(Ma), HmaxRLDA);	// ;
  HmaxMaxA = del_matrix_double(Sn+1,GLmax(Ma), HmaxMaxA);	// ;
  HmaxM = del_matrix_double(Sn+1,GLmax(Ma), HmaxM);	// ;
  HmaxD = del_matrix_double(Sn+1,GLmax(Ma), HmaxD);	// ;
  HmaxMn = del_matrix_int(Sn+1,GLmax(Ma), HmaxMn);	// ;
  HmaxDn = del_matrix_int(Sn+1,GLmax(Ma), HmaxDn);	// ;
}// ::~rede()

// Executa o simplex e retorna o valor da função objetivo.
double rede::Simplex(const char* MODEL,const  char* DATA)
{
  LPX *LP = lpx_read_model(MODEL, DATA, AUX_OUT_FILE );		// Inicia o modelo.
  lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
  lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
  // 	cout << "LP criado." << "\n";

  if(lpx_simplex(LP)!=200) return printf("Simplex: ERRO!\n");	// Executa o simplex.
    //cout << "\nSimplex out - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
  return lpx_get_obj_val(LP);
}// ::Simplex()

// Executa o HLDA e retorna o valor do congestionamento.
double rede::HLDA(const char* DATA, int gl, int k)
{
  tmatrix m = makeMatrix(T[k], T[k]);
  fill(m, 0);

  tmatrix d = makeMatrix(T[k], T[k]);
  fill(d, 0);

  for(int i=0; i<T[k]-1; i++)
  {
    for(int j=i+1; j<T[k];j++)
    {
      setData(d, i, j, demS[k][i][j]);
      setData(d, j, i, demS[k][j][i]);
    }//j
  }//i

  m = hlda(m, d, gl);

  const char* MODEL = HmaxLP_API_MODEL;
  //sprintf(MODEL, HmaxLP_MODEL);
  return Simplex(MODEL,DATA);
}// ::HLDA

#include "datamod.C"

// Determina o LB a partir do LBP.
void rede::LBproof(double LBP, int gl, int k, const char* s = "backbone")
{
  double proof;
  int i = 0;
  LPX *LP;
  
  do
    {
      const char* MODEL = HmaxLBproof_MODEL;
      //sprintf(MODEL, HmaxLBproof_MODEL);
      string DATA = DataMod(k,s,LBP*(1 - ((double)i)/200),gl);
      
      LP = lpx_read_model(MODEL, DATA.c_str(), AUX_OUT_FILE );		// Inicia o modelo.
      lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
      lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
      // 	cout << "LP criado." << "\n";
      
      if(lpx_simplex(LP)!=200) printf("Simplex: ERRO!\n");	// Executa o simplex.
	//cout << "\nSimplex out - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
      
      proof = lpx_get_obj_val(LP);
      
      //cout << "\n Proof out - LBP = " << LBP*(1 - ((double)i)/200) << "  - LB = " << proof << " - iterações = " << i+2 << "\n\n";
      if (proof > LBP*(1 - ((double)i)/100))
	{
	  string MPS_FILE = DATA;
	  string sulfixo(".mps");
	  MPS_FILE += sulfixo;
	  glp_write_mps(LP, GLP_MPS_FILE , NULL, MPS_FILE.c_str() );

	  HmaxLB[k][gl] = proof;
	  HmaxLBi[k][gl] = i+2;
	  return;
	}
      i++;
    } while(1);
}// ::LBproof

#define ALFA 0.05	// CONFIANCA = 1 - ALFA.
#define ERRO 0.05		// Margem de erro para as estatísticas.
#define Max_Amostra 10000	// Tamanho máximo da amostra.
#define Min_Amostra 30

#include "statistic.C"

#include "allfiles.C"















