
#include "include/ram.h"
// #include "include/cabecalho.h"
#include <ga/garandom.h>


/* Funções auxiliares */
/* Essa função retorna o número de caracteres que é preciso para escrever algum número. */
int align(elem data){
  int i;
  for(i=0;data>1;i++){
    data /= 10;
  }
  return i;
}
/* Retorna o ultimo número da linha de um arquivo. */
int getLastNumberLine(FILE *arq){
  int i;
  char c, last, str[STR];
  last = 0;
  do{
    c = fgetc(arq);
    if((c>='0')&&(c<='9')){
      if(last==0){
	i = 0;
	last = 1;
      }
      str[i++] = c;
    }
    else
      last = 0;
  }while((c!='\n')&&(c!=EOF));
  str[i]='\0';
  return atoi(str);
}

/* Funções de interface */
tmatrix makeMatrix(int lin, int col){
  int i;
  tmatrix m;
  m = (tmatrix)malloc(sizeof(struct matrix));
  if(!m)
    exit(-1);
  m->lin = lin;
  m->col = col;
  m->data = (elem **)malloc(sizeof(elem *)*lin);
  if(!m->data)
    exit(-1);
  for(i=0;i<lin;i++){
    m->data[i] = (elem *)malloc(sizeof(elem)*col);
    if(!m->data[i])
      exit(-1);
  }
  return m;
}

int getLines(tmatrix m){
  return m->lin;
}

int getCols(tmatrix m){
  return m->col;
}

elem getData(tmatrix m, int i, int j){
  return m->data[i][j];
}

void setData(tmatrix m, int i, int j, elem data){
  m->data[i][j] = data;
}

void copyMatrix(tmatrix src, tmatrix des){
  int i, j, lin, col;
  lin = getLines(src);
  col = getCols(src);
  if((lin==getLines(des))&&(col==getCols(des)))
    for(i=0;i<lin;i++)
      for(j=0;j<col;j++)
	setData(des, i, j, getData(src, i, j));
}

int equalMatrix(tmatrix m1, tmatrix m2){
  int i, j, lin, col;
  lin = getLines(m1);
  col = getCols(m1);
  if((lin==getLines(m2))&&(col==getCols(m2)))
    for(i=0;i<lin;i++){
      for(j=0;j<col;j++)
	if(getData(m1, i, j)!=getData(m2, i, j))
	  return 0;
    }
    else
      return 0;
    return 1;
}

void fill(tmatrix m, elem data){
  int i, j;
  for(i=0;i<m->lin;i++)
    
    for(j=0;j<m->col;j++)
      m->data[i][j] = data;
}

void destroyMatrix(tmatrix m){
  int i;
  for(i=0;i<m->lin;i++)
    free(m->data[i]);
  free(m->data);
  free(m);
}

void printMatrix(tmatrix m, int prec){
  int i, j;
  char strfmt[STR];
  sprintf(strfmt, "%%.%df ", prec);
  for(i=0;i<m->lin;i++){
    for(j=0;j<m->col;j++)
      printf(strfmt, getData(m, i, j));
    printf("\n");
  }
  printf("\n");
}

tmatrix readMatrix(char *fileName){
  FILE *arq;
  int num, i, j;
  tmatrix m;
  elem x;
  arq = fopen(fileName, "r");
  if(!arq)
    exit(-1);
  num = getLastNumberLine(arq);
  fgetc(arq);
  fgetc(arq);
  m = makeMatrix(num, num);
  fill(m, 0);
  for(i=0;i<num;i++){
    fscanf(arq, "%f", &x);
    for(j=0;j<num;j++){
      fscanf(arq, "%f", &x);
      setData(m, i, j, x);
    }
  }
  fclose(arq);
  return m;
}

void writeMatrixNumNodes(char *fileName, tmatrix m, char *param){
  FILE *arq;
  arq = fopen(fileName, "a");
  if(!arq)
    exit(-1);
  fprintf(arq, "param %s := %d;\n", param, getLines(m));
  fclose(arq);
}

void writeMatrix(char *fileName, tmatrix m, int prec, int max_elem, char *param){
  int i, j;
  char strfmt[STR], num[STR], p[STR];
  FILE *arq;
  
  arq = fopen(fileName, "a");
  if(!arq)
    exit(-1);
  sprintf(strfmt, "%%%d.%df ", align(max_elem)+prec+1, prec);
  sprintf(num, "%%%dd ", align(max_elem)+prec+1);
  sprintf(p, "param %s : ", param);
  
  fprintf(arq, "%s", p);
  for(j=0;j<m->col;j++)
    fprintf(arq, num, j+1);
  fprintf(arq, "\n:=");
  for(i=0;i<m->lin;i++){
    if(i==0)
      sprintf(p, "%%%dd ", strlen(param)+6);
    else
      sprintf(p, "%%%dd ", strlen(param)+8);
    fprintf(arq, p, i+1);
    for(j=0;j<m->col;j++)
      fprintf(arq, strfmt, getData(m, i, j));
    fprintf(arq, "\n");
  }
  fprintf(arq, ";\n");
  fclose(arq);
}

