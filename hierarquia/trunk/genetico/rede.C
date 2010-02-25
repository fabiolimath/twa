
#include "include/cabecalho.h"
#include "include/rede.h"

// Definições:
// int GLPK_MSGLEV = 0;	// Nivel de verborragia do glpk.
// int GLPK_PRESOL = 1;	// Usar ou não o presolver.
// int GLPK_TERM_OUT = 0;	// Saída de terminal, sim (1) ou não (0) ?
// string AUX_OUT_FILE = "models/out";	// Arquivo auxiliar para a saída do GLPK.
// 
// string HmaxMagic_MODEL = "models/labtel-Magic.mod";	// Modelo para calcular o congestionamento.
// string HmaxLBproof_MODEL = "models/labtel-LBproof.mod";	// Modelo para calcular o congestionamento.
// string HmaxLP_API_MODEL = "models/labtel-HmaxLP-API.mod";	// Modelo para calcular o congestionamento.
// string HmaxLP_API_FTnet_MODEL = "models/labtel-HmaxLP-FTnet-API.mod";	// Modelo para calcular o congestionamento.
// 
// float ALFA = 0.01;	// CONFIANCA = 1 - ALFA.
// float ERRO = 0.01;		// Margem de erro para as estatísticas.
// unsigned long Max_Amostra = 1000000;	// Tamanho máximo da amostra.
// float Min_Amostra = 1000;
// int PLB_PRECISION = 6;
// 
// inline double apx(double x) { if(x < pow(10,-PLB_PRECISION)) return pow(10,-PLB_PRECISION); else  return x; }

// Inicia as variáveis.
void rede::Iniciar(int argc, char** argv)
{
  if (NDC == 0) Evolve(argc,argv);
  
/*  for(int i=1; i<argc;) 
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
	    
	    if ( buffer == "GLPK_TERM_OUT") 
	    {
	      in >> GLPK_TERM_OUT;
	      getline(in, buffer);
	      file << "\n Lido: GLPK_TERM_OUT= " << Min_Amostra << ", Comentário: " << buffer;
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
  }*/
  WriteResumoGA( argv [ 0 ] );	// Imprime um resumo da instancia.
  
  
/*  HmaxLB = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxHLDA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxRLDA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxMaxA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxM = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxD = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  TimeS = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  HmaxMn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  HmaxDn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  Hmax = new_cube_double(Sn+1,GLmax(Ma),Max_Amostra);	// ;
  FTnetLB = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  FTnetRLDA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  FTnetMaxA = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  FTnetM = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  FTnetD = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  TimeSFTnet = new_matrix_double(Sn+1,GLmax(Ma));	// ;
  FTnetMn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  FTnetDn = new_matrix_int(Sn+1,GLmax(Ma));	// ;
  FTnet = new_cube_double(Sn+1,GLmax(Ma),Max_Amostra);	// ;*/
}// ::Inicia

#include "datamod.C"
#include "allfiles.C"


// // Libera a memória dos vetores alocados dinamicamente.
// rede::~rede()
// {
// /*  HmaxLB = del_matrix_double(Sn+1,GLmax(Ma),HmaxLB );	// ;
//   HmaxHLDA = del_matrix_double(Sn+1,GLmax(Ma), HmaxHLDA);	// ;
//   HmaxRLDA = del_matrix_double(Sn+1,GLmax(Ma), HmaxRLDA);	// ;
//   HmaxMaxA = del_matrix_double(Sn+1,GLmax(Ma), HmaxMaxA);	// ;
//   HmaxM = del_matrix_double(Sn+1,GLmax(Ma), HmaxM);	// ;
//   HmaxD = del_matrix_double(Sn+1,GLmax(Ma), HmaxD);	// ;
//   TimeS = del_matrix_double(Sn+1,GLmax(Ma), TimeS);	// ;
//   HmaxMn = del_matrix_int(Sn+1,GLmax(Ma), HmaxMn);	// ;
//   HmaxDn = del_matrix_int(Sn+1,GLmax(Ma), HmaxDn);	// ;
//   Hmax = del_cube_double(Sn+1,GLmax(Ma),Max_Amostra, Hmax);	// ;
//   FTnetLB = del_matrix_double(Sn+1,GLmax(Ma),FTnetLB );	// ;
//   FTnetRLDA = del_matrix_double(Sn+1,GLmax(Ma), FTnetRLDA);	// ;
//   FTnetMaxA = del_matrix_double(Sn+1,GLmax(Ma), FTnetMaxA);	// ;
//   FTnetM = del_matrix_double(Sn+1,GLmax(Ma), FTnetM);	// ;
//   FTnetD = del_matrix_double(Sn+1,GLmax(Ma), FTnetD);	// ;
//   TimeSFTnet = del_matrix_double(Sn+1,GLmax(Ma), TimeSFTnet);	// ;
//   FTnetMn = del_matrix_int(Sn+1,GLmax(Ma), FTnetMn);	// ;
//   FTnetDn = del_matrix_int(Sn+1,GLmax(Ma), FTnetDn);	// ;
//   FTnet = del_cube_double(Sn+1,GLmax(Ma),Max_Amostra, FTnet);	// ;*/
// }// ::~rede()

