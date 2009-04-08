
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <iomanip>
using namespace boost::math;
using namespace std;

//#include <ga/GASStateGA.h>
#include <ga/GADemeGA.h>

#include <ga/GAListGenome.h>
#include <ga/garandom.h>
#include <ga/std_stream.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define cout STD_COUT
#define cerr STD_CERR
#define endl STD_ENDL
#define ostream STD_OSTREAM
#define ifstream STD_IFSTREAM
#define ofstream STD_OFSTREAM

/*
// You can use either edge recombination crossover or partial match crossover.
// Which one you select makes a HUGE difference in the performance of the
// genetic algorithm.  Only one of the two following lines should be commented.
//#define XOVER PMXover       // (Partial Match Crossover)
*/
#define XOVER ERXover         // (Edge Recombination Crossover)

void  remover(int, GAList<int>&);

float Objective(GAGenome&);
float conjestionamento(GAGenome&);
int   Mutator(GAGenome&, float);
void  Initializer(GAGenome&);
float Comparator(const GAGenome&, const GAGenome&); 
int   ERXover(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);
int   PMXover(const GAGenome&, const GAGenome&, GAGenome*, GAGenome*);
void  ERXOneChild(const GAGenome&, const GAGenome&, GAGenome*);


extern "C" {
  #include <glpk.h>
}

#include "ram.h"

#include "matrix.h"

