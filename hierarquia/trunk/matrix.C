#include "include/matrix.h"


float **new_matrix_float (int m, int n) {
  float **v; 						/* ponteiro para a matriz */
	int i; 							/* variavel auxiliar */

	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}
	
	/* aloca as linhas da matriz */
	v = (float **) calloc (m+1, sizeof(float *));
	if (v == NULL) {
	  printf ("** Erro: Memoria Insuficiente **");
	  return (NULL);
	}
	
	/* aloca as colunas da matriz */
	for ( i = 0; i <= m; i++ ) {
	  v[i] = (float*) calloc (n+1, sizeof(float));
	  if (v[i] == NULL) {
	    printf ("** Erro: Memoria Insuficiente **");
	    return (NULL);
	  }
	}
	
	return (v); /* retorna o ponteiro para a matriz */
}

float **del_matrix_float (int m, int n, float **v){
  int i; 							/* variavel auxiliar */

	if (v == NULL) return (NULL);
	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}
	
	for (i=0; i<=m; i++) free (v[i]); 			/* libera as linhas da matriz */

	free (v); /* libera a matriz */

	return (NULL); /* retorna um ponteiro nulo */
}

double **new_matrix_double (int m, int n) {
  double **v; 						/* ponteiro para a matriz */
	int i; 							/* variavel auxiliar */

	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}
	
	/* aloca as linhas da matriz */
	v = (double **) calloc (m+1, sizeof(double *));
	if (v == NULL) {
	  printf ("** Erro: Memoria Insuficiente **");
	  return (NULL);
	}
	
	/* aloca as colunas da matriz */
	for ( i = 0; i <= m; i++ ) {
	  v[i] = (double*) calloc (n+1, sizeof(double));
	  if (v[i] == NULL) {
	    printf ("** Erro: Memoria Insuficiente **");
	    return (NULL);
	  }
	}
	
	return (v); /* retorna o ponteiro para a matriz */
}

double **del_matrix_double (int m, int n, double **v){
  int i; 							/* variavel auxiliar */

	if (v == NULL) return (NULL);
	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}
	
	for (i=0; i<=m; i++) free (v[i]); 			/* libera as linhas da matriz */

	free (v); /* libera a matriz */

	return (NULL); /* retorna um ponteiro nulo */
}

int **new_matrix_int (int m, int n) {
  int **v; 						/* ponteiro para a matriz */
	int i; 							/* variavel auxiliar */

	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}
	
	/* aloca as linhas da matriz */
	v = (int **) calloc (m+1, sizeof(int *));
	if (v == NULL) {
	  printf ("** Erro: Memoria Insuficiente **");
	  return (NULL);
	}
	
	/* aloca as colunas da matriz */
	for ( i = 0; i <= m; i++ ) {
	  v[i] = (int*) calloc (n+1, sizeof(int));
	  if (v[i] == NULL) {
	    printf ("** Erro: Memoria Insuficiente **");
	    return (NULL);
	  }
	}
	
	return (v); /* retorna o ponteiro para a matriz */
}

float ***new_cube_float (int l, int m, int n) {
  
  float ***v; /* ponteiro para a matriz */
	
	v = new float**[l];
	
	for (int i = 0; i < l; ++i) {
	  v[i] = new float*[m];
	  
	  for (int j = 0; j < m; ++j)
	    v[i][j] = new float[n];
	}
	
	return (v); /* retorna o ponteiro para a matriz */
}

float ***del_cube_float (int l, int m, int n, float ***v) {
  
  for (int i = 0; i < l; ++i) {
    for (int j = 0; j < m; ++j)
      delete [] v[i][j];
    
    delete [] v[i];
  }
  delete [] v;
  
  return (NULL); /* retorna o ponteiro para a matriz */
}

int **del_matrix_int (int m, int n, int **v){
  int i; 							/* variavel auxiliar */

	if (v == NULL) return (NULL);
	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}
	
	for (i=0; i<=m; i++) free (v[i]); 			/* libera as linhas da matriz */

	free (v); /* libera a matriz */

	return (NULL); /* retorna um ponteiro nulo */
}

char **new_matrix_char (int m, int n) {
  char **v; 						/* ponteiro para a matriz */
	int i; 							/* variavel auxiliar */

	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}
	
	/* aloca as linhas da matriz */
	v = (char **) calloc (m+1, sizeof(char *));
	if (v == NULL) {
	  printf ("** Erro: Memoria Insuficiente **");
	  return (NULL);
	}
	
	/* aloca as colunas da matriz */
	for ( i = 0; i <= m; i++ ) {
	  v[i] = (char*) calloc (n+1, sizeof(char));
	  if (v[i] == NULL) {
	    printf ("** Erro: Memoria Insuficiente **");
	    return (NULL);
	  }
	}
	
	return (v); /* retorna o ponteiro para a matriz */
}

char **del_matrix_char (int m, int n, char **v){
  int i; 							/* variavel auxiliar */

	if (v == NULL) return (NULL);
	if (m < 1 || n < 1) { 					/* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}
	
	for (i=0; i<=m; i++) free (v[i]); 			/* libera as linhas da matriz */

	free (v); /* libera a matriz */

	return (NULL); /* retorna um ponteiro nulo */
}

