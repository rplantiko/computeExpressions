// An algorithm to determine all binary expression trees
// Uses C99 features: compile with -std=c99. 

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "etrees.h"  
                        
const node initialNode = { true, 0, 0 };
                        
void getExpressions(int size, visitor f) {
    
  node nodes[2*size+1]; // Allocate the complete tree as an array
  node* stack[size];    // Maximum # of stacked nodes = # of operations
  
  node* current = nodes + 2*size+ 1; // = behind the last element
    
  doNode( current, 0, stack, nodes, f );  
  
}

  
void doNode( node* current, int stackSize, 
             node* stack[], node* root, visitor f ) {
              
  int currentIndex = current - root;               
              
// Stack too large - it will not be possible to connect all references
  if (stackSize > currentIndex + 1) return; 
  
  if (currentIndex > 0) {
    
    current--;
  
// First option: Go on with a node with 2 leaves
    if (currentIndex >= 2) {
      addNodeWithTwoLeaves( current, stackSize, stack, root, f );
      }
  
// If there is (at least) one usable reference node with 1 leaf, 1 ref
    if (currentIndex >= 1 && stackSize >= 1) {
      addNodeWithOneLeaf( LEFT,  current, stackSize, stack, root, f );
      addNodeWithOneLeaf( RIGHT, current, stackSize, stack, root, f );
      }   
  
// If there are two node references available: use them in the current node
    if (stackSize >= 2) {
      addNodeWithNoLeaves( current, stackSize, stack, root, f );
      }
    
  } 
  
  else {
  
// Terminal point: Do something with the expression
    f( root );
      
    }  

  }              

void addNodeWithTwoLeaves( node* current, int stackSize, 
                           node* lastStack[], node* root, visitor f ) {

  node *stack[stackSize];  
  for (int i=stackSize-1;i>=0;i--) stack[i] = lastStack[i];

// Build 2 leaves
  *current = initialNode;
  current--;
  *current = initialNode;
  current--;
                  
// Now build the op code                  
  *current = initialNode;
  current->isLeaf = false;  // tag as operation

  current->left  = current+1;
  current->right = current+2;
    
// Push current node on stack   
  stack[stackSize] = current;
  stackSize++;
  
  doNode( current, stackSize, stack, root, f );

  }
  
void addNodeWithOneLeaf( childPos side, node* current, 
                         int stackSize, node* lastStack[], node* root, visitor f ) {

  node *stack[stackSize];  
  for (int i=stackSize-1;i>=0;i--) stack[i] = lastStack[i];

// Build one leaf
  *current = initialNode;
  current--;
                        
  *current = initialNode; 
  current->isLeaf = false;  // tag as operation

// Make the left child node point to the free op    
  switch (side) {
    case LEFT:
      current->left  = stack[stackSize-1];
      current->right = current+1;
      break;
    case RIGHT:
      current->right = stack[stackSize-1];
      current->left  = current+1;
      break;
    default:
      assert( false ); // Not allowed
    }
  
// Replace top of stack by new node 
  stack[stackSize-1] = current;  
    
  doNode( current, stackSize, stack, root, f );
  
  }

void addNodeWithNoLeaves(node* current, int stackSize, 
                         node* lastStack[], node* root, visitor f ) {

  node *stack[stackSize];  
  for (int i=stackSize-1;i>=0;i--) stack[i] = lastStack[i];

  *current = initialNode;
  current->isLeaf = false;  // tag as operation
  
// Make the child nodes point to the topmost free op's
  current->left  = stack[stackSize-1];    
  current->right = stack[stackSize-2];
    
// pop 2, push 1 gives: pop 1   
  stackSize--;  
  stack[stackSize-1] = current;
    
  doNode( current, stackSize, stack, root, f );
      
  }
  
void printNode( node* current) {
  static int n = 0;
  static int j = 0;
  if (current) {
    j++;
    if (current->isLeaf) 
      printf( "num" );
    else { 
      printf( "[op,");
      printNode( current->left );
      printf( "," );
      printNode( current->right );
      printf( "]" );  
      }
    j--;
    if (j == 0) {
      n++;
      printf( "\n");
      }
    }
  else {
    printf( "\nTotal: %d expression trees\n", n);
    }      
  }  

