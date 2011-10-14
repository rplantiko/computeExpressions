#ifndef ETREES_H
#define ETREES_H

typedef struct node {
  bool isLeaf; 
  struct node* left; 
  struct node* right;
  } node;


typedef void(*visitor)(node*);
    
extern const node initialNode;

// Child node position 
typedef enum { LEFT, RIGHT } childPos;

void getExpressions(int size, visitor f);
  
void doNode( node* current, int stackSize, 
             node* stack[], node* root, visitor f);
  
void addNodeWithTwoLeaves(node* current, int stackSize, node* stack[], node* root, visitor f);
void addNodeWithOneLeaf(childPos side,node* current, int stackSize, node* stack[], node* root, visitor f);
void addNodeWithNoLeaves(node* current, int stackSize, node* stack[], node* root, visitor f);


void printNode( node*);

#endif
