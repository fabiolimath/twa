

// Chama o HLDA o RLDA e estima as médias.
void rede::allfiles(int argc, char** argv)
{
  const char* MODEL = HmaxMagic_MODEL.c_str();
  const char* clus = "cluster";
  //cout << "\n allfiles!\n\n";
  //sprintf(MODEL, HmaxMagic_MODEL);
//   cout << "\n cluster!\n\n";
  //sprintf(clus, "cluster");
  Iniciar( argc, argv );	// Inicializa a instancia, gera as matrizes de demandas e distancias e seta a semente do genético.
  cerr << "\nEvolução...\n\n";
  Evolve( argc, argv );	// Executa o genético.
  SeparaMatrizes();		// Separa as matrizes de demandas e distancias dos clusters e do backbone.
  WriteTamanhos();
  WriteClusters();
  WriteFitness();
  
  
  ostringstream oss;
  oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".statistics";
  string dir = oss.str();
  
  ofstream file( dir.c_str() );
  
  if (file.is_open())
  {
    file << "k ";
    file << "T[k]\t";
    file << "gl ";
    file << "Time\t";
    file << "Mn\t";
    file << "Dn\t";
    file << "LBi\t";
    file << "LB\t";
    file << "HLDA\t";
    file << "RLDA\t";
    file << "Ma\t";
    file << "M\t";
    file << "D\t";
    
    file.close();
  }
  
  cerr << "\nEstatísticas dos Clusters...";
  
  for(int k = 0; k < Sn; k++)
  {
    string DATA  = DataMod(k,clus);
    Magic[k] = Simplex ( MODEL, DATA.c_str() )*(T[k] - 1);
    
    for(int gl = 1; gl <= GLmax(T[k]); gl++)
    {
      LBproof( round(Magic[k]/gl,PLB_PRECISION), gl, k, clus );
      DATA = DataMod(k, clus, HmaxLB[k][gl-1], gl);
      HmaxHLDA[k][gl-1] = HLDA( DATA.c_str(), gl, k );
//       cout << "\n LB provado = " << HmaxLB[k][gl] << "\tIterações: " << HmaxLBi[k][gl] << "\n\n";
      Statistica(DATA.c_str(), gl, k);
//       cout << "\n Média: " << HmaxM[k][gl] << " amostra: " << HmaxMn[k][gl] << " Desvio padrão: " << HmaxD[k][gl] << " amostra: "<< HmaxDn[k][gl] << " RLDA: "<< HmaxRLDA[k][gl] << "\n";
    }//i
    }//j
//     cout << "\n backbone!\n\n";
    
    //sprintf(clus, "backbone");
    cerr << "\n\nEstatísticas do Backbone...";
    
    string DATA  = DataMod(Sn);
    Magic[Sn] = Simplex ( MODEL, DATA.c_str() )*(T[Sn] - 1);
    
    for(int gl = 1; gl <= GLmax(T[Sn]); gl++)
    {
      LBproof( round(Magic[Sn]/gl,PLB_PRECISION), gl, Sn );
      DATA  = DataMod(Sn, "backbone", HmaxLB[Sn][gl-1], gl);
      HmaxHLDA[Sn][gl-1] = HLDA( DATA.c_str(), gl, Sn);
//       cout << "\n LB provado = " << HmaxLB[Sn][gl] << "\tIterações: " << HmaxLBi[Sn][gl] << "\n\n";
      Statistica(DATA.c_str(), gl, Sn);
//       cout << "\n Média: " << HmaxM[Sn][gl] << " amostra: " << HmaxMn[Sn][gl] << " Desvio padrão" << HmaxD[Sn][gl] << " amostra: " << HmaxDn[Sn][gl] << " RLDA: "<< HmaxRLDA[Sn][gl] << "\n";
    }//i
    
    }// ::allfiles
    
    

