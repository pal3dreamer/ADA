#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

void generateRandomMatrix(int n, int A[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand() % 10;
}

void multiplyIterative(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main() {
    int n;
    printf("Enter matrix size: ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    generateRandomMatrix(n, A);
    generateRandomMatrix(n, B);

    clock_t start = clock();
    multiplyIterative(n, A, B, C);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Iterative multiplication took %f seconds\n", time_taken);

    return 0;
}
