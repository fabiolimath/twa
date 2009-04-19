

// Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
void rede::Statistica(const char* DATA, int gl, int k)
{
  double  RLDA = 0;	// Melhor resultado.
  double  MaxA = 0;	// Máximo amostral.
  double   X[Max_Amostra+1];	// Amostra.
  double somaX = 0;	// Soma das amostras.
  double     S = 0;	// Variância Amostral.
  unsigned   n = 1;	// Tamanho da amostra.
  unsigned  nm = 0;	// Tamanho de Amostra para a média.
  unsigned  ns = 0;	// Tamanho de Amostra para o desvio padrão.
  double Xerro = 0;
  
/*  normal Z;
  unsigned np = pow( quantile(Z, ALFA / 2)/(2*ERRO), 2);*/
//   cerr << "\nnp = " << np;
  
  const char* dump = HmaxLP_API_MODEL.c_str();
  const char* dump2 = AUX_OUT_FILE.c_str();
  LPX *LP;
  glp_term_out(GLPK_TERM_OUT);
  LP = lpx_read_model(dump, DATA, dump2 );		// Inicia o modelo.
  lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
  lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.

  tmatrix m = makeMatrix(T[k], T[k]);
  fill(m, 0); 
  srand(n);
  m = rldaRing(m, gl);
  
/*  cout << "\nTopologia: \n";
  for(int i = 0; i < T[k]; i++)
  {for(int j = 0; j < T[k]; j++)
  cout << getData(m,i,j) << " ";
  cout << "\n";}
  cout << "\n";*/
  
  for(int j=0;j<T[k]*T[k];j++) lpx_set_col_bnds(LP,j+1,LPX_FX,(double)getData(m,j/T[k],j%T[k]),0);
  
  if(lpx_simplex(LP)!=200) { printf("Simplex: ERRO!\n"); return;}	// Executa o simplex.
    
    X[n] = (lpx_get_obj_val(LP)/HmaxLB[k][gl-1]) - 1;
    RLDA = lpx_get_obj_val(LP);
    MaxA = lpx_get_obj_val(LP);
    //   cout << "\n X[n] = " << X[n] << "";
    //   cout << "\n lpx_get_obj_val(LP) = " << lpx_get_obj_val(LP) << "";
    //   
    //cout << "\n X[n] = " << X[n] << "\n";
    
    somaX += X[n];
    X[0] = somaX/n;
    
    cerr << "\nk = " << (k+1)%(Sn+1) << " - T[k] = " << T[k] << " - GL = " << gl;
    
    int bitM = 0;
    int bitD = 0;
    
    double tempo = clock();			// Marca o inicio do algoritmo.
    
    do
    {
      n++;
      
      srand(n);
      fill(m, 0);
      m = rldaRing(m, gl);
      
      /*      cout << "\nTopologia: \n";
      for(int i = 0; i < T[k]; i++)
      {for(int j = 0; j < T[k]; j++)
      cout << getData(m,i,j) << " ";
      cout << "\n";}
      cout << "\n";*/
      
      for(int j=0;j<T[k]*T[k];j++) lpx_set_col_bnds(LP,j+1,LPX_FX,(double)getData(m,j/T[k],j%T[k]),0);
      
      if(lpx_simplex(LP)!=200) { printf("Simplex: ERRO!\n"); return;}	// Executa o simplex.
      
        X[n] = (lpx_get_obj_val(LP)/round(HmaxLB[k][gl-1],PLB_PRECISION)) - 1;
      if (lpx_get_obj_val(LP) < RLDA) RLDA = lpx_get_obj_val(LP);
      if (lpx_get_obj_val(LP) > MaxA) MaxA = lpx_get_obj_val(LP);
      somaX += X[n];
      
      if (n >= Min_Amostra)
      {
	X[0] = somaX/n;
	S = 0;
	for(unsigned i = 1; i <= n; i++ ) S += pow(X[i] - X[0],2);
	S = sqrt( S/(n - 1) );
	
	if (bitM==0)
	{
	  students_t distT(n - 1);
	  double StudentsT = quantile(complement(distT, ALFA / 2));
	  unsigned auxnm = (unsigned)ceil(pow(StudentsT*S/ERRO,2));
	  
	  if (auxnm < n)
	  {
	    nm = n;
	    bitM = 1;
	  }
	}
	
	if (bitD==0)
	{
	  
	  chi_squared distX(n - 1);
	  double XSquare1 = quantile(complement(distX, ALFA/2));
	  double XSquare2 = quantile(distX, ALFA/2);
	  double LimInfS = sqrt( (n - 1)*pow(S,2)/XSquare1 );
	  double LimSupS = sqrt( (n - 1)*pow(S,2)/XSquare2 );
	  Xerro = (LimSupS - LimInfS)/2;
	  
	  if (Xerro <= ERRO)
	  {
	    S = LimSupS - Xerro;
	    ns = n;
	    bitD = 1;
	  }
	}
      }
      /*	cerr << "\nN = " << n << " - nm = " << nm;
      cerr << " - X[n] = " << round(X[n],3);
      // 	cout << " - LP = " << lpx_get_obj_val(LP);
      cerr << " - Xerro = " << Xerro;*/
      
} while ( (!bitM || !bitD) && (n < Max_Amostra) );

tempo = clock() - tempo;			// Marca o fim do algori­tmo.

// cerr << "\nDone!\n\n\n";

TimeS[k][gl-1] = tempo/CLOCKS_PER_SEC;
HmaxRLDA[k][gl - 1] = RLDA;
HmaxM[k][gl - 1] = X[0];
HmaxMn[k][gl - 1] = nm;
HmaxD[k][gl - 1] = S;
HmaxDn[k][gl - 1] = ns;
HmaxMaxA[k][gl - 1] = MaxA;
for(unsigned i = 1; i <= n; i++ ) Hmax[k][gl - 1][i-1] = X[i];

ofstream file;

string INFO_FILE(DATA);
INFO_FILE += ".amostra";

file.open( INFO_FILE.c_str() );
if (file.is_open())
{
/*  file << "\n" << DATA << "\n";
  file << "\nLB = " << HmaxLB[k][gl - 1];
  file << "\nHLDA = " << HmaxHLDA[k][gl - 1];
  file << "\nRLDA = " << HmaxRLDA[k][gl - 1];
  file << "\nMédia  = " << HmaxM[k][gl - 1];
  file << "\nDesvio Padrão = " << HmaxD[k][gl - 1];
  file << "\nMáximo Amostral = " << HmaxMaxA[k][gl - 1];
  file << "\nTamanho de Amostra para a Média  = " << HmaxMn[k][gl - 1];
  file << "\nTamanho de Amostra para o Desvio Padrão = " << HmaxDn[k][gl - 1];
  file << "\nAmostra:\n";*/
  for(unsigned i = 0; i < n; i++ ) file << Hmax[k][gl - 1][i] << "\n";
//   file << "\n\n";
  file.close();
}


ostringstream oss;
oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".statistics";
string dir = oss.str();

file.open( dir.c_str(), ofstream::app );
if (file.is_open())
{
  file << "\n";
  file << (k+1)%(Sn+1) << " ";
  file << T[k] << "\t";
  file << gl << "  ";
  file << TimeS[k][gl-1] << "\t";
  file << HmaxMn[k][gl - 1] << "\t";
  file << HmaxDn[k][gl - 1] << "\t";
  file << HmaxLBi[k][gl - 1] << "\t";
  file << HmaxLB[k][gl - 1] << "\t";//
  file << round(abs((HmaxHLDA[k][gl - 1]/round(HmaxLB[k][gl-1],PLB_PRECISION)) - 1),2) << "\t";
  file << round(abs((HmaxRLDA[k][gl - 1]/round(HmaxLB[k][gl-1],PLB_PRECISION)) - 1),2) << "\t";
  file << round(abs((HmaxMaxA[k][gl - 1]/round(HmaxLB[k][gl-1],PLB_PRECISION)) - 1),2) << "\t";
  file << setprecision(4) << HmaxM[k][gl - 1] << "\t";
  file << HmaxD[k][gl - 1] << "\t";
  
  file.close();
}



lpx_delete_prob(LP);
destroyMatrix(m);
string buffer = "rm -f out " + AUX_OUT_FILE;
system(buffer.c_str());

}// ::Statistica