void endFile(char *fileName){
  FILE *arq;
  
  arq = fopen(fileName, "a");
  if(!arq)
    exit(-1);
  fprintf(arq, "end;\n");
  fclose(arq);
}


/* Funções auxiliares */
/* Cria e aloca aleatóriamente um anel básico */
tmatrix makeRing(int size){
  tmatrix ring;
  int i, rnd;
  elem aux;
  ring = makeMatrix(1, size);
  for(i=0;i<size;i++)
    setData(ring, 0, i, i);
  for(i=0;i<size;i++){
    rnd = (rand()%(size-1))+1;
    aux = getData(ring, 0, rnd);
    setData(ring, 0, rnd, getData(ring, 0, i));
    setData(ring, 0, i, aux);
  }
  return ring;
}

/* Transpõe um anel básico para a matriz de topologia virtual */
void pasteRing(tmatrix m, tmatrix ring, int displace){
  int i, len;
  len = getCols(ring);
  for(i=0;i<len-1;i++)
    setData(m, getData(ring, 0, i), ((int)getData(ring, 0, (i+1))+displace)%len, 1);
  setData(m, getData(ring, 0, i), ((int)getData(ring, 0, 0)+displace)%len, 1);
}

/* Retorna uma matriz de adjacencia a partir de uma matriz de distâncias */
tmatrix makeMatrixAdj(tmatrix m){
  int i, j, ord;
  ord = getLines(m);
  for(i=0;i<ord;i++)
    for(j=0;j<ord;j++)
      if(getData(m, i, j))
	setData(m, i, j, 1);
      else
	setData(m, i, j, 0);
      return m;
}

/* Preenche uma matriz de topologia virtual totalmente transparente */
void makeMatrixFull(tmatrix m){
  int i;
  fill(m, 1);
  for(i=0;i<getLines(m);i++)
    setData(m, i, i, 0);
}

/* Retorna o resultado da soma de uma linha da matriz */
elem sumLin(tmatrix m, int lin){
  int i, sum=0;
  for(i=0;i<getCols(m);i++)
    sum += getData(m, lin, i);
  return sum;
}

/* Retorna o resultado da soma de uma coluna da matriz */
elem sumCol(tmatrix m, int col){
  int i, sum=0;
  for(i=0;i<getLines(m);i++)
    sum += getData(m, i, col);
  return sum;
}

/* Preenche o vetor max_demand, que deve ser de 4 posições, com: [0][1] Valor da maior demanda;
[0][2] Linha da maior demanda;
[0][3] Coluna da maior demanda;
[0][4] Valor da segunda maior demanda.*/
void getMaxTraffic(tmatrix m, tmatrix max_demand){
  int i, j, nodes;
  fill(max_demand, 0);
  nodes = getLines(m);
  for(i=0;i<nodes;i++)
    for(j=0;j<nodes;j++){
      if(getData(max_demand, 0, 0) < getData(m, i, j)) {
	setData(max_demand, 0, 3, getData(max_demand, 0, 0));
	setData(max_demand, 0, 0, getData(m, i, j));
	setData(max_demand, 0, 1, i);
	setData(max_demand, 0, 2, j);
      } else {
	if(getData(max_demand, 0, 3) < getData(m, i, j))
	  setData(max_demand, 0, 3, getData(m, i, j));
      }
    }
}

/* Funções de interface */
/* Heurísticas [Ram96] */
tmatrix rlda(tmatrix m, int degree){
  int i, j, k, lin, col, nodes;
  char flag;
  tmatrix lin_ring, col_ring, lin_degree, col_degree;
  nodes = getLines(m);
  lin_degree = makeMatrix(nodes, 1);
  col_degree = makeMatrix(1, nodes);
  for(k=0;k<nodes;k++){
    setData(lin_degree, k, 0, sumLin(m, k));
    setData(col_degree, 0, k, sumCol(m, k));
  }
  lin_ring = makeRing(nodes);
  col_ring = makeRing(nodes);
  for(i=0;i<nodes;i++){
    lin = getData(lin_ring, 0, i);
    for(j=0;j<degree;j++){
      flag = 0;
      k=0;
      while((k<nodes)&&(flag==0)){
	col = getData(col_ring, 0, k);
	if((lin!=col)&&(getData(col_degree, 0, col)<degree)&&(getData(lin_degree, lin, 0)<degree)&&(getData(m, lin, col)<1)){
	  setData(m, lin, col, 1);
	  setData(lin_degree, lin, 0, (getData(lin_degree, lin, 0)+1));
	  setData(col_degree, 0, col, (getData(col_degree, 0, col)+1));
	  flag=1;
	}
	k++;
      }
    }
  }
  destroyMatrix(lin_ring);
  destroyMatrix(col_ring);
  destroyMatrix(lin_degree);
  destroyMatrix(col_degree);
  return m;
}

