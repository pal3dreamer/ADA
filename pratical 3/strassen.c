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

void strassenMultiply(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX], M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Partition matrices
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

    // M1 = (A11 + A22) * (B11 + B22)
    add(half, A11, A22, temp1);
    add(half, B11, B22, temp2);
    strassenMultiply(half, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    add(half, A21, A22, temp1);
    strassenMultiply(half, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    subtract(half, B12, B22, temp2);
    strassenMultiply(half, A11, temp2, M3);

    // M4 = A22 * (B21 - B11)
    subtract(half, B21, B11, temp2);
    strassenMultiply(half, A22, temp2, M4);

    // M5 = (A11 + A12) * B22
    add(half, A11, A12, temp1);
    strassenMultiply(half, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subtract(half, A21, A11, temp1);
    add(half, B11, B12, temp2);
    strassenMultiply(half, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subtract(half, A12, A22, temp1);
    add(half, B21, B22, temp2);
    strassenMultiply(half, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    add(half, M1, M4, temp1);
    subtract(half, temp1, M5, temp2);
    add(half, temp2, M7, C11);

    // C12 = M3 + M5
    add(half, M3, M5, C12);

    // C21 = M2 + M4
    add(half, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subtract(half, M1, M2, temp1);
    add(half, temp1, M3, temp2);
    add(half, temp2, M6, C22);

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
