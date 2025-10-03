#include <stdio.h>
#include <stdlib.h>

struct Term {
    int coeff;    
    int exp;      
    struct Term *next; 
};


struct Term* createNode(int coeff, int exp) {
    struct Term* newNode = (struct Term*)malloc(sizeof(struct Term));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertTerm(struct Term**
     poly, int coeff, int exp) {
    struct Term* newTerm = createNode(coeff, exp);

    if (*poly == NULL || (*poly)->exp < exp) {
        
        newTerm->next = *poly;
        *poly = newTerm;
    } else {
        
        struct Term* temp = *poly;
        while (temp->next != NULL && temp->next->exp > exp) {
            temp = temp->next;
        }
        if (temp->next != NULL && temp->next->exp == exp) {
            
            temp->next->coeff += coeff;
            free(newTerm);  
        } else {
            newTerm->next = temp->next;
            temp->next = newTerm;
        }
    }
}


struct Term* addPolynomials(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;

    
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly1->exp < poly2->exp) {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coeff + poly2->coeff;
            if (sum != 0) {
                insertTerm(&result, sum, poly1->exp);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    
    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}


void displayPolynomial(struct Term* poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    while (poly != NULL) {
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL && poly->coeff > 0) {
            printf(" + ");
        }
    }
    printf("\n");
}


void inputPolynomial(struct Term** poly) {
    int n, coeff, exp;

    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* result = NULL;

   
    printf("Enter the first polynomial:\n");
    inputPolynomial(&poly1);

    printf("Enter the second polynomial:\n");
    inputPolynomial(&poly2);

    
    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    
    result = addPolynomials(poly1, poly2);

    
    printf("Result of addition: ");
    displayPolynomial(result);

    return 0;
}
