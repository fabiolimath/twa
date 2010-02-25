

// Cria o data.mod e retorna o nome do arquivo.
string rede::DataMod(int k, int gl = 0, const char* s = "backbone", double HmaxLB = 0, double FTnetLB = 0, int W = 0, double HmaxM = 0, double FTnetM = 0)
{
  //cout << "\n DataMod in!\n\n";
  
  char filename[250];
  
  if (gl==0)
  {
    sprintf (filename, "data/N%d.I%d.s%d/data.N%d.I%d.s%d.%s%d.T%d.mod",NTOWNS,Inst,seed,NTOWNS,Inst,seed, s,(k+1)%(Sn+1),T[k]);
    //cout << "\n filename!: "<< filename <<"\n\n";
    
  }
  else
  {
    if ( W==0 ) 
	 {
		sprintf (filename, "data/N%d.I%d.s%d/data.N%d.I%d.s%d.%s%d.T%d.GL%d.mod",NTOWNS,Inst,seed,NTOWNS,Inst,seed, s,(k+1)%(Sn+1),T[k],gl);
	 }
	 else
	 {
		sprintf (filename, "data/N%d.I%d.s%d/data.N%d.I%d.s%d.%s%d.T%d.GL%d.W%d.mod",NTOWNS,Inst,seed,NTOWNS,Inst,seed, s,(k+1)%(Sn+1),T[k],gl,W);
	 }
  }
  
  ostringstream oss;
  oss << "mkdir -p data/N" << NTOWNS << ".I" << Inst << ".s" << seed;
  string dir = oss.str();
  system( dir.c_str() );
  
  ofstream file(filename);
  
  if (file.is_open())
  {
	 file << "\n# " << s << " " << (k+1)%(Sn+1) << " :\n# ";
	 for(int i=0; i<T[k]; i++)
	 file << cluster[k][i] << " ";
	 file << "\n\n";
	 
	 file << "data;\n\n";
	 file << "# N�mero de n�s.\n";
	 file << "param N  := " << T[k] << " ;\n" ;
	 file << "\n" ;
	 
	 if (gl != 0) file << "param gl := " 		<< gl	 		<< " ;\n" ;
	 if (W  != 0) file << "param Wc := "		<< W			<< " ;\n" ;
	 
/*	 if (HmaxLB != 0) file << "param HmaxLB := " 	<< HmaxLB 		<< " ;\n" ;
	 if (W  != 0) file << "param HmaxM := "		<< HmaxM  		<< " ;\n" ;
	 if (W  != 0) file << "param HmaxD := "		<< HmaxD[k][gl - 1]	<< " ;\n" ;
	 if (W  != 0) file << "param HmaxRLDA := "	<< HmaxRLDA[k][gl - 1]	<< " ;\n" ;
	 if (W  != 0) file << "param HmaxHLDA := "	<< HmaxHLDA[k][gl - 1]	<< " ;\n" ;
	 if (W  != 0) file << "param HmaxMaxA := "	<< HmaxMaxA[k][gl - 1]	<< " ;\n" ;

	 if (FTnetLB  != 0) file << "param FTnetLB := " << FTnetLB  		<< " ;\n" ;
	 if (W  != 0) file << "param FTnetM := "	<< FTnetM		<< " ;\n" ;
	 if (W  != 0) file << "param FTnetD := "	<< FTnetD[k][gl - 1]	<< " ;\n" ;
	 if (W  != 0) file << "param FTnetRLDA := "	<< FTnetRLDA[k][gl - 1]	<< " ;\n" ;
	 if (W  != 0) file << "param FTnetMaxA := "	<< FTnetMaxA[k][gl - 1]	<< " ;\n" ;*/
	 
	 file << "# Matriz de Demandas.\n" ;

	 file << "param D : " ;
    for(int i = 1; i <= T[k]; i++) file << " " << i << " ";
    file << " :=\n";
    
    for(int i=0; i<T[k]; i++)
    {
      file << (i+1) << " ";
      if((i+1)<10){file << " ";}
      for(int j=0; j<T[k];j++)
      {
			file << demS[k][i][j] << " ";
      }//j
      file << "\n" ;
    }//i
    
	 file << ";\n\n" ;
	 
	 file << "# Matriz de Distancias.\n";
	 file << "param C : ";
	 for(int i = 1; i <= T[k]; i++) file << " " << i << " ";
	 file << " :=\n";
	 
	 for(int i=0; i<T[k]; i++)
	 {
		 file << (i+1) << " ";
		 if((i+1)<10){file << " ";}
		 for(int j=0; j<T[k];j++)
		 {
			file << distS[k][i][j] << " ";
		 }//j
		 file << "\n" ;
	 }//i
	 file << ";\n" ;
	 
// 	 file << "\nend;\n";
    
    
    file.close();
    
  }//if (file.is_open())
  //cout << "\n DataMod out!\n\n";
  
  string DATA(filename);
  return DATA;
  
}// ::DataMod()









