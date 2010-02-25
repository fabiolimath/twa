/*#ifdef __cplusplus
extern "C" {
  #endif*/
/*  #ifndef RAM_H
  #define RAM_H*/
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #define STR 32
  
  typedef float elem;
  
  typedef struct matrix {
    int lin, col;
    elem **data;
  } *tmatrix;
  
  /* ProtÃ³tipos */
/* Essa funÃ§Ã£o aloca uma estrutura de dados matrix de tamanho lin x col, preenche os respectivos campos de linha e coluna. */
tmatrix makeMatrix(int lin, int col);

/* Essa funÃ§Ã£o retorna o nÃºmero de linhas que a matriz da estrutura de dados matrix contÃ©m. */
int getLines(tmatrix m);

/* Essa funÃ§Ã£o retorna o nÃºmero de colunas que a matriz da estrutura de dados matrix contÃ©m. */
int getCols(tmatrix m);

/* Essa funÃ§Ã£o retorna o elemento de posiÃ§Ã£o i, j na matriz da estrutura de dados matrix. */
elem getData(tmatrix m, int lin, int col);

/* Essa funÃ§Ã£o altera o elemento de posiÃ§Ã£o lin x col na matriz da estrutura de dados matrix, pelo elemento passado como parÃ¢metro. */
void setData(tmatrix m, int lin, int col, elem data);

/* Essa funÃ§Ã£o copia a matriz src, para a matriz des. */
void copyMatrix(tmatrix src, tmatrix des);

/* Essa funÃ§Ã£o compara se duas matrizes sÃ£o iguais. */
int equalMatrix(tmatrix m1, tmatrix m2);

/* Essa funÃ§Ã£o preenche toda a matriz da estrutura de dados com o elemento passado como parÃ¢metro. */
void fill(tmatrix m, elem f);

/* Essa funÃ§Ã£o libera a memÃ³ria ocupada pela estrutura de dados matrix. */
void destroyMatrix(tmatrix m);

/* Essa funÃ§Ã£o imprime a matriz da estrutura de dados na tela. */
void printMatrix(tmatrix m, int prec);

/* Essa funÃ§Ã£o escreve no arquivo o numero de nÃ³s da contÃ©m a matriz, nescessÃ¡rio para o glpk */
void writeMatrixNumNodes(char *fileName, tmatrix m, char *param);

/* Essa funÃ§Ã£o salva a estrutura de dados matrix em um arquivo no formato MathProg. */
void writeMatrix(char *fileName, tmatrix m, int prec, int max_elem, char *param);

/* Essa funÃ§Ã£o lÃª a matriz de um arquivo, no formato MathProg. Aloca e preenche a estrutura de dados, e retorna um ponteiro para a mesma. */
tmatrix readMatrix(char *fileName);

/* Essa funÃ§Ã£o imprime "end;" no arquivo. */
void endFile(char *fileName);

/* Prot�tipos */
/* Heur�sticas [Ram96] */
tmatrix hlda(tmatrix m, tmatrix mat_traff, int degree);
tmatrix mlda(tmatrix m, tmatrix mat_dist, tmatrix mat_traff, int degree);
tmatrix tilda(tmatrix m, tmatrix mat_dist, int degree);
tmatrix rlda(tmatrix m, int degree,unsigned int seed);

/* Varia��es */
/* rlda [ram96] com o anel b�sico. */
tmatrix rldaRing(tmatrix m, int degree);
/* rlda gerando degree an�is b�sicos e sobrepondo na matriz. */
tmatrix rldaRings(tmatrix m, int degree);
/* rlda gerando um anel b�sico e deslocando degree vezes um n�mero aleat�rio de colunas e zerando a diagonal principal. */
tmatrix rldaDisplace(tmatrix m, int degree);
/*
#ifdef __cplusplus
}
#endif*/
// #endif

