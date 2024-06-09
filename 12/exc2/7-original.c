#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 1000

int main() {
    double **a, **b, **c;

    a = (double**)malloc(N * sizeof(double*));
    b = (double**)malloc(N * sizeof(double*));
    c = (double**)malloc(N * sizeof(double*));
    for (int i = 0; i < N; i++) {
        a[i] = (double*)malloc(N * sizeof(double));
        b[i] = (double*)malloc(N * sizeof(double));
        c[i] = (double*)malloc(N * sizeof(double));
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            a[i][j] = (double)rand() / RAND_MAX;
            b[i][j] = (double)rand() / RAND_MAX;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    printf("Original loop time: %.6f seconds\n", elapsed);

    for (int i = 0; i < N; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    return 0;
}