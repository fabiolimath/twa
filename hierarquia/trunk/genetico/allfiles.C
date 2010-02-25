

// Chama o HLDA o RLDA e estima as médias.
void rede::allfiles(int argc, char** argv)
{
//   const char* MODEL = HmaxMagic_MODEL.c_str();
  const char* clus = "cluster";
//   cerr << "\n allfiles!\n\n";
  //sprintf(MODEL, HmaxMagic_MODEL);
//   cout << "\n cluster!\n\n";
  //sprintf(clus, "cluster");
  Iniciar( argc, argv );	// Inicializa a instancia, gera as matrizes de demandas e distancias e seta a semente do genético.
  cerr << "\nEvolução Terminada...\n";
//   Evolve( argc, argv );	// Executa o genético.
  WriteTamanhos();
//   cerr << "\nTamanhos salvos...\n\n";
  WriteClusters();
  cerr << "\nClusters salvos...\n\n";
  WriteFitness();
  cerr << "\nFitness salvos...\n\n";  
  SeparaMatrizes();		// Separa as matrizes de demandas e distancias dos clusters e do backbone.
  cerr << "\nMatrizes separadas...\n";
  
//   cerr << "\nEstatísticas - Iniciando outputs...\n\n";
  /*
  ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".Hmax.statistics";
  string dir = oss.str();
  
  ofstream file( dir.c_str() );
  
  if (file.is_open())
  {
    file << "k ";
    file << "T[k] ";
    file << "gl ";
    file << "Time\t";
    file << "Mn\t";
    file << "Dn\t";
    file << "LB\t";
    file << "HLDA\t";
    file << "RLDA\t";
    file << "Ma\t";
    file << "M\t";
    file << "D";
    
    file.close();
  }
  
  ostringstream oss2;
  oss2 << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".FTnet.statistics";
  string dir2 = oss2.str();
  
  ofstream filei( dir2.c_str() );
  
  if (filei.is_open())
  {
	 filei << "k ";
	 filei << "T[k] ";
	 filei << "gl ";
	 filei << "Time\t";
	 filei << "Mn\t";
	 filei << "Dn\t";
	 filei << "LB\t";
	 filei << "RLDA\t";
	 filei << "Ma\t";
	 filei << "M\t";
	 filei << "D";
	 
	 filei.close();
  }
  

  cerr << "\nEstatísticas dos Clusters...";
  */
  for(int k = 0; k < Sn; k++)
  {
//     string DATA  = DataMod(k,clus);
//     Magic[k] = Simplex ( MODEL, DATA.c_str() )*(T[k] - 1);
    
    for(int gl = 1; gl <= GLmax(T[k]); gl++)
    {
//       LBproof( round(Magic[k]/gl,PLB_PRECISION), gl, k, clus );

/*		HmaxLB[k][gl-1] = MTB(k, gl);
// 		cerr << "\nFTB...";
		FTnetLB[k][gl-1] = FTB(k, gl);*/
// 		cerr << "\nFTB OK ...";
		string DATA = DataMod(k, gl, clus);
// 		cerr << "\nDataMod OK...";
// 		HmaxHLDA[k][gl-1] = HLDA( DATA.c_str(), gl, k );
// 		cout << "\n HLDA = " << HmaxHLDA[k][gl-1] << "\n\n";
// 		Statistica(DATA.c_str(), gl, k);
// 		cerr << "StatisticaFTnet...";
// 		StatisticaFTnet(DATA.c_str(), gl, k);
		
// 		DATA = DataMod(k, clus, HmaxLB[k][gl-1], gl, FTnetLB[k][gl-1], 1, HmaxM[k][gl-1], FTnetM[k][gl-1]);		
//       cout << "\n Média: " << HmaxM[k][gl] << " amostra: " << HmaxMn[k][gl] << " Desvio padrão: " << HmaxD[k][gl] << " amostra: "<< HmaxDn[k][gl] << " RLDA: "<< HmaxRLDA[k][gl] << "\n";
    }//gl
    }//k
//     cout << "\n backbone!\n\n";
    
    //sprintf(clus, "backbone");
//     cerr << "\n\nEstatísticas do Backbone...";
    
/*    string DATA  = DataMod(Sn);
    Magic[Sn] = Simplex ( MODEL, DATA.c_str() )*(T[Sn] - 1);*/
    
    for(int gl = 1; gl <= GLmax(T[Sn]); gl++)
    {
//       LBproof( round(Magic[Sn]/gl,PLB_PRECISION), gl, Sn );
/*		HmaxLB[Sn][gl-1] = MTB(Sn, gl);
		FTnetLB[Sn][gl-1] = FTB(Sn, gl);*/
		string DATA  = DataMod(Sn, gl, "backbone");
//       HmaxHLDA[Sn][gl-1] = HLDA( DATA.c_str(), gl, Sn);
//       cout << "\n LB provado = " << HmaxLB[Sn][gl] << "\tIterações: " << HmaxLBi[Sn][gl] << "\n\n";
//       Statistica(DATA.c_str(), gl, Sn);
// 		StatisticaFTnet(DATA.c_str(), gl, Sn);
		
// 		DATA = DataMod(Sn, "backbone", HmaxLB[Sn][gl-1], gl, FTnetLB[Sn][gl-1], 1, HmaxM[Sn][gl-1], FTnetM[Sn][gl-1]);
		//       cout << "\n Média: " << HmaxM[Sn][gl] << " amostra: " << HmaxMn[Sn][gl] << " Desvio padrão" << HmaxD[Sn][gl] << " amostra: " << HmaxDn[Sn][gl] << " RLDA: "<< HmaxRLDA[Sn][gl] << "\n";
    }//gl
    
    }// ::allfiles
    
    

