

#include "include/cabecalho.h"


// Definições:
int GLPK_MSGLEV = 0;	// Nivel de verborragia do glpk.
int GLPK_PRESOL = 1;	// Usar ou não o presolver.
int GLPK_TERM_OUT = 0;	// Saída de terminal, sim (1) ou não (0) ?
string AUX_OUT_FILE = "models/out";	// Arquivo auxiliar para a saída do GLPK.

string HmaxLP_API_MODEL = "models/labtel-HmaxLP-API.mod";	// Modelo para calcular o congestionamento.
string HmaxLP_API_FTnet_MODEL = "models/labtel-HmaxLP-FTnet-API.mod";	// Modelo para calcular o congestionamento.

float ALFA = 0.01;	// CONFIANCA = 1 - ALFA.
float ERRO = 0.01;		// Margem de erro para as estatísticas.
unsigned long Max_Amostra = 100000;	// Tamanho máximo da amostra.
float Min_Amostra = 1000;
int PLB_PRECISION = 6;

inline double apx(double x) { if(x < pow(10,-PLB_PRECISION)) return pow(10,-PLB_PRECISION); else  return x; }

float MTB(float **Dem, int T,  int gl);
float FTB(float **Dem, int T,  int gl);


// Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
int main(int argc, char** argv) 


