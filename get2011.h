#include <time.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <thread>
#include <pthread.h>


#include "rational.h"
#include "etrees.h"
#include "ExpressionTemplate.h"

int main(int argc, char **argv);
void nextExecutionPlan( node* root );
void nextExecutionPlanSingleThreaded( node* root );
void *evaluate(void* p);

void readNumberFromCommandLine( int i, int* n, int argc, char** argv );

