
#include "include/cabecalho.h"
#include "include/rede.h"

rede p;	// Define a instancia com escopo global.

int main(int argc, char** argv) {

  if(argc==1)
  {// Verifica se não forão passados os parâmetros e imprime a sintaxe.
    p.WriteSintaxe( argv[ 0 ] );
    return 0;
  }
  
  p.Iniciar( argc, argv );	// Inicializa a instancia, gera as matrizes de demandas e distancias e seta a semente do genético.
  p.Evolve( argc, argv );	// Executa o genético.
  p.SeparaMatrizes();		// Separa as matrizes de demandas e distancias dos clusters e do backbone.
  cout << "\n SeparaMatrizes!\n";
  p.WriteResumoGA( argv [ 0 ] );	// Imprime um resumo da instancia.
  p.WriteTamanhos();
  p.WriteClusters();
  p.WriteFitness();
  
  
  p.allfiles();
  cout << "\n writes!\n";
  
  cout << "Finalizado...\n\n";
  
  return 0;
}

 /*
  //############################################################################
  //############################################################################
  //############################################################################


// Here are the genome operators that we want to use for this problem.
// Thanks to Jan Kees IJspeert for isolating an order-of-evaluation problem
// in the previous implementation of this function.   */


float Objective(GAGenome& g) {
  GAListGenome<int> & gen = (GAListGenome<int> &)g;
    
  float score = 0;
  
  if(gen.head()) 
{ 
  score = p.Solucao(gen);
  
}//if(gen.head())

  return score;
}


void remover(int k, GAList<int>& g) {
  GAList<int> &child=(GAList<int> &)g;
  //static int a = 0;
  //static int b = child.size();
  //int m = (int)(b-a)/2;
  
  if(child.head()) {
    // 		if(k>(*child.warp(m))){
 // 			a = (m+1);
 // 			remover(k, child);
 // 		}
 // 		else {
   // 			if(k<(*child.warp(m))){
 // 				b = (m-1);
 // 				remover(k, child);
 // 			}
 // 		}
 for(int i=0; i<child.size(); i++){
   if(k==(*child.warp(i))){
     child.destroy();
     break;}
 }
  }
}


void Initializer(GAGenome& g) {
  GAListGenome<int> &child=(GAListGenome<int> &)g;
  while(child.head()) child.destroy(); 
  // destroy any pre-existing list
  
  int i,town;
  int gensize = p.GEN_SIZE;
  
  
  int *visit = new int[p.MAX_TOWNS];
  
  
  for(int i=0; i < p.MAX_TOWNS; i++){
    visit[i] = 0;
  }
  
  //memset(visit, 0, p.MAX_TOWNS*sizeof(int));
  
  town=GARandomInt(0,gensize-1);
  
  visit[town]=1;
  
  child.insert(town,GAListBASE::HEAD);
  // the head node
  
  for( i=1; i<gensize; i++) {
    do {
      town=GARandomInt(0,gensize-1);
    } while (visit[town]);
    visit[town]=1;
    child.insert(town);
  }		// each subsequent node 
  delete visit;
  
  
}


int Mutator(GAGenome& g, float pmut) {
  GAListGenome<int> &child=(GAListGenome<int> &)g;
  register int n, i;
  if ((GARandomFloat() >= pmut) || (pmut <= 0)) return 0;
  
  n = child.size();
  
  if (GARandomFloat()<0.5) {
    child.swap(GARandomInt(0,n-1),GARandomInt(0,n-1)); // swap only one time
  }
  else {
    int nNodes = GARandomInt(1,((int)(n/2-1)));       // displace nNodes 
    child.warp(GARandomInt(0,n-1));                   // with or without
    GAList<int> TmpList;                              // inversion
    for(i=0;i<nNodes;i++) {
      int *iptr = child.remove();
      TmpList.insert(*iptr,GAListBASE::AFTER);
      delete iptr;
      child.next();
    }
    int invert;
    child.warp(GARandomInt(0,n-nNodes));
    invert = (GARandomFloat()<0.5) ? 0 : 1;
    if (invert) TmpList.head(); else TmpList.tail();
    
    for(i=0;i<nNodes;i++) {
      int *iptr = TmpList.remove();
      child.insert(*iptr,GAListBASE::AFTER);
      delete iptr;
      if (invert) TmpList.prev(); else TmpList.next();
    }
  }
  child.head();		// set iterator to root node
  
  return (1);
}


int ERXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2) {
  int nc=0;
  if(c1) { ERXOneChild(g1,g2,c1); nc+=1; }
  if(c2) { ERXOneChild(g1,g2,c2); nc+=1; }
  
  return nc;
}


