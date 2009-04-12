
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stdio.h>

#define cout STD_COUT
#define cerr STD_CERR
#define endl STD_ENDL
#define ostream STD_OSTREAM
#define ifstream STD_IFSTREAM
#define ofstream STD_OFSTREAM


float **new_matrix_float (int m, int n) ;
float **del_matrix_float (int m, int n, float **v);
double **new_matrix_double (int m, int n) ;
double **del_matrix_double (int m, int n, double **v);

int **new_matrix_int (int m, int n) ;

float ***new_cube_float (int l, int m, int n) ;

float ***del_cube_float (int l, int m, int n, float ***v) ;

double ***new_cube_double (int l, int m, int n) ;

double ***del_cube_double (int l, int m, int n, double ***v) ;

int **del_matrix_int (int m, int n, int **v);

char **new_matrix_char (int m, int n) ;

char **del_matrix_char (int m, int n, char **v);