// void rede::Statistica(const char* DATA, int gl, int k)
{
   
//   char *MODEL;
  char *DATA;
  int T = 0;
  int gl = 0;
  string id;
  float **Dem;
  
  int verborragia = 0;
  
   DATA = argv [ 1 ];	// Dados;

   for(int i=1; i<argc;) 
    if(strcmp(argv[i++],"-v") == 0) 
      verborragia = 1;
   
   ifstream in(DATA); 
   
   if(!in) {
         cerr << "\nCould not read DATA file " << DATA << "\n";
         exit(1);
   }
   
   do 
   {
         string buffer;
         in >> buffer;
         
         if ( buffer == "param" )
         {
	  in >> buffer;
	  
	  if ( buffer == "N")
	  {
	     in >> buffer;
	     in >> T;
	     getline(in, buffer);
	     Dem = new_matrix_float(T+1,T+1);	// ;
	     continue;
	  }
	  
	  if ( buffer == "gl") 
	  {
	     in >> buffer;
	     in >> gl;
	     getline(in, buffer);
	     continue;
	  }
	  
	  if ( buffer == "D") 
	  {
	     getline(in, buffer);
	     for(int i = 0; i < T; i++)
	     {
	        in >> buffer;
	        for(int j = 0; j < T; j++) in >> Dem[i][j];
	     }
	     continue;
	  }
         }
         
         if ( buffer == "#" )
         {
	  in >> buffer;
	  
	  if ( buffer == "backbone")
	  {
	     id = "bk";
	     getline(in, buffer);
	     continue;
	  }
	  
	  if ( buffer == "cluster")
	  {
	     id = "c";
	     in >> buffer;
	     id += buffer;
	     getline(in, buffer);
	     continue;
	  }
         }
   } while(!in.eof());
   in.close();

   
   string DATA_FILE(DATA);
   DATA_FILE.replace(DATA_FILE.find(".mod"),4,".W1.TIFgap0.1.mod");

   ofstream data( DATA_FILE.c_str() );
   
   in.open(DATA);
   do
   {
      string tmp;
      getline(in, tmp);
      data << tmp << "\n";
   } while(!in.eof());
   in.close();
   data.close();   
    
/*  normal Z;
  unsigned np = pow( quantile(Z, ALFA / 2)/(2*ERRO), 2);*/
//   cerr << "\n\nArquivo Lido\n\n";

   unsigned   n = 0;	// Tamanho da amostra.

   /// Congestionamento
   double   X[2][Max_Amostra+1];	// Amostra.
   double HmaxLB = (double)MTB(Dem, T, gl);
   double  RLDAc = 0;	// Melhor resultado.
   double  HLDAc = 0;	// HLDA.
   double  MaxAc = 0;	// Máximo amostral.
   double somaXc = 0;	// Soma das amostras.
   double     Sc = 0;	// Variância Amostral.
   unsigned  nmc = 0;	// Tamanho de Amostra para a média.
   unsigned  nsc = 0;	// Tamanho de Amostra para o desvio padrão.
   const char* dumpc = HmaxLP_API_MODEL.c_str();
   LPX *LPc;

   /// Tráfego Retransmitido
   double FTnetLB = (double)FTB(Dem, T, gl);
   double  RLDAt = 0;	// Melhor resultado.
   double  HLDAt = 0;	// HLDA.
   double  MaxAt = 0;	// Máximo amostral.
   double somaXt = 0;	// Soma das amostras.
   double     St = 0;	// Variância Amostral.
   unsigned  nmt = 0;	// Tamanho de Amostra para a média.
   unsigned  nst = 0;	// Tamanho de Amostra para o desvio padrão.
   const char* dumpt = HmaxLP_API_FTnet_MODEL.c_str();
   LPX *LPt;
//   cerr << "\n\nVariáveis Definidas\n\n";
   
   data.open(DATA_FILE.c_str(), ofstream::app);
   if ( data.is_open() )
   {	    
      data << "\nparam HmaxLB := " << HmaxLB << " ;" ;
      data << "\nparam FTnetLB := " << FTnetLB << " ;" ;
      data.close();
   }
//   cerr << "\n\nLB's gravados\n\n";
  
  const char* dump2 = AUX_OUT_FILE.c_str();

  glp_term_out(GLPK_TERM_OUT);

  LPc = lpx_read_model(dumpc, DATA, dump2 );		// Inicia o modelo.
//   lpx_set_int_parm(LPc, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
//   lpx_set_int_parm(LPc, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.

  LPt = lpx_read_model(dumpt, DATA, dump2 );		// Inicia o modelo.
//   lpx_set_int_parm(LPt, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
//   lpx_set_int_parm(LPt, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.

  tmatrix d = makeMatrix(T, T);
  fill(d, 0);

  for(int i=0; i<T-1; i++)
  {
    for(int j=i+1; j<T;j++)
    {
      setData(d, i, j, Dem[i][j]);
      setData(d, j, i, Dem[j][i]);
    }//j
  }//i
  tmatrix m = makeMatrix(T, T);
  
  /// HLDA
    srand(n);
    fill(m, 0); 
    m = hlda(m, d, gl);
  
    for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPc,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);
    for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPt,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);

    if(lpx_simplex(LPc)!=200) { printf("Simplex: Congestionamento -  ERRO!\n"); return 1;}	// Executa o simplex.
    if(lpx_simplex(LPt)!=200) { printf("Simplex: Tráfego Retransmitido - ERRO!\n"); return 1;}	// Executa o simplex.

    HLDAc = apx((lpx_get_obj_val(LPc)/HmaxLB) - 1);
    HLDAt = apx((lpx_get_obj_val(LPt)/FTnetLB) - 1);

/*  cout << "\nTopologia do HLDA: \n";
  for(int i = 0; i < T; i++)
  {for(int j = 0; j < T; j++)
  cout << getData(m,i,j) << " ";
  cout << "\n";}
  cout << "\n";*/

   /// Primeiro elemento da Amostra
   n++;
   srand(n);
   fill(m, 0);
   m = rldaRing(m, gl);

    for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPc,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);
    for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPt,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);

    if(lpx_simplex(LPc)!=200) { printf("Simplex: Congestionamento -  ERRO!\n"); return 1;}	// Executa o simplex.
    if(lpx_simplex(LPt)!=200) { printf("Simplex: Tráfego Retransmitido - ERRO!\n"); return 1;}	// Executa o simplex.

    double gapc = apx((lpx_get_obj_val(LPc)/HmaxLB) - 1);
    X[1][n] = gapc;
    RLDAc = gapc;
    MaxAc = gapc;
    HLDAc = gapc;

    double gapt = apx((lpx_get_obj_val(LPt)/FTnetLB) - 1);
    X[0][n] = gapt;
    RLDAt = gapt;
    MaxAt = gapt;
    HLDAt = gapt;

    //   cout << "\n X[n] = " << X[n] << "";
    //   cout << "\n lpx_get_obj_val(LP) = " << lpx_get_obj_val(LP) << "";
    //cout << "\n X[n] = " << X[n] << "\n";
    
    somaXc += X[1][n];
    X[1][0] = somaXc/n;
    
    somaXt += X[0][n];
    X[0][0] = somaXt/n;
    
