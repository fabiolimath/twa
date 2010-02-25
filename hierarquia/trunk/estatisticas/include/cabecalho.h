
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/distributions/students_t.hpp>
#include <iomanip>
using namespace boost::math;
using namespace std;
using boost::math::normal; // typedef provides default type is double.
using std::cout; using std::endl; using std::left; using std::showpoint; using std::noshowpoint;
using std::setw; using std::setprecision;
#include <limits>
using std::numeric_limits;

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
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <vector>
using std::vector;

#define cout STD_COUT
#define cerr STD_CERR
#define endl STD_ENDL
#define ostream STD_OSTREAM
#define ifstream STD_IFSTREAM
#define ofstream STD_OFSTREAM

// extern "C" {
  #include <glpk.h>
// }

#include "ram.h"

#include "matrix.h"

