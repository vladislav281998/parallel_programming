#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define N 1000000000

void optimized(int n, double *x, double *y) {
#pragma omp parallel for
    for (int i=0; i < n; i++) {
        double factor = 1.0 / (1 << i);
        x[i] = factor * y[i];
    }
}

int main() {
    // Allocate memory for arrays x and y
    double *x = (double *)malloc(N * sizeof(double ));
    double *y = (double *)malloc(N * sizeof(double ));

    // Check if memory allocation is successful
    if (x == NULL || y == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize arrays x and y
    for (int i=0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
    }

    double start_time = omp_get_wtime();
    optimized(N, x, y);
    double end_time = omp_get_wtime();

    //print execution time
    printf("Execution time of optimized function: %f seconds\n", end_time - start_time);

    // Free dynamically allocated memory
    free(x);
    free(y);

    return 0;
}
