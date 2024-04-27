#include <stdio.h>
#include <stdlib.h>

#define N 1000000000

void original_code(int *x, int *y, int a, int b, int n) {
    for (int i=0; i < n; i++) {
        x[i] = y[i] * 2 + b * i;
    }
    
    for (int i=0; i < n; i++) {
        y[i] = x[i] + a / (i+1);
    }
}

int main() {
    // Allocate memory for arrays x and y
    int *x = (int *)malloc(N * sizeof(int));
    int *y = (int *)malloc(N * sizeof(int));
    
    // Check if memory allocation is successful
    if (x == NULL || y == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int a = 10, b = 5;
    
    // Initialize array y
    for (int i=0; i < N; i++) {
        y[i] = i;
    }
    
    original_code(x, y, a, b, N);

    // Free dynamically allocated memory
    free(x);
    free(y);

    return 0;
}