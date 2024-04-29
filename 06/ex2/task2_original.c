#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 1000000000

void original(int n, double *x, double *y, double *z) {
    for (int i = 1; i<n; i++) {
        x[i] = (x[i] + y[i-1]) / 2;
        y[i] = y[i] + z[i] * 3;
    }
}

int main() {
    // Allocate memory for arrays x and y
    double *x = (double *)malloc(N * sizeof(double ));
    double *y = (double *)malloc(N * sizeof(double ));
    double *z = (double *)malloc(N * sizeof(double ));

    // Check if memory allocation is successful
    if (x == NULL || y == NULL || z == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize arrays x and y
    for (int i=0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
        z[i] = i * 2;
    }

    double start_time = omp_get_wtime();
    original(N, x, y, z);
    double end_time = omp_get_wtime();

    //print execution time
    printf("Execution time of optimized function: %f seconds\n", end_time - start_time);

    // Free dynamically allocated memory
    free(x);
    free(y);
    free(z);
    return 0;
}
