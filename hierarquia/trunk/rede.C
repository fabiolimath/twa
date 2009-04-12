
#include "include/cabecalho.h"
#include "include/rede.h"

// Definições:
int GLPK_MSGLEV = 0;	// Nivel de verborragia do glpk.
int GLPK_PRESOL = 1;	// Usar ou não o presolver.
string AUX_OUT_FILE = "models/out";	// Arquivo auxiliar para a saída do GLPK.

string HmaxMagic_MODEL = "models/labtel-Magic.mod";	// Modelo para calcular o congestionamento.
string HmaxLBproof_MODEL = "models/labtel-LBproof.mod";	// Modelo para calcular o congestionamento.
string HmaxLP_API_MODEL = "models/labtel-HmaxLP-API.mod";	// Modelo para calcular o congestionamento.

float ALFA = 0.05;	// CONFIANCA = 1 - ALFA.
float ERRO = 0.05;		// Margem de erro para as estatísticas.
unsigned long Max_Amostra = 10000;	// Tamanho máximo da amostra.
float Min_Amostra = 30;
int PLB_PRECISION = 2;

// Inicia as variáveis.
void rede::Iniciar(int argc, char** argv)
{
  if (NDC == 0) Evolve(argc,argv);
  
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
	    if ( buffer == "PLB_PRECISION") 
	    {
	      in >> PLB_PRECISION;
	      getline(in, buffer);
	      file << "\n Lido: PLB_PRECISION= " << PLB_PRECISION << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "Min_Amostra") 
	    {
	      in >> Min_Amostra;
	      getline(in, buffer);
	      file << "\n Lido: Min_Amostra= " << Min_Amostra << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "Max_Amostra") 
	    {
	      in >> Max_Amostra;
	      getline(in, buffer);
	      file << "\n Lido: Max_Amostra= " << Max_Amostra << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "ERRO") 
	    {
	      in >> ERRO;
	      getline(in, buffer);
	      file << "\n Lido: ERRO= " << ERRO << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "ALFA") 
	    {
	      in >> ALFA;
	      getline(in, buffer);
	      file << "\n Lido: ALFA= " << ALFA << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "GLPK_MSGLEV") 
	    {
	      in >> GLPK_MSGLEV;
	      getline(in, buffer);
	      file << "\n Lido: GLPK_MSGLEV= " << GLPK_MSGLEV << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "GLPK_PRESOL") 
	    {
	      in >> GLPK_PRESOL;
	      getline(in, buffer);
	      file << "\n Lido: GLPK_PRESOL= " << GLPK_PRESOL << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "AUX_OUT_FILE") 
	    {
	      in >> AUX_OUT_FILE;
	      getline(in, buffer);
	      file << "\n Lido: AUX_OUT_FILE= " << AUX_OUT_FILE << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "HmaxMagic_MODEL")
	    {
	      in >> HmaxMagic_MODEL;
	      getline(in, buffer);
	      file << "\n Lido: HmaxMagic_MODEL= " << HmaxMagic_MODEL << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "HmaxLBproof_MODEL") 
	    {
	      in >> HmaxLBproof_MODEL;
	      getline(in, buffer);
	      file << "\n Lido: HmaxLBproof_MODEL= " << HmaxLBproof_MODEL << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    if ( buffer == "HmaxLP_API_MODEL") 
	    {
	      in >> HmaxLP_API_MODEL;
	      getline(in, buffer);
	      file << "\n Lido: HmaxLP_API_MODEL= " << HmaxLP_API_MODEL << ", Comentário: " << buffer;
	      continue;
	    }
	    
	    file.close();
	  }
	}
      } while(!in.eof());
    }
  }
  
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
  Hmax = new_cube_double(Sn+1,GLmax(Ma),Max_Amostra);	// ;
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
  Hmax = del_cube_double(Sn+1,GLmax(Ma),Max_Amostra, Hmax);	// ;
}// ::~rede()

// Executa o simplex e retorna o valor da função objetivo.
double rede::Simplex(string MODEL,const  char* DATA)
{
  const char* dump = MODEL.c_str();
  const char* dump2 = AUX_OUT_FILE.c_str();
  LPX *LP = lpx_read_model(dump, DATA, dump2 );		// Inicia o modelo.
  lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
  lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
  // 	cout << "LP criado." << "\n";

  if(lpx_simplex(LP)!=200) return printf("Simplex: ERRO!\n");	// Executa o simplex.
    //cout << "\nSimplex out - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
    
  double obj = lpx_get_obj_val(LP);
  lpx_delete_prob(LP);
  string buffer = "rm -f out " + AUX_OUT_FILE;
  system(buffer.c_str());
  
  return obj;
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

  string MODEL = HmaxLP_API_MODEL;
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
  const char* dump = HmaxLBproof_MODEL.c_str();
  const char* dump2 = AUX_OUT_FILE.c_str();
  
  do
    {
      string DATA = DataMod(k,s,LBP*(1 - ((double)i)/200),gl);
      
      LP = lpx_read_model(dump, DATA.c_str(), dump2 );		// Inicia o modelo.
      lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
      lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
      // 	cout << "LP criado." << "\n";
      
      if(lpx_simplex(LP)!=200) printf("Simplex: ERRO!\n");	// Executa o simplex.
	//cout << "\nSimplex out - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
      
      proof = lpx_get_obj_val(LP);
      
      //cout << "\n Proof out - LBP = " << LBP*(1 - ((double)i)/200) << "  - LB = " << proof << " - iterações = " << i+2 << "\n\n";
      if (proof > LBP*(1 - ((double)i)/100))
	{
// 	  string MPS_FILE = DATA;
// 	  string sulfixo(".mps");
// 	  MPS_FILE += sulfixo;
// 	  glp_write_mps(LP, GLP_MPS_FILE , NULL, MPS_FILE.c_str() );

	  HmaxLB[k][gl] = proof;
	  HmaxLBi[k][gl] = i+2;
	  return;
	}
      i++;
    } while(1);
    
    lpx_delete_prob(LP);
    string buffer = "rm -f out " + AUX_OUT_FILE;
    system(buffer.c_str());
    
}// ::LBproof

#include "statistic.C"

#include "allfiles.C"