//     cerr << "\nID = " << id << " - T = " << T << " - GL = " << gl;
    
    int bitMc = 0;
    int bitDc = 0;
    
    int bitMt = 0;
    int bitDt = 0;
    
    double tempo = clock();			// Marca o inicio do algoritmo.
    
    do
    {
      n++;
      
      srand(n);
      fill(m, 0);
      m = rldaRing(m, gl);
      
      /*      cout << "\nTopologia: \n";
      for(int i = 0; i < T; i++)
      {for(int j = 0; j < T; j++)
      cout << getData(m,i,j) << " ";
      cout << "\n";}
      cout << "\n";*/
      
      for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPc,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);
      for(int j=0;j<T*T;j++) lpx_set_col_bnds(LPt,j+1,LPX_FX,(double)getData(m,j/T,j%T),0);
      
      if(lpx_simplex(LPc)!=200) { printf("Simplex: Congestionamento -  ERRO!\n"); return 1;}	// Executa o simplex.
      if(lpx_simplex(LPt)!=200) { printf("Simplex: Tráfego Retransmitido - ERRO!\n"); return 1;}	// Executa o simplex.
      
/*      double gap = (round(lpx_get_obj_val(LP),PLB_PRECISION)/round(HmaxLB,PLB_PRECISION)) - 1;
      
      if ( gap < pow(10,-PLB_PRECISION) )
      {
	 X[n] = pow(10,-PLB_PRECISION);
      }
      else
      {
	 X[n] = gap;
      }*/
      
      gapc = apx((lpx_get_obj_val(LPc)/HmaxLB) - 1);
     X[1][n] = gapc;
      
      if (gapc < RLDAc) RLDAc = gapc;
      if (gapc > MaxAc) MaxAc = gapc;
      somaXc +=X[1][n];
      
      gapt = apx((lpx_get_obj_val(LPt)/FTnetLB) - 1);
      X[0][n] = gapt;
      
      if (gapt < RLDAt) RLDAt = gapt;
      if (gapt > MaxAt) MaxAt = gapt;
      somaXt += X[0][n];
      
      if (n >= Min_Amostra)
      {
	X[1][0] = somaXc/n;
	Sc = 0;
	for(unsigned i = 1; i <= n; i++ ) Sc += pow(X[1][i] - X[1][0],2);
	Sc = sqrt( Sc/(n - 1) );

	X[0][0] = somaXt/n;
	St = 0;
	for(unsigned i = 1; i <= n; i++ ) St += pow(X[0][i] - X[0][0],2);
	St = sqrt( St/(n - 1) );
	
	if (bitMc==0)
	{
	  students_t distT(n - 1);
	  double StudentsT = quantile(complement(distT, ALFA / 2));
	  unsigned auxnm = (unsigned)ceil(pow(StudentsT*Sc/ERRO,2));
	  
	  if (auxnm < n)
	  {
	    nmc = n;
	    bitMc = 1;
	  }
	}
	
	if (bitMt==0)
	{
	  students_t distT(n - 1);
	  double StudentsT = quantile(complement(distT, ALFA / 2));
	  unsigned auxnm = (unsigned)ceil(pow(StudentsT*St/ERRO,2));
	  
	  if (auxnm < n)
	  {
	    nmt = n;
	    bitMt = 1;
	  }
	}
	
	if (bitDc==0)
	{
	  
	  chi_squared distX(n - 1);
	  double XSquare1 = quantile(complement(distX, ALFA/2));
	  double XSquare2 = quantile(distX, ALFA/2);
	  double LimInfS = sqrt( (n - 1)*pow(Sc,2)/XSquare1 );
	  double LimSupS = sqrt( (n - 1)*pow(Sc,2)/XSquare2 );
	  double Xerro = (LimSupS - LimInfS)/2;
	  
	  if (Xerro <= ERRO)
	  {
	    Sc = LimSupS - Xerro;
	    nsc = n;
	    bitDc = 1;
	  }
	}
	
	if (bitDt==0)
	{
	  
	  chi_squared distX(n - 1);
	  double XSquare1 = quantile(complement(distX, ALFA/2));
	  double XSquare2 = quantile(distX, ALFA/2);
	  double LimInfS = sqrt( (n - 1)*pow(St,2)/XSquare1 );
	  double LimSupS = sqrt( (n - 1)*pow(St,2)/XSquare2 );
	  double Xerro = (LimSupS - LimInfS)/2;
	  
	  if (Xerro <= ERRO)
	  {
	    St = LimSupS - Xerro;
	    nst = n;
	    bitDt = 1;
	  }
	}
      }
      /*	cerr << "\nN = " << n << " - nm = " << nm;
      cerr << " - X[n] = " << round(X[n],3);
      // 	cout << " - LP = " << lpx_get_obj_val(LP);
      */
      
} while ( !(bitMc*bitDc*bitMt*bitDt) && (n < Max_Amostra) );