tmatrix hlda(tmatrix m, tmatrix mat_traff, int degree){
  tmatrix aux, max_demand, lin_degree, col_degree;
  int i, nodes, lin, col;
  nodes = getLines(m);
  if(nodes!=getLines(mat_traff))
    exit(-1);
  lin_degree = makeMatrix(nodes, 1);
  col_degree = makeMatrix(1, nodes);
  for(i=0;i<nodes;i++){
    setData(lin_degree, i, 0, sumLin(m, i));
    setData(col_degree, 0, i, sumCol(m, i));
  }
  aux = makeMatrix(nodes, nodes);
  copyMatrix(mat_traff, aux);
  max_demand = makeMatrix(1,4);
  getMaxTraffic(aux, max_demand);
  while(1){
    if(getData(max_demand, 0, 0)>0.0f){
      lin = (int)getData(max_demand, 0, 1);
      col = (int)getData(max_demand, 0, 2);
      if((getData(col_degree, 0, getData(max_demand, 0, 2))<degree)&&(getData(lin_degree, getData(max_demand, 0, 1), 0)<degree)){
	setData(m, lin, col, (getData(m, lin, col)+1));
	setData(lin_degree, lin, 0, (getData(lin_degree, lin, 0)+1));
	setData(col_degree, 0, col, (getData(col_degree, 0, col)+1));
	setData(aux, lin, col, (getData(max_demand, 0, 0)-getData(max_demand, 0, 3)));
      } else {
	setData(aux, lin, col, 0);
      }
      setData(max_demand, 0, 0, (getData(max_demand, 0, 0)-getData(max_demand, 0, 3)));
      getMaxTraffic(aux, max_demand);
    } else {
      destroyMatrix(max_demand);
      destroyMatrix(aux);
      destroyMatrix(lin_degree);
      destroyMatrix(col_degree);
      return rlda(m, degree);
    }
  }
}

tmatrix mlda(tmatrix m, tmatrix mat_dist, tmatrix mat_traff, int degree){
  copyMatrix(makeMatrixAdj(mat_dist), m);
  return hlda(m, mat_traff, degree);
}

tmatrix tilda(tmatrix m, tmatrix mat_dist, int degree){
  int i, j, k, nodes, lin, col, col_aux;
  tmatrix lin_degree, col_degree, ring_aux, ring_lin, ring_col;
  nodes = getLines(m);
  if(nodes<=degree+1){
    makeMatrixFull(m);
    return m;
  }
  copyMatrix(makeMatrixAdj(mat_dist), m);
  nodes = getLines(m);
  lin_degree = makeMatrix(nodes, 1);
  col_degree = makeMatrix(1, nodes);
  for(i=0;i<nodes;i++){
    setData(lin_degree, i, 0, sumLin(m, i));
    setData(col_degree, 0, i, sumCol(m, i));
  }
  ring_lin = makeRing(nodes);
  ring_col = makeRing(nodes);
  
  
  for(i=0;i<nodes;i++){
    lin = getData(ring_lin, 0, i);
    for(j=0;j<nodes;j++){
      col = getData(ring_col, 0, j);
      if(getData(mat_dist, lin, col)){
	ring_aux = makeRing(nodes);
	for(k=0;k<nodes;k++){
	  col_aux = getData(ring_aux, 0, k);
	  if((lin!=col_aux)&&(getData(m, col, col_aux))&&(!getData(m, lin, col_aux))&&(getData(lin_degree, lin, 0)<degree)&&(getData(col_degree, 0, col_aux)<degree)){
	    setData(m, lin, col_aux, 1);
	    setData(lin_degree, lin, 0, (getData(lin_degree, lin, 0)+1));
	    setData(col_degree, 0, col_aux, (getData(col_degree, 0, col_aux)+1));
	  }
	}
      }
    }
  }
  
  destroyMatrix(ring_lin);
  destroyMatrix(ring_col);
  destroyMatrix(ring_aux);
  destroyMatrix(lin_degree);
  destroyMatrix(col_degree);
  return m;
}

/* Variações do rlda */
tmatrix rldaRing(tmatrix m, int degree){
  int nodes;
  tmatrix ring;
  nodes = getLines(m);
  if(nodes<=degree+1){
    makeMatrixFull(m);
    return m;
  }
  ring = makeRing(nodes);
  pasteRing(m, ring, 0);
  destroyMatrix(ring);
  rlda(m, degree);
  return m;
}

tmatrix rldaRings(tmatrix m, int degree){
  tmatrix ring;
  int i, nodes;
  nodes = getLines(m);
  if(nodes<=degree+1){
    makeMatrixFull(m);
    return m;
  }
  for(i=0;i<degree;i++){
    ring = makeRing(nodes);
    pasteRing(m, ring, 0);
  }
  destroyMatrix(ring);
  return m;
}

tmatrix rldaDisplace(tmatrix m, int degree){
  tmatrix ring;
  int i, nodes;
  nodes = getLines(m);
  if(nodes<=degree+1){
    makeMatrixFull(m);
    return m;
  }
  ring = makeRing(nodes);
  while(degree>sumLin(m, 1))
    pasteRing(m, ring, rand());
  destroyMatrix(ring);
  for(i=0;i<nodes;i++)
    setData(m, i, i, 0);
  destroyMatrix(ring);
  return m;
}
