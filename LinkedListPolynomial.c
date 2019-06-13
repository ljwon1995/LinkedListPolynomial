//
//  LinkedListPolynomial.c
//  LinkedListPolynomial
//
//  Created by 이재원 on 10/06/2019.
//  Copyright © 2019 Jae Won. All rights reserved.
//

#include "LinkedListPolynomial.h"


boolean isEmpty(termPointer poly){
    if(poly == NULL)
        return True;
    return False;
}

float coef(termPointer poly, int expon){
    while(poly != NULL){
        if(poly->expon == expon)
            return poly->coef;
        poly = poly->link;
    }
    return 0;
}

int leadExp(termPointer poly){
    if(!isEmpty(poly))
        return poly->expon;
    return 0;
}

void attachTerm(termPointer *poly, float coef, int expon){
    termPointer targ;
    termPointer idx;
    termPointer temp;
    
    if(coef == 0){
        return;
    }
    
    //create Term and init
    targ = (termPointer)malloc(sizeof(term));
    targ->coef = coef;
    targ->expon = expon;
    targ->link = NULL;
    
    //find fit position for this term.
    if(isEmpty(*poly))
        *poly = targ;
    else{
        idx = *poly;
        if(idx->expon < targ->expon){
            targ->link = idx;
            *poly = targ;
        }
        else if(idx->expon == targ->expon){
            idx->coef += targ->coef;
            if(idx->coef == 0){
                *poly = idx->link;
            }
        }
        else{
            while((idx->link != NULL) && idx->link->expon > targ->expon)
                idx = idx->link;
            if(idx -> link == NULL){
                idx->link = targ;
            }
            else if(idx->link->expon < targ->expon){
                targ->link = idx->link;
                idx->link = targ;
            }
            
            else if(idx->link->expon == targ->expon){
                idx->link->coef += targ->coef;
                if(idx->link->coef == 0){
                    temp = idx->link;
                    idx->link = temp->link;
                    free(temp);
                }
            }
            
            else{
                fprintf(stderr, "ERROR CODE : %d\n", UNKNOWN_ERROR);
                exit(UNKNOWN_ERROR);
            }
        }
        
    }
}

int power(int bot, int index){
    int result;
    result = bot;
    
    if(index == 0)
        return 1;
    
    while(index != 1){
        result *= bot;
        index--;
    }
    
    return result;
}

void printOneDigit(int n){
    switch (n) {
        case 0:
            printf("⁰");
            break;
            
        case 1:
            printf("¹");
            break;
            
        case 2:
            printf("²");
            break;
            
        case 3:
            printf("³");
            break;
            
        case 4:
            printf("⁴");
            break;
            
        case 5:
            printf("⁵");
            break;
            
        case 6:
            printf("⁶");
            break;
            
        case 7:
            printf("⁷");
            break;
            
        case 8:
            printf("⁸");
            break;
            
        case 9:
            printf("⁹");
            break;
            
        default:
            fprintf(stderr, "ERRORCODE : %d\n",UNKNOWN_ERROR);
            exit(UNKNOWN_ERROR);
            break;
    }
}

void printSuperScript(int n){
    int len, i;
    int temp;
    
    temp = n;
    len = 0;
    while(temp != 0){
        temp /= 10;
        len++;
    }
    
    for(i = len; i > 0; i--){
        printOneDigit(n / (power(10, i-1)));
        n %= power(10, i-1);
    }
}

void printPoly(termPointer poly){
    boolean first = True;
    
    while(poly != NULL){
        
        if(poly->coef > 0)
            printf("%.0f", poly->coef);
        else if(poly->coef < 0){
            if(first == True){
                printf("- ");
            }
            printf("%.0f", -poly->coef);
        }
        else{
            fprintf(stderr, "ERRORCODE : %d\n", UNKNOWN_ERROR);
            exit(UNKNOWN_ERROR);
        }
        
        
        
        if(poly->expon != 0)
            printf("x");
        printSuperScript(poly->expon);
        if(poly->link != NULL && poly->link->coef > 0){
            printf(" + ");
        }
        else if(poly->link != NULL && poly->link->coef < 0){
            printf(" - ");
        }
        else if(poly->link != NULL && poly->link->coef == 0){
            fprintf(stderr, "ERRORCODE : %d\n", UNKNOWN_ERROR);
            exit(UNKNOWN_ERROR);
        }
        
        poly = poly->link;
        first = False;
    }
}