tempo = (clock() - tempo)/CLOCKS_PER_SEC;			// Marca o fim do algori­tmo.

double TempMed;
unsigned int biggestN = 0;

if (nmc > biggestN) biggestN = nmc;
if (nsc > biggestN) biggestN = nsc;
if (nmt > biggestN) biggestN = nmt;
if (nst > biggestN) biggestN = nst;
   
TempMed = tempo/((double)biggestN);

// cerr << "\nDone!\n\n\n";

string amostra(DATA);
amostra.replace(amostra.find(".mod"),4,".Hmax.amostra");

data.open( amostra.c_str() );
if (data.is_open())
{
  for(unsigned i = 1; i <= n; i++ ) data << X[1][i] << "\n";
  data.close();
}

amostra = DATA;
amostra.replace(amostra.find(".mod"),4,".FTnet.amostra");

data.open( amostra.c_str() );
if (data.is_open())
{
  for(unsigned i = 1; i <= n; i++ ) data << X[0][i] << "\n";
  data.close();
}

if(verborragia)
{
//    cout << "\n";
if(verborragia) cout << "    " << "  ";
   cout << "id" << " ";
   cout << "T" << " ";
   cout << "gl" << "  ";
   cout << "nm" << "\t";
   cout << "tnm" << "\t";
   cout << "ns" << "\t";
   cout << "tns" << "\t";
   cout << "LB" << "\t";//
   cout << "HLDA" << "\t";
   cout << "RLDA" << "\t";
   cout << "MaxA" << "\t";
   cout << "Med" << "\t";
   cout << "DP";
   cout << "\n";
}

if(verborragia) cout << "Hmax" << "  ";
cout << id << " ";
cout << T << " ";
cout << gl << "  ";
cout << nmc << "\t";
cout << TempMed*nmc << "\t";
cout << nsc << "\t";
cout << TempMed*nsc << "\t";
cout << HmaxLB << "\t";//
cout << setprecision(2) << HLDAc << "\t";
cout << RLDAc << "\t";
cout << MaxAc << "\t";
cout << X[1][0] << "\t";
cout << Sc;

cout << "\n";
if(verborragia) cout << "FTnet" << " ";
cout << id << " ";
cout << T << " ";
cout << gl << "  ";
cout << nmt << "\t";
cout << TempMed*nmt << "\t";
cout << nst << "\t";
cout << TempMed*nst << "\t";
cout << FTnetLB << "\t";//
cout << setprecision(2) << HLDAt << "\t";
cout << RLDAt << "\t";
cout << MaxAt << "\t";
cout << X[0][0] << "\t";
cout << St << "\n";

data.open( DATA_FILE.c_str(), ofstream::app );
data << "\nparam Wc     := 1 ;" ;
data << "\nparam TIFgap := 0.1 ;" ;

data << "\nparam HmaxHLDA := " << HLDAc << " ;" ;
data << "\nparam HmaxRLDA := " << RLDAc << " ;" ;
data << "\nparam HmaxMaxA := " << MaxAc << " ;" ;
data << "\nparam HmaxM := " << X[1][0] << " ;" ;
data << "\nparam HmaxD := " << Sc << " ;" ;

