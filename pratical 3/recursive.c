#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void recursiveMultiply(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Initialize submatrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // C11 = A11*B11 + A12*B21
    recursiveMultiply(half, A11, B11, temp1);
    recursiveMultiply(half, A12, B21, temp2);
    add(half, temp1, temp2, C11);

    // C12 = A11*B12 + A12*B22
    recursiveMultiply(half, A11, B12, temp1);
    recursiveMultiply(half, A12, B22, temp2);
    add(half, temp1, temp2, C12);

    // C21 = A21*B11 + A22*B21
    recursiveMultiply(half, A21, B11, temp1);
    recursiveMultiply(half, A22, B21, temp2);
    add(half, temp1, temp2, C21);

    // C22 = A21*B12 + A22*B22
    recursiveMultiply(half, A21, B12, temp1);
    recursiveMultiply(half, A22, B22, temp2);
    add(half, temp1, temp2, C22);

    // Combine results
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
}