void ERXOneChild(const GAGenome& g1, const GAGenome& g2, GAGenome* c1) {
  GAListGenome<int> &mate1=(GAListGenome<int> &)g1;
  GAListGenome<int> &mate2=(GAListGenome<int> &)g2;
  GAListGenome<int> &sis=(GAListGenome<int> &)*c1;
  
  int i,j,k,t1,t2,town;
  
  
  char **CM;
  
  CM = new_matrix_char(p.MAX_TOWNS,p.MAX_TOWNS);
  int *visit = new int[p.MAX_TOWNS];
  
  for(int i=0; i < p.MAX_TOWNS; i++){
    visit[i] = 0;
    for(int j=0; j< p.MAX_TOWNS; j++){
      CM[i][j] = 0;
    }
  }
  
  
  //memset(CM, 0, p.MAX_TOWNS*p.MAX_TOWNS*sizeof(char));
  //memset(visit, 0, p.MAX_TOWNS*sizeof(int));
  
  
  while (sis.head()) sis.destroy();
  
  // create connection matrix
  mate1.head();
  
  
  for(j=0; j<p.GEN_SIZE; j++) {
    t1 = *mate1.current();
    t2 = *mate1.next();
    
    
    CM[t1][t2] = 1;
    CM[t1][t2] = 1;
    
    
  }
  
  
  mate2.head();
  for(j=0; j<p.GEN_SIZE; j++) {
    t1 = *mate2.current(); t2 = *mate2.next();
    CM[t1][t2]=1; CM[t2][t1]=1;
  }
  
  // select 1st town randomly
  town=GARandomInt(0,p.GEN_SIZE-1);
  visit[town]=1; 
  
  for(int i=0; i < p.MAX_TOWNS; i++){
    CM[town][i] = 0;
  }
  
  //memset(CM[town], 0, p.MAX_TOWNS*sizeof(char));
  
  sis.insert(town); // the head node 
  
  GAList<int> PossFollowList;
  GAList<int> FollowersList[5];
  while (PossFollowList.head()) PossFollowList.destroy();
  for(k=0; k<5; k++) {
    while (FollowersList[k].head()) FollowersList[k].destroy(); 
  }
  
  // select the following town with the minimal no of next folling towns
  int nPoss,nFollow;
  for(i=1; i<p.GEN_SIZE; i++) {           
    nPoss = 0;
    for(j=0; j<p.GEN_SIZE; j++) {          // no of poss. following towns
      if (CM[j][town]) {
	nPoss += 1;
	PossFollowList.insert(j);}
    }
    // nPoss = 0;
    if (nPoss == 0) {
      do {town=GARandomInt(0,p.GEN_SIZE-1);} while (visit[town]); // no follower
	visit[town]=1; 
	
	for(int i=0; i < p.MAX_TOWNS; i++){
	  CM[town][i] = 0;
	}
	
	//memset(CM[town], 0, p.MAX_TOWNS*sizeof(char));
	
	sis.insert(town); 
    }
    else {
      PossFollowList.head();
      for(j=0; j<nPoss; j++) {
	nFollow = 0; 
	town = (*PossFollowList.current());
	for(k=0; k<p.GEN_SIZE; k++) {
	  if (CM[k][town]) nFollow++; 
	}
	FollowersList[nFollow].insert(town);
	PossFollowList.next();
      }
      k=0;
      while (FollowersList[k].size() == 0) k++;
      FollowersList[k].warp(GARandomInt(0,FollowersList[k].size()));
      town = (*FollowersList[k].current());
      visit[town]=1; 
      
      for(int i=0; i < p.MAX_TOWNS; i++){
	CM[town][i] = 0;
      }
      
      //memset(CM[town], 0, p.MAX_TOWNS*sizeof(char));
      
      sis.insert(town); 
    }
    while (PossFollowList.head()) PossFollowList.destroy();
    for(k=0; k<5; k++) {
      while (FollowersList[k].head()) FollowersList[k].destroy(); 
    }
  }
  sis.head();         // set iterator to head of list
  
  CM = del_matrix_char (p.MAX_TOWNS,p.MAX_TOWNS,CM);
  delete visit;
  
  
}


