

// Estima a média e o desvio padrão para o congestionamento, com de uma amostra representativa, e guarda o mínimo amostral.
void rede::Statistica(const char* DATA, int gl, int k)
{
  double  RLDA = 0;	// Melhor resultado.
  double  MaxA = 0;	// Máximo amostral.
  double   X[Max_Amostra];	// Amostra.
  double somaX = 0;	// Soma das amostras.
  double     S = 0;	// Variância Amostral.
  unsigned   n = 1;	// Tamanho da amostra.
  unsigned  nm = 0;	// Tamanho de Amostra para a média.
  unsigned  ns = 0;	// Tamanho de Amostra para o desvio padrão.
  double Xerro = 0;
  
  tmatrix d = makeMatrix(T[k], T[k]);
  tmatrix m = makeMatrix(T[k], T[k]);
  fill(d, 0);
  
  for(int i=0; i<T[k]-1; i++)
  {
    for(int j=i+1; j<T[k];j++)
    {
      setData(d, i, j, demS[k][i][j]);
      setData(d, j, i, demS[k][j][i]);
    }//j
  }//i
  
  const char* dump = HmaxLP_API_MODEL.c_str();
  const char* dump2 = AUX_OUT_FILE.c_str();
  LPX *LP = lpx_read_model(dump, DATA, dump2 );		// Inicia o modelo.
  lpx_set_int_parm(LP, LPX_K_MSGLEV, GLPK_MSGLEV);		// Nivel de verborragia do glpk.
  lpx_set_int_parm(LP, LPX_K_PRESOL, GLPK_PRESOL);		// Usar ou não o presolver.
  // 	cout << "LP criado." << "\n";
  
  fill(m, 0);
  srand(n);
  m = rldaRing(d, gl);
  fill(m, 0);
  srand(n);
  m = rldaRing(d, gl);
  
  /*  cout << "\nTopologia: \n";
  for(int i = 0; i < T[k]; i++)
  {for(int j = 0; j < T[k]; j++)
  cout << getData(m,i,j) << " ";
  cout << "\n";}
  cout << "\n";*/
          
  
  for(int j=0;j<T[k]*T[k];j++) lpx_set_col_bnds(LP,j+1,LPX_FX,(double)getData(m,j/T[k],j%T[k]),0);
  
  if(lpx_simplex(LP)!=200) { printf("Simplex: ERRO!\n"); return;}	// Executa o simplex.
    
    X[n] = (lpx_get_obj_val(LP)/HmaxLB[k][gl]) - 1;
    RLDA = lpx_get_obj_val(LP);
    MaxA = lpx_get_obj_val(LP);
    //   cout << "\n X[n] = " << X[n] << "";
    //   cout << "\n lpx_get_obj_val(LP) = " << lpx_get_obj_val(LP) << "";
    //   
    //cout << "\n X[n] = " << X[n] << "\n";
    
    somaX += X[n];
    X[0] = somaX/n;
    
    do
    {
      n++;
      
      srand(n);
      fill(m, 0);
      m = rldaRing(d, gl);
      
      /*      cout << "\nTopologia: \n";
      for(int i = 0; i < T[k]; i++)
      {for(int j = 0; j < T[k]; j++)
      cout << getData(m,i,j) << " ";
      cout << "\n";}
      cout << "\n";*/
      
      for(int j=0;j<T[k]*T[k];j++) lpx_set_col_bnds(LP,j+1,LPX_FX,(double)getData(m,j/T[k],j%T[k]),0);
      
      if(lpx_simplex(LP)!=200) { printf("Simplex: ERRO!\n"); return;}	// Executa o simplex.
	
	X[n] = (lpx_get_obj_val(LP)/HmaxLB[k][gl]) - 1;
	//       cout << "\n" << X[n];
	
	if (lpx_get_obj_val(LP) < RLDA) RLDA = lpx_get_obj_val(LP);
	if (lpx_get_obj_val(LP) > MaxA) MaxA = lpx_get_obj_val(LP);
	
	somaX += X[n];
	X[0] = somaX/n;
	S = 0;
	for(unsigned i = 1; i <= n; i++ ) S += pow(X[i] - X[0],2);
	S = sqrt( S/(n - 1) );
	students_t distT(n - 1);
	double StudentsT = quantile(complement(distT, ALFA / 2));
	
	nm = (unsigned)ceil(pow(StudentsT*S/ERRO,2));
	
	cout << "\nT[k] = " << T[k] << " - GL = " << gl << " - N = " << n << " - StT = " << StudentsT << "\t - nm = " << pow(StudentsT*S/ERRO,2) << " \t-> " << nm;
	cout << " - X[n] = " << round(X[n],3);
	cout << " - LP = " << lpx_get_obj_val(LP);
	cout << " - Xerro = " << Xerro << " - Desvio = " << S;
	
	chi_squared distX(n - 1);
	double XSquare1 = quantile(complement(distX, ALFA/2));
	double XSquare2 = quantile(complement(distX, 1-(ALFA/2)));
	double LimInfS = sqrt( (n - 1)*pow(S,2)/XSquare1 );
	double LimSupS = sqrt( (n - 1)*pow(S,2)/XSquare2 );
	Xerro = (LimSupS - LimInfS)/2;
	
	if (Xerro <= ERRO)
	{
	  S = LimInfS + Xerro;
	  ns = n;
	}
	
	
} while ( ( ((nm > n) || (Xerro > ERRO)) && (n < Max_Amostra) ) || (n < Min_Amostra) );

HmaxRLDA[k][gl] = RLDA;
HmaxM[k][gl] = X[0];
HmaxMn[k][gl] = nm;
HmaxD[k][gl] = S;
HmaxDn[k][gl] = ns;

lpx_delete_prob(LP);
/*destroyMatrix(m);
destroyMatrix(d);*/
string buffer = "rm -f out " + AUX_OUT_FILE;
system(buffer.c_str());

}// ::Statistica





