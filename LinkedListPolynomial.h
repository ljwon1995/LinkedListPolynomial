//
//  LinkedListPolynomial.h
//  LinkedListPolynomial
//
//  Created by 이재원 on 10/06/2019.
//  Copyright © 2019 Jae Won. All rights reserved.
//

#ifndef LinkedListPolynomial_h
#define LinkedListPolynomial_h

#include <stdio.h>
#include "Boolean.h"
#include <stdlib.h>
#define UNKNOWN_ERROR -1

typedef struct term *termPointer;
typedef struct term{
    float coef;
    int expon;
    termPointer link;
}term;

void printPoly(termPointer poly);
boolean isEmpty(termPointer poly);
float coef(termPointer poly, int expon);
int leadExp(termPointer poly);
void attachTerm(termPointer *poly, float coef, int expon);
void deleteTerm(termPointer *poly, int expon);
void singleMult(termPointer *poly, float coef, int expon);
termPointer polyAdd(termPointer polyA, termPointer polyB);
termPointer polyMult(termPointer polyA, termPointer polyB);
void deleteAll(termPointer *poly);
termPointer polyRead(void);
float peval(termPointer poly, float x);


    


#endif /* LinkedListPolynomial_h */