int PMXover(const GAGenome& g1, const GAGenome& g2, GAGenome* c1, GAGenome* c2) {
  GAListGenome<int> &mom=(GAListGenome<int> &)g1;
  GAListGenome<int> &dad=(GAListGenome<int> &)g2;
  
  int a = GARandomInt(0, mom.size());
  int b = GARandomInt(0, dad.size());
  int h;
  if (b<a) { h=a; a=b; b=h; }
  
  int* index;
  int i,j,nc=0;
  
  if(c1) {
    GAListGenome<int> &sis=(GAListGenome<int> &)*c1;
    sis.GAList<int>::copy(mom);
    GAListIter<int> diter(dad);
    index = diter.warp(a);
    for(i=a; i<b; i++, index=diter.next()){
      if(*sis.head() == *index){
	sis.swap(i,0);
      }
      else{
	for(j=1; (j<sis.size()) && (*sis.next() != *index); j++);
	sis.swap(i,j);  // no op if j>size
      }
    }
    sis.head();         // set iterator to head of list
    nc += 1;
  }
  if(c2) {
    GAListGenome<int> &sis=(GAListGenome<int> &)*c2;
    sis.GAList<int>::copy(mom);
    GAListIter<int> diter(dad);
    index = diter.warp(a);
    for(i=a; i<b; i++, index=diter.next()){
      if(*sis.head() == *index){
	sis.swap(i,0);
      }
      else{
	for(j=1; (j<sis.size()) && (*sis.next() != *index); j++);
	sis.swap(i,j);  // no op if j>size
      }
    }
    sis.head();         // set iterator to head of list
    nc += 1;
  }
  
  return nc;
}


float Comparator(const GAGenome& g1, const GAGenome& g2) {
  GAListGenome<int> &a = (GAListGenome<int> &)g1;
  GAListGenome<int> &b = (GAListGenome<int> &)g2;
  
  int i,j,t1,t2;
  float dist=p.GEN_SIZE;
  
  char **CM1 = new_matrix_char (p.MAX_TOWNS,p.MAX_TOWNS);
  char **CM2 = new_matrix_char (p.MAX_TOWNS,p.MAX_TOWNS);
  
  for(int i=0; i < p.MAX_TOWNS; i++){
    for(int j=0; j< p.MAX_TOWNS; j++){
      CM1[i][j] = 0;
      CM2[i][j] = 0;
      
    }
  }
  
  //memset(CM1, 0, p.MAX_TOWNS*p.MAX_TOWNS*sizeof(char));
  //memset(CM2, 0, p.MAX_TOWNS*p.MAX_TOWNS*sizeof(char));
  
  // create connection matrix CM1
  a.head();
  for(i=0; i<p.GEN_SIZE; i++) {
    t1 = *a.current(); t2 = *a.next();
    CM1[t1][t2]=1; CM1[t2][t1]=1;
  }
  // create connection matrix CM2
  b.head();
  for(i=0; i<p.GEN_SIZE; i++) {
    t1 = *b.current(); t2 = *b.next();
    CM2[t1][t2]=1; CM2[t2][t1]=1;
  }
  //calc distance = how many edges are different
  for (i=0; i<p.GEN_SIZE; i++) {
    for (j=i; j<p.GEN_SIZE; j++) {
      if (CM1[i][j]&CM2[i][j]) dist--;
    }
  }
  
  CM1 = del_matrix_char (p.MAX_TOWNS,p.MAX_TOWNS,CM1);
  CM2 = del_matrix_char (p.MAX_TOWNS,p.MAX_TOWNS,CM2);
  
  return (dist);
}

/*


//   Here we override the _write method for the List class.  This lets us see
// exactly what we want (the default _write method dumps out pointers to the
// data rather than the data contents).
//   This routine prints out the contents of each element of the list, 
// separated by a space.  It does not put a newline at the end of the list.
//   Notice that you can override ANY function of a template class.  This is
// called "specialization" in C++ and it lets you tailor the behaviour of a 
// template class to better fit the type.

*/

template <> int GAListGenome<int>::write(ostream & os) const {
  int *cur, *head;
  GAListIter<int> tmpiter(*this);
  if((head=tmpiter.head()) != 0) {
    os << *head << " ";
    for(cur=tmpiter.next(); cur && cur != head; cur=tmpiter.next())
      os << *cur << " ";
  }
  
  return os.fail() ? 1 : 0;
}



/*
// force instantiations for compilers that do not do auto instantiation
// for some compilers (e.g. metrowerks) this must come after any
// specializations or you will get 'multiply-defined errors when you compile.
*/

#if !defined(GALIB_USE_AUTO_INST)
#include <ga/GAList.C>
#include <ga/GAListGenome.C>
GALIB_INSTANTIATION_PREFIX GAList<int>;
GALIB_INSTANTIATION_PREFIX GAListGenome<int>;
#endif