data << "\nparam FTnetHLDA := " << HLDAt << " ;" ;
data << "\nparam FTnetRLDA := " << RLDAt << " ;" ;
data << "\nparam FTnetMaxA := " << MaxAt << " ;" ;
data << "\nparam FTnetM := " << X[0][0] << " ;" ;
data << "\nparam FTnetD := " << St << " ;" ;
data << "\nend ;" ;
data.close();

lpx_delete_prob(LPc);
lpx_delete_prob(LPt);
destroyMatrix(m);
destroyMatrix(d);
string buffer = "rm -f out " + AUX_OUT_FILE;
system(buffer.c_str());

}// ::Statistica



// Determina o LB a partir do LBP.
float MTB(float **Dem, int T,  int gl)
{
  float mtb = 0;
//     cerr << "\n\n MTB in \n\n";

  for (int i = 0; i < T; i++ ) 
  {
     float somai = 0;
     float somaj = 0;
     
     for ( int j = 0; j < T; j++ )
      {
	 somai += Dem[i][j];
	 somaj += Dem[j][i];
      }
      
      if (somai > mtb) mtb = somai;
      if (somaj > mtb) mtb = somaj;
  }
  
  if (mtb > 0) mtb = mtb/gl;
//     cerr << "\n\n MTB out \n\n";
  
  return mtb;
}// MTB

// Forwarded Trafﬁc Bound 
float FTB(float **Dem, int T,  int gl)
{   
//        cerr << "\n\n FTB in \n\n";

   vector<vector<int> > DemOrd; // Matriz de ordem das demandas.
   
   DemOrd.resize(T + 1);
   for (int i = 0; i < T + 1; ++i) DemOrd[i].resize(T);

  
   for (int i = 0; i < T; i++ ) 
   {
      int *Vtmp = (int*) calloc (T+1, sizeof(int));
      for(int j = 0; j < T; j++ ) Vtmp[j] = j;

      for ( int l = 0; l < T- 1; l++ )
      {
         int maior = i;

         for ( int j = 0; j < T; j++ )
         {
// 	  cerr << "\nFTB2... i = " << i << " l = " << l << " j = " << j;
// 	  cerr << "\ndemS[k][i][Vtmp[j]] = " << demS[k][i][Vtmp[j]] << " demS[k][i][maior] = " << demS[k][i][maior] << " maior = " << maior;
	  if (Dem[i][Vtmp[j]] > Dem[i][maior]) maior = j;
// 	  cerr << "\ndemS[k][i][Vtmp[j]] = " << demS[k][i][Vtmp[j]] << " demS[k][i][maior] = " << demS[k][i][maior] << " maior = " << maior;
         }
      DemOrd[i][l] = maior;
      Vtmp[maior] = i;
      }

      free (Vtmp);
   }

   float ftb = 0;
 
   if (gl > 1) 
   {
      int kt = ceil( log(1 + T*(gl - 1))/log(gl) ) - 2;
// 	 cerr << "\nFTB - mior que 1 - 3... kt = " << kt << " T[k] = " << T[k] << " gl = " << gl;

      for (int i = 0; i < T; i++ ) 
      {
         for ( int l = 1; l <= kt; l++ )
         {
// 		  cerr << "\nFTB - mior que 1 - 4...";
	  for ( int j = 1 + min( double(T-1),(pow(gl,l+1)-1)/(gl-1) - 1 ); j <= min( double(T-1),(pow(gl,l+2)-1)/(gl-1) - 1 ) ; j++ )
	  {
	     ftb += l*Dem[i][DemOrd[i][j-1]];
// 			 cerr << l << "*" << demS[k][i][demSord[k][i][j-1]] << " + ";
	  }
         }
      }
   }
   else
   {
// 		  cerr << "\nFTB4...";
      for (int i = 0; i < T; i++ ) 
      {
         for ( int j = 1; j < T-1; j++ )
         {
	  ftb += j*Dem[i][DemOrd[i][j]];
         }
      }
   }
//   cerr << "\nFTB - Final ...\n\n";

  return ftb;
}



