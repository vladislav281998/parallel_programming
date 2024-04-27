#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000000000

void original_code(int *x, int *y, double *z, int n) {
    double a = 0.0, f;
    int k = 10;
    
    for (int i=0; i < n; i++) {
        a = (x[i] + y[i]) / (i+1);
        z[i] = a;
    }
    
    f = sqrt(a + k);
}

int main() {
    // Allocate memory for arrays x, y, and z
    int *x = (int *)malloc(N * sizeof(int));
    int *y = (int *)malloc(N * sizeof(int));
    double *z = (double *)malloc(N * sizeof(double));
    
    // Check if memory allocation is successful
    if (x == NULL || y == NULL || z == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    
    // Initialize arrays x and y
    for (int i=0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
    }
    
    original_code(x, y, z, N);
    
    // Free dynamically allocated memory
    free(x);
    free(y);
    free(z);

    return 0;
}