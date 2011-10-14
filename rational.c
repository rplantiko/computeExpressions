#include <stdio.h>
#include "rational.h"

const operation OPERATION[4] = { plus, minus, times, by  };
const rational Infinity = {1,0};

// Constant for tagging an op-node
void any(rational *first, rational second) {}

/* 
  Rational numbers (type rational) and operations on them
  To avoid copy costs, the operations put the result into their first argument    
*/ 

void plus( rational* first, rational second) {
  first->numer = first->numer * second.denom + first->denom * second.numer;
  first->denom = first->denom * second.denom;
  }

void minus( rational* first, rational second) {
  first->numer = first->numer * second.denom - first->denom * second.numer;
  first->denom = first->denom * second.denom;
  }

void times( rational* first, rational second) {
  first->numer *= second.numer;
  first->denom *= second.denom;
  }

void by( rational* first, rational second) {
  first->numer *= second.denom;
  first->denom *= second.numer;
  }
 
int equals(rational *first, rational second) {
  return 
  second.denom &&
  first->numer * second.denom == first->denom * second.numer &&
  first->denom;
  } 

void copy( rational *target, rational source) {
  target->numer = source.numer;
  target->denom = source.denom;  
  }

void printRational( rational x) {
  if (x.denom == 1) printf( "%d", x.numer );
  else printf( "(%d/%d)", x.numer, x.denom );
  }

char glyph( operation op ) {
  if (op==plus)  return '+';
  if (op==minus) return '-';
  if (op==times) return '*';
  if (op==by)    return '/';
  if (op==0)  return '#';
  return '?';
  }
  


  void testRationals() {  
  rational x = {5,3}, y = {4,2}, z;
  printf("Plus, Minus, Times, Divided by applied to\n");
  printRational(x);
  printf(" and ");
  printRational(y);
  printf("\ngives:\n");
  for (int i=0;i<4;i++) {
    copy(&z,x);
    OPERATION[i](&z,y);
    printRational(z);
    printf("\n");
    }
  }
