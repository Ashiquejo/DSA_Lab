#include <stdio.h>
int main() {
    int n, k;
    printf("Enter number of events: ");
    scanf("%d", &n);
    int A[n];
    printf("Enter activity points for each event: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    printf("Enter maximum number of events you can participate in: ");
    scanf("%d", &k);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] < A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    int maxPoints = 0;
    for (int i = 0; i < k && i < n; i++)
        maxPoints += A[i];

    printf("Maximum activity points you can earn: %d\n", maxPoints);
    return 0;
}