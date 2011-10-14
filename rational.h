#ifndef RATIONAL_H
#define RATIONAL_H

// Basic structure of a rational number
typedef struct {
  int numer;
  int denom;
  } rational;   
  
// Operations with rational numbers  
void plus(rational *first, rational second);
void minus(rational *first, rational second);
void times(rational *first, rational second);
void by(rational *first, rational second);

// Any operation on rationals
typedef void(*operation)(rational*, rational);

extern const operation OPERATION[];
extern const rational Infinity;

// Other functions on numbers
int equals(rational *first, rational second);
void copy(rational *target, rational source);
void printRational(rational x);
char glyph(operation op);

// Constant for tagging an op-node
void any(rational *first, rational second);


void testRationals(void);

#endif