// // Executa o simplex e retorna o valor da função objetivo.
// double rede::Simplex(string MODEL,const  char* DATA)
// {
// //   cerr << "\n Simplex in...\n";
//   const char* dump = MODEL.c_str();
//   const char* dump2 = AUX_OUT_FILE.c_str();
//   LPX *LP;
//   glp_term_out(GLPK_TERM_OUT);
// //   	cout << "LP criado." << "\n";
//   LP = lpx_read_model(dump, DATA, dump2 );		// Inicia o modelo.
// //   cout << "\nLP lido. MODEL = " << dump << " DATA = " << DATA << " OUT_FILE = " << dump2 << "\n";
//   
//   lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
//   lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
// /*  cerr << "\n Simplex start...";*/
//   
//   if(lpx_simplex(LP)!=200) return printf("Simplex: ERRO!\n");	// Executa o simplex.
// //     cout << "\nSimplex - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
//     
//   double obj = lpx_get_obj_val(LP);
//   lpx_delete_prob(LP);
//   string buffer = "rm -f out " + AUX_OUT_FILE;
//   system(buffer.c_str());
// //   cerr << "\n Simplex out...";
//   
//   return obj;
// }// ::Simplex()

// // Executa o HLDA e retorna o valor do congestionamento.
// double rede::HLDA(const char* DATA, int gl, int k)
// {
// //   cerr << "\n HLDA in...";
//   tmatrix m = makeMatrix(T[k], T[k]);
//   fill(m, 0);
// 
//   tmatrix d = makeMatrix(T[k], T[k]);
//   fill(d, 0);
// 
//   for(int i=0; i<T[k]-1; i++)
//   {
//     for(int j=i+1; j<T[k];j++)
//     {
//       setData(d, i, j, demS[k][i][j]);
//       setData(d, j, i, demS[k][j][i]);
//     }//j
//   }//i
// 
//   m = hlda(m, d, gl);
// 
//   string MODEL = HmaxLP_API_MODEL;
//   const char* dump = MODEL.c_str();
//   const char* dump2 = AUX_OUT_FILE.c_str();
//   LPX *LP;
//   glp_term_out(GLPK_TERM_OUT);
// //   	cout << "LP criado." << "\n";
//   LP = lpx_read_model(dump, DATA, dump2 );		// Inicia o modelo.
// //   cout << "\nLP lido. MODEL = " << dump << " DATA = " << DATA << " OUT_FILE = " << dump2 << "\n";
//   
//   lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
//   lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
// /*  cerr << "\n Simplex start...";*/
// 
//   for(int j=0;j<T[k]*T[k];j++) lpx_set_col_bnds(LP,j+1,LPX_FX,(double)getData(m,j/T[k],j%T[k]),0);
// 
//   if(lpx_simplex(LP)!=200) return printf("Simplex: ERRO!\n");	// Executa o simplex.
// //     cout << "\nSimplex - Hmax = " << lpx_get_obj_val(LP) << "\n\n";
//     
//   double obj = lpx_get_obj_val(LP);
//   lpx_delete_prob(LP);
//   string buffer = "rm -f out " + AUX_OUT_FILE;
//   system(buffer.c_str());
// 
//   return obj;
// }// ::HLDA

// Determina o LB a partir do LBP.
// float rede::MTB(int k,  int gl)
// {
//   float mtb = 0;
//   
//   for (int i = 0; i < T[k]; i++ ) 
//   {
//      float somai = 0;
//      float somaj = 0;
//      
//      for ( int j = 0; j < T[k]; j++ )
//       {
// 	 somai += demS[k][i][j];
// 	 somaj += demS[k][j][i];
//       }
//       
//       if (somai > mtb) mtb = somai;
//       if (somaj > mtb) mtb = somaj;
//   }
//   
//   if (mtb > 0) mtb = mtb/gl;
//   
//   return mtb;
// }// MTB

// Forwarded Trafﬁc Bound 
/*float rede::FTB(int k,  int gl)
{
  float ftb = 0;
  
  if (gl > 1) 
  {
	 int kt = ceil( log(1 + T[k]*(gl - 1))/log(gl) ) - 2;
// 	 cerr << "\nFTB - mior que 1 - 3... kt = " << kt << " T[k] = " << T[k] << " gl = " << gl;
	 
	 for (int i = 0; i < T[k]; i++ ) 
	 {
		for ( int l = 1; l <= kt; l++ )
		{
// 		  cerr << "\nFTB - mior que 1 - 4...";
		  for ( int j = 1 + min( double(T[k]-1),(pow(gl,l+1)-1)/(gl-1) - 1 ); j <= min( double(T[k]-1),(pow(gl,l+2)-1)/(gl-1) - 1 ) ; j++ )
		  {
			 ftb += l*demS[k][i][demSord[k][i][j-1]];
// 			 cerr << l << "*" << demS[k][i][demSord[k][i][j-1]] << " + ";
		  }
		}
	 }
  }
  else
  {
// 		  cerr << "\nFTB4...";
	 for (int i = 0; i < T[k]; i++ ) 
	 {
		for ( int j = 1; j < T[k]-1; j++ )
		{
		  ftb += j*demS[k][i][demSord[k][i][j]];
		}
	 }
  }*/
// //   cerr << "\nFTB - Final ...\n\n";
//   
//   return ftb;
// }

// #include "statistic.C"
// #include "statisticFTnet.C"















