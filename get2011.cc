#include "get2011.h"

// Some globals...
size_t size = 8;                          // how many operations
rational expectedResult = {2011,1};    // the result we are looking for
size_t numThreads = 5;  // Number of threads per package
rational* numbers;      // Pre-set with the operands 1, 2, 3, ... (size + 1) by default

std::vector<ExpressionTemplate*> worklist;

int main(int argc, char** argv) {

// Read args from command line
  readNumberFromCommandLine( 1, (int*)&size, argc, argv );
  readNumberFromCommandLine( 2, &expectedResult.numer, argc, argv ); 
  readNumberFromCommandLine( 3, (int*)&numThreads, argc, argv ); 

  std::cout << "Starting with..." << std::endl
            << "Number of operations : " << size << std::endl
            << "Expected result : " << expectedResult.numer << std::endl
            << "Package size for number of threads : " << numThreads << std::endl << std::endl;
    
  clock_t t_before = clock();

// Allocate rational numbers on stack and make them globally accessible
// This is OK, since they will be immutable during execution
  rational theNumbers[size+1];
  for (int i=0;i<=size;i++) theNumbers[i] = { i+1, 1};
  numbers = theNumbers;

// Start recursion to evaluate the different parenthesizations  
  getExpressions( size, nextExecutionPlan );

// Cleanup call for the last worklist  
  nextExecutionPlan(0);

  clock_t t_after = clock();

  std::cout << std::endl << (t_after - t_before)*1000/CLOCKS_PER_SEC
            <<"msec execution time" << std::endl;
            
  pthread_exit( 0 );            

  }
  
void *evaluate(void* p) {
  ExpressionTemplate *t = (ExpressionTemplate*) p;
  t->evaluateAllocations();
  return 0;
  }  
  
void nextExecutionPlan( node* root ) {

  if (root != 0) {  // There must be a final cleanup call with root = 0
    worklist.push_back( 
      new ExpressionTemplate(root,numbers,expectedResult,size) 
      );
    }
    
  if (worklist.size() >= numThreads || root == 0) {
  
    std::vector<pthread_t> threads;
  
    for (auto templ = worklist.begin(); templ != worklist.end(); ++templ) {
      pthread_t t;
      pthread_create( &t, 0, evaluate, *templ );
      threads.push_back( t );
      }
    
// Waiting for the end of the threads, in the order of their creation 
// (not so bad, but could be improved, of course)    
    for (auto t = threads.begin(); t != threads.end(); ++t ) {
      pthread_join( *t, 0 );      
      }
    
    for (auto templ = worklist.begin(); templ != worklist.end(); ++templ) {
      (*templ)->printResults();
      delete *templ;
      }    
    
    worklist.resize( 0 );
    
    }
    
  }  

void readNumberFromCommandLine( int i, int* n, int argc, char** argv )  {
  if (argc > i) {
    int number;
    if (sscanf( argv[i], "%d", &number )) *n = number;
    }
  }  
  
// For analysis: This function works pthread-free  
void nextExecutionPlanSingleThreaded( node* root ) {
  ExpressionTemplate* t = new ExpressionTemplate(root,numbers,expectedResult,size);
  t->evaluateAllocations();
  t->printResults();
  delete t;
  }
  
  