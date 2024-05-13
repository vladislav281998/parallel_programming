#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
    #pragma omp parallel for schedule(guided)
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
    double start_time, end_time;
    
    start_time = omp_get_wtime();
    hadamard_product_parallel(n, a, b, c);
    end_time = omp_get_wtime();
    printf("Parallel execution time: %f seconds\n", end_time - start_time);
    
    
    free_matrix(n, a);
    free_matrix(n, b);
    free_matrix(n, c);
    
    return 0;
}

