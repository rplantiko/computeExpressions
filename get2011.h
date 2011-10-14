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
//bool doBrackets( int opIndex, int parentOpIndex );
void nextExecutionPlan( node* root );
//void evaluateAllocations(node* root, rational result[]);
//bool isDuplicateByAssociativity( node* current, node* root, int op[] );
//void printResult( node* current, int parentOp, node* root, rational result[], int op[]);
void printResultRPN( node* current, node* root, rational result[], int op[]);
//void setNumbers( node* current, node* root, rational result[], int* numberIndex );
void readNumberFromCommandLine( int i, int* n, int argc, char** argv );

