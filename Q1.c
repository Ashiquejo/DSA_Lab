#include<stdio.h>
struct Poly{
    int coef;
    int expo;
};
int main(){
    int i,j,k,n1,n2;
    printf("Enter the no of terms of first polynomial: ");
    scanf("%d",&n1);
    struct Poly p1[n1];
    for(i=0;i<n1;i++){
        printf("Enter the coefficient and exponent of term %d of first polynomial: ",i+1);
        scanf("%d%d",&p1[i].coef,&p1[i].expo);
    }
    printf("Enter the no of terms of Second polynomial: ");
    scanf("%d",&n2);
    struct Poly p2[n2];
    for(i=0;i<n2;i++){
        printf("Enter the coefficient and exponent of term %d of first polynomial: ",i+1);
        scanf("%d%d",&p2[i].coef,&p2[i].expo);
    }
    printf("\nFirst polynomial: ");
    for(i=0;i<n1;i++){
        printf("%dx^%d",p1[i].coef,p1[i].expo);
        if(i!=n1-1){
            printf("+");
        }
    }
    printf("\nSecond Polynomial: ");
    for(i=0;i<n2;i++){
        printf("%dx^%d",p2[i].coef,p2[i].expo);
        if(i!=n2-1){
            printf("+");
        }
    }
    i=0;j=0;k=0;
    printf("\n");
    struct Poly res[n1+n2];
    while(i<n1 && j<n2){
        if(p1[i].expo==p2[j].expo){
            res[k].coef=p1[i].coef+p2[j].coef;
            res[k].expo=p1[i].expo;
            i++;j++;k++;
        }
        else if(p1[i].expo>p2[j].expo){
            res[k]=p1[i];
            i++;k++;
            }
        else{
            res[k]=p2[j];
            j++;k++;
        }
    }    
    while(i<n1){
        res[k]=p1[i];
        i++;k++;
    }
    while(j<n2){
        res[k]=p2[j];
        j++;k++;
    }
    printf("\nResultant polynomial: ");int x=0;
    for (i = 0; i < k; i++) {
        if (res[i].coef != 0) {
            if (x) {
                printf(" + ");
            }
            printf("%dx^%d", res[i].coef, res[i].expo);
            x = 1;
        }
    }
}
