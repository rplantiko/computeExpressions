#include <iostream>
#include <vector>

#include "rational.h"
#include "etrees.h"

class ExpressionTemplate {
  public : 
    ExpressionTemplate(node* root, rational* numbers, rational expectedResult, const int size);
    ~ExpressionTemplate();
    void evaluateAllocations();
	void printResults();
  private :
    int size;
	rational expectedResult;
    typedef struct valuatedNode {
      bool isLeaf;
      int* op;
      rational value;
      struct valuatedNode* left;
      struct valuatedNode* right;
      } valuatedNode;
    valuatedNode* nodes;
    int* ops;
	std::vector<int*> results;
    void setNumbersAndOperations( valuatedNode* node, rational* numbers, int* iNum, int* iOps );
    bool isDuplicateByAssociativity( const valuatedNode* node );
	bool doBrackets( int op, int parentOp );
	void printResult( valuatedNode* current, valuatedNode* parent, int ops[]);
  };

