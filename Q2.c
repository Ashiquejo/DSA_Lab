#include <stdio.h>
int convert(int matrix[10][10], int rows, int cols, int tup[50][3]) {
    int k = 1;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (matrix[i][j] != 0) {
                tup[k][0] = i;
                tup[k][1] = j;
                tup[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    tup[0][0] = rows;
    tup[0][1] = cols;
    tup[0][2] = k - 1; 
    return k;
}
void display_matrix( int matrix[10][10],int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
           
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void displaytup(int tup[50][3]) {
    int n = tup[0][2];
    printf("Row\tCol\tVal\n");
    for (int i = 0; i <= n; i++){
        printf("%d\t%d\t%d\n", tup[i][0], tup[i][1], tup[i][2]);
    }
}
void add(int tupA[50][3], int tupB[50][3], int sum[50][3]) {
    int i = 1, j = 1, k = 1;
    sum[0][0] = tupA[0][0];
    sum[0][1] = tupA[0][1];

    while (i <= tupA[0][2] && j <= tupB[0][2]) {
        if (tupA[i][0] < tupB[j][0] || (tupA[i][0] == tupB[j][0] && tupA[i][1] < tupB[j][1])) {
            sum[k][0] = tupA[i][0];
            sum[k][1] = tupA[i][1];
            sum[k][2] = tupA[i][2];
            i++;
        } else if (tupB[j][0] < tupA[i][0] || (tupB[j][0] == tupA[i][0] && tupB[j][1] < tupA[i][1])) {
            sum[k][0] = tupB[j][0];
            sum[k][1] = tupB[j][1];
            sum[k][2] = tupB[j][2];
            j++;
        } else {
            sum[k][0] = tupA[i][0];
            sum[k][1] = tupA[i][1];
            sum[k][2] = tupA[i][2] + tupB[j][2];
            i++; j++;
        }
        k++;
    }
    while (i <= tupA[0][2]) {
        sum[k][0] = tupA[i][0];
        sum[k][1] = tupA[i][1];
        sum[k][2] = tupA[i][2];
        i++; k++;
    }
    while (j <= tupB[0][2]) {
        sum[k][0] = tupB[j][0];
        sum[k][1] = tupB[j][1];
        sum[k][2] = tupB[j][2];
        j++; k++;
    }

    sum[0][2] = k - 1;
}
void trans(int tup[50][3], int trans[50][3]) {
    int k = 1;
    trans[0][0] = tup[0][1]; 
    trans[0][1] = tup[0][0]; 
    trans[0][2] = tup[0][2];

    for (int col = 0; col < tup[0][1]; col++) {
        for (int i = 1; i <= tup[0][2]; i++) {
            if (tup[i][1] == col) {
                trans[k][0] = tup[i][1];  
                trans[k][1] = tup[i][0];  
                trans[k][2] = tup[i][2];
                k++;
            }
        }
    }
}
int main() {
    int A[10][10], B[10][10];
    int tupleA[50][3], tupleB[50][3], sumTuple[50][3], transTuple[50][3];
    int rows, cols;

    printf("Enter rows and columns: ");
    scanf("%d%d", &rows, &cols);

    printf("\nEnter Matrix A:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter Matrix B:\n");
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            scanf("%d", &B[i][j]);
        }
    }
    printf("Sparse matrix A:\n");
    display_matrix(A,rows,cols);
    printf("Sparse matrix B:\n");
    display_matrix(B,rows,cols);

    convert(A, rows, cols, tupleA);
    convert(B, rows, cols, tupleB);

    printf("\nTuple Representation of Matrix A:\n");
    displaytup(tupleA);

    printf("\nTuple Representation of Matrix B:\n");
    displaytup(tupleB);

    add(tupleA, tupleB, sumTuple);
    printf("\nSum of Matrix A and B in Tuple Format:\n");
    displaytup(sumTuple);

    trans(sumTuple, transTuple);
    printf("\nTranspose of the Sum Matrix in Tuple Format:\n");
    displaytup(transTuple);

    return 0;
}
