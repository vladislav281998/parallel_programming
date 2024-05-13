#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** create_matrix(int n) {
    double** mat = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        mat[i] = (double*)malloc(n * sizeof(double));
    }
    return mat;
}

void free_matrix(int n, double** mat) {
    for (int i = 0; i < n; ++i) {
        free(mat[i]);
    }
    free(mat);
}


void hadamard_product_parallel(int n, double **a, double **b, double **c) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please specify matrix size\n", argv[0]);
        return 1;
    }

    size_t n = atoi(argv[1]);
    double **a = create_matrix(n);
    double **b = create_matrix(n);
    double **c = create_matrix(n);
    
    clock_t start_time = clock();
    hadamard_product_parallel(n, a, b, c);
    clock_t end_time = clock();
    printf("Serial execution time: %f seconds\n", ((double) (end_time - start_time)) / CLOCKS_PER_SEC);
    
    
    free_matrix(n, a);
    free_matrix(n, b);
    free_matrix(n, c);
    
    return 0;
}