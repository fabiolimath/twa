

// Cria o data.mod e retorna o nome do arquivo.
string rede::DataMod(int k, const char* s = "backbone", double HmaxLB = 0, int gl = 0, int DemOnly = 0)
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
    sprintf (filename, "data/N%d.I%d.s%d/data.N%d.I%d.s%d.%s%d.T%d.GL%d.mod",NTOWNS,Inst,seed,NTOWNS,Inst,seed, s,(k+1)%(Sn+1),T[k],gl);
  }
  
  ostringstream oss;
  oss << "mkdir -p data/N" << NTOWNS << ".I" << Inst << ".s" << seed;
  string dir = oss.str();
  system( dir.c_str() );
  
  ofstream file(filename);
  
  if (file.is_open())
  {
    if (DemOnly == 0)
    {
      file << "\n# " << s << " " << (k+1)%(Sn+1) << ":\n# ";
      for(int i=0; i<T[k]; i++)
	file << cluster[k][i] << " ";
      file << "\n\n";
      
      file << "data;\n\n";
      file << "# Número de nós.\n";
      file << "param N  := " << T[k] << ";\n";
      file << "\n";
      
      if (HmaxLB != 0) file << "param HmaxLB := " << HmaxLB << ";\n";
      if (gl != 0) file << "param gl := " << gl << ";\n";
      
      file << "# Matriz de Demandas.\n";
      
    }
    file << "param D : ";
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
    
    if (DemOnly == 0)
    {
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
      
      file << "\nend;\n";
    }
    
    file.close();
    
  }//if (file.is_open())
  //cout << "\n DataMod out!\n\n";
  
  string DATA(filename);
  return DATA;
  
}// ::DataMod()









