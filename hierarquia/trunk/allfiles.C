

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
  cerr << "\nEstatísticas dos Clusters...";
  
  
  for(int k = 0; k < Sn; k++)
  {
    string DATA  = DataMod(k,clus);
    Magic[k] = Simplex ( MODEL, DATA.c_str() )*(T[k] - 1);
    
    for(int i = 0; i < GLmax(T[k]); i++)
    {
      LBproof( round(Magic[k]/(i+1),PLB_PRECISION), (i+1), k, clus );
      DATA = DataMod(k, clus, HmaxLB[k][(i+1)], (i+1));
      HmaxHLDA[k][(i+1)] = HLDA( DATA.c_str(), (i+1), k );
//       cout << "\n LB provado = " << HmaxLB[k][(i+1)] << "\tIterações: " << HmaxLBi[k][(i+1)] << "\n\n";
      Statistica(DATA.c_str(), (i+1), k);
//       cout << "\n Média: " << HmaxM[k][(i+1)] << " amostra: " << HmaxMn[k][(i+1)] << " Desvio padrão: " << HmaxD[k][(i+1)] << " amostra: "<< HmaxDn[k][(i+1)] << " RLDA: "<< HmaxRLDA[k][(i+1)] << "\n";
    }//i
    }//j
//     cout << "\n backbone!\n\n";
    
    //sprintf(clus, "backbone");
    cerr << "\n\nEstatísticas do Backbone...";
    
    string DATA  = DataMod(Sn);
    Magic[Sn] = Simplex ( MODEL, DATA.c_str() )*(T[Sn] - 1);
    
    for(int i = 0; i < GLmax(T[Sn]); i++)
    {
      LBproof( round(Magic[Sn]/(i+1),PLB_PRECISION), (i+1), Sn );
      DATA  = DataMod(Sn, "backbone", HmaxLB[Sn][(i+1)], (i+1));
      HmaxHLDA[Sn][(i+1)] = HLDA( DATA.c_str(), (i+1), Sn);
//       cout << "\n LB provado = " << HmaxLB[Sn][(i+1)] << "\tIterações: " << HmaxLBi[Sn][(i+1)] << "\n\n";
      Statistica(DATA.c_str(), (i+1), Sn);
//       cout << "\n Média: " << HmaxM[Sn][(i+1)] << " amostra: " << HmaxMn[Sn][(i+1)] << " Desvio padrão" << HmaxD[Sn][(i+1)] << " amostra: " << HmaxDn[Sn][(i+1)] << " RLDA: "<< HmaxRLDA[Sn][(i+1)] << "\n";
    }//i
    
    ostringstream oss;
    oss << "data/N" << NTOWNS << ".I" << Inst << ".s" << seed << "/" << NTOWNS << ".I" << Inst << ".s" << seed << ".statistics";
    string dir = oss.str();
    
    ofstream file( dir.c_str() );
    
    if (file.is_open())
    {
      file << "k ";
      file << "T[k] ";
      file << "gl ";
      file << "Mn\t";
      file << "Dn\t";
      file << "LB\t";
      file << "HLDA\t";
      file << "RLDA\t";
      file << "Ma\t";
      file << "M\t";
      file << "D\t";

      for (int k = 0; k <= Sn; k++)
      {
	for(int gl = 1; gl <= GLmax(T[k]); gl++)
	{
	  file << "\n";
	  file << (k+1)%(Sn+1) << " ";
	  file << T[k] << "    ";
	  file << gl << setprecision(4) << "  ";
	  file << HmaxMn[k][gl] << "\t";
	  file << HmaxDn[k][gl] << "\t";
	  file << HmaxLB[k][gl] << "\t";
	  file << HmaxHLDA[k][gl] << "\t";
	  file << HmaxRLDA[k][gl] << "\t";
	  file << HmaxMaxA[k][gl] << "\t";
	  file << HmaxM[k][gl] << "\t";
	  file << HmaxD[k][gl] << "\t";
	}
      }

      file.close();
    }
    
    }// ::allfiles
    
    

