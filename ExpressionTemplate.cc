#include "ExpressionTemplate.h"

ExpressionTemplate::ExpressionTemplate(node* root, rational* numbers, rational expectedResult, const int size) {

  this->size = size;
  this->expectedResult = expectedResult;

/* Get space on the heap */
  nodes = new valuatedNode[2*size+1];
  ops = new int[size];  

/* Copy node structure to enriched node structure (valuatedNode) 
   i)   The left and right child pointers have to be redirected correctly
   ii)  The operation nodes point to successive elements of the allocation array
   iii) The leaves get the rational numbers in the required sequence.
        (ii) & (iii) are performed with a recursive method, see setNumbersAndOperations() below.
   */
  for (int i=0;i<=2*size;i++) {
    nodes[i].isLeaf = (root+i)->isLeaf;
    if (!nodes[i].isLeaf) {
      nodes[i].left  = nodes + ((root+i)->left  - root );
      nodes[i].right = nodes + ((root+i)->right - root );
      }
    }
  int iNum = 0, iOps = 0;
  this->setNumbersAndOperations( nodes, numbers, &iNum, &iOps );
  }  

// Determine the sequence of numbers to evaluate (once per execution plan)
void ExpressionTemplate::setNumbersAndOperations( valuatedNode* node, rational* numbers, int* iNum, int *iOps ) {
  if (node->isLeaf) {
    node->value = numbers[(*iNum)++];
    }
  else {
    node->op = & ops[(*iOps)++];
    this->setNumbersAndOperations(node->left,numbers,iNum,iOps);
    this->setNumbersAndOperations(node->right,numbers,iNum,iOps);
    }
  }
  
ExpressionTemplate::~ExpressionTemplate() {
  for (auto r = results.begin(); r != results.end(); ++r) {
    delete[] *r;
    }
  delete[] nodes;
  delete[] ops;
  }  
  
void ExpressionTemplate::evaluateAllocations() {

// Create all 4**size combinations of operations,
// using a bit field of length 2*size
// If size becomes > 31, think of another implementation of this part
  long long int counter = 1 << 2*size;

  while (counter) {
    counter--;

    long long int allocation = counter;
    nodes[0].value.denom = 0;  // Makes result unequal to everything
    int iOp = size-1;

    for (valuatedNode* current =  nodes + 2*size;
                       current >= nodes;
                       current-- ) {

      if (!current->isLeaf) {

// Pop next operation from bit field
        ops[iOp--] = allocation & 0b11;
        allocation >>= 2;

// Skip [ *, [ *, ...], <>[*,...] ] & the like by associativity
        if  (isDuplicateByAssociativity( current )) break;
        
// Compute next intermediate result
        current->value = current->left->value;
        OPERATION[*current->op](&current->value,current->right->value);

// ignore div 0
        if (current->value.denom == 0) break;

        }

      }

    if (equals(&expectedResult,nodes[0].value)) {
      int* result = new int[size];
      for (int i=0;i<size;i++) result[i] = ops[i];
      results.push_back( result );
      }
    }
  }

inline bool ExpressionTemplate::isDuplicateByAssociativity( const valuatedNode* current ) {
   return
     ! current->left->isLeaf &&
     (*current->left->op & 0b10) == (*current->op & 0b10) &&
        ( current->right->isLeaf ||
           (*current->right->op & 0b10) != (*current->op & 0b10) 
        ); 
   }  
   
void ExpressionTemplate::printResults() {
  
  for (auto ops = results.begin(); ops != results.end(); ops++ ) {
    printResult( nodes, 0, *ops );
    }
    
  }   
   
// Print result as expression
void ExpressionTemplate::printResult( valuatedNode* current, valuatedNode* parent, int ops[]) {
  if (current == nodes) {
    for (int i=0; i<size; i++) { 
      this->ops[i] = ops[i];
      }
    }
  
  if (current->isLeaf) {
    printRational( current->value );
    }
  else {
    if (current != nodes && doBrackets(*current->op, *parent->op) ) std::cout << '(';
    printResult( current->left, current, ops);
    std::cout << glyph( OPERATION[*current->op] );
    printResult( current->right, current, ops);
    if (current != nodes && doBrackets(*current->op, *parent->op)) std::cout << ')';
    }

  if (current == nodes) std::cout << '\n';

  }

// Omit brackets in cases like a * ( b * c ), a * ( b / c ) and so on
inline bool ExpressionTemplate::doBrackets( int op, int parentOp ) {

  int pattern = ( parentOp << 2 ) | op;

  if ( ( pattern == 0b0000 ) ||   // PLUS  -> PLUS
       ( pattern == 0b0001 ) ||   // PLUS  -> MINUS
       ( pattern == 0b1010 ) ||   // TIMES -> TIMES
       ( pattern == 0b1011 ) )    // TIMES -> BY
    return false;
  else
    return true;

  }   
  
