

// Chama o HLDA o RLDA e estima as médias.
void rede::allfiles()
{
  const char* MODEL = HmaxMagic_MODEL.c_str();
  const char* clus = "cluster";
  //cout << "\n allfiles!\n\n";
  //sprintf(MODEL, HmaxMagic_MODEL);
  cout << "\n cluster!\n\n";
  //sprintf(clus, "cluster");
  
  for(int k = 0; k < Sn; k++)
  {
    string DATA  = DataMod(k,clus);
    Magic[k] = Simplex ( MODEL, DATA.c_str() )*(T[k] - 1);
    
    for(int i = 0; i < GLmax(T[k]); i++)
    {
      LBproof( round(Magic[k]/(i+1),PLB_PRECISION), (i+1), k, clus );
      DATA = DataMod(k, clus, HmaxLB[k][(i+1)], (i+1));
      HmaxHLDA[k][(i+1)] = HLDA( DATA.c_str(), (i+1), k );
      cout << "\n LB provado = " << HmaxLB[k][(i+1)] << "\tIterações: " << HmaxLBi[k][(i+1)] << "\n\n";
      Statistica(DATA.c_str(), (i+1), k);
      cout << "\n Média: " << HmaxM[k][(i+1)] << " amostra: " << HmaxMn[k][(i+1)] << " Desvio padrão: " << HmaxD[k][(i+1)] << " amostra: "<< HmaxDn[k][(i+1)] << " RLDA: "<< HmaxRLDA[k][(i+1)] << "\n";
    }//i
    }//j
    cout << "\n backbone!\n\n";
    
    //sprintf(clus, "backbone");
    
    string DATA  = DataMod(Sn);
    Magic[Sn] = Simplex ( MODEL, DATA.c_str() )*(T[Sn] - 1);
    
    for(int i = 0; i < GLmax(T[Sn]); i++)
    {
      LBproof( round(Magic[Sn]/(i+1),PLB_PRECISION), (i+1), Sn );
      DATA  = DataMod(Sn, "backbone", HmaxLB[Sn][(i+1)], (i+1));
      HmaxHLDA[Sn][(i+1)] = HLDA( DATA.c_str(), (i+1), Sn);
      cout << "\n LB provado = " << HmaxLB[Sn][(i+1)] << "\tIterações: " << HmaxLBi[Sn][(i+1)] << "\n\n";
      Statistica(DATA.c_str(), (i+1), Sn);
      cout << "\n Média: " << HmaxM[Sn][(i+1)] << " amostra: " << HmaxMn[Sn][(i+1)] << " Desvio padrão" << HmaxD[Sn][(i+1)] << " amostra: " << HmaxDn[Sn][(i+1)] << " RLDA: "<< HmaxRLDA[Sn][(i+1)] << "\n";
    }//i
    
    }// ::allfiles
    
    