void deleteTerm(termPointer *poly, int expon){
    termPointer temp, idx;
    
    if(isEmpty(*poly)){
        return;
    }
    
    else if(expon == leadExp(*poly)){
        temp = *poly;
        *poly = (*poly)->link;
        free(temp);
        return;
    }
    
    else{
        idx = *poly;
        while((idx->link != NULL) && (idx->link->expon != expon)){
            idx = idx->link;
        }
        
        if(idx->link == NULL)
            return;
        else if(idx->link->expon == expon){
            temp = idx->link;
            idx->link = temp->link;
            free(temp);
            return;
        }
        else{
            fprintf(stderr, "ERRORCODE %d\n", UNKNOWN_ERROR);
            exit(UNKNOWN_ERROR);
        }
            
        
    }
}

void deleteAll(termPointer *poly){
    termPointer idx, temp;

    idx = *poly;
    temp = *poly;
    *poly = NULL;
    
    while(idx->link != NULL){
        idx = idx->link;
        free(temp);
        temp = idx;
        
    }
    free(temp);
}

void singleMult(termPointer *poly, float coef, int expon){
    termPointer idx;
    
    if(coef == 0)
        deleteAll(poly);
    else{
        idx = *poly;
        while(idx != NULL){
            idx->coef *= coef;
            idx->expon += expon;
            idx = idx->link;
        }
    }
}

termPointer polyAdd(termPointer polyA, termPointer polyB){
    termPointer polyResult = NULL;
    termPointer rear = NULL;
    termPointer temp;
    
    if(isEmpty(polyA) && isEmpty(polyB))
        return NULL;
    
    polyResult = (termPointer)malloc(sizeof(term));
    rear = polyResult;
    
    while(polyA != NULL && polyB != NULL){
        if(leadExp(polyA) > leadExp(polyB)){
            rear->link = (termPointer)malloc(sizeof(term));
            rear = rear->link;
            rear->link = NULL;
            rear->coef = polyA->coef;
            rear->expon = polyA->expon;
            polyA = polyA->link;
        }
        
        else if(leadExp(polyA) == leadExp(polyB)){
            
            if(polyA->coef + polyB->coef != 0){
                rear->link = (termPointer)malloc(sizeof(term));
                rear = rear->link;
                rear->link = NULL;
                rear->coef = polyA->coef + polyB->coef;
                rear->expon = polyA->expon;
                
            }
                polyA = polyA->link;
                polyB = polyB->link;
        }
        
        else{
            rear->link = (termPointer)malloc(sizeof(term));
            rear = rear->link;
            rear->link = NULL;
            rear->coef = polyB->coef;
            rear->expon = polyB->expon;
            polyB = polyB->link;
        }
    }
    
    if(polyA == NULL){
        while(polyB != NULL){
            rear->link = (termPointer)malloc(sizeof(term));
            rear = rear->link;
            rear->link = NULL;
            rear->coef = polyB->coef;
            rear->expon = polyB->expon;
            polyB = polyB->link;
        }
    }
    
    else{
        while(polyA != NULL){
            rear->link = (termPointer)malloc(sizeof(term));
            rear = rear->link;
            rear->link = NULL;
            rear->coef = polyA->coef;
            rear->expon = polyA->expon;
            polyA = polyA->link;
        }
    }
    
    temp = polyResult;
    polyResult = polyResult->link;
    free(temp);
    
    return polyResult;
}

termPointer polyMult(termPointer polyA, termPointer polyB){
    termPointer idxA, idxB;
    termPointer resultPoly = NULL;
    
    
    if(polyA == NULL || polyB == NULL)
        return NULL;
    
    for(idxA = polyA; idxA != NULL; idxA = idxA->link){
        for(idxB = polyB; idxB != NULL; idxB = idxB->link){
            attachTerm(&resultPoly, idxA->coef * idxB->coef, idxA->expon + idxB->expon);
        }
    }
    
    return resultPoly;
}
