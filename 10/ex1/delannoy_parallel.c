#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void delannoy_number(unsigned long **D, size_t N) {
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (size_t i = 0; i <= N; i++) {
                D[i][0] = 1;
                D[0][i] = 1;
            }
        }
        
        #pragma omp taskloop
        for (size_t i = 1; i <= N; i++) {
            for (size_t j = 1; j <= N; j++) {
                {
                D[i][j] = D[i-1][j] + D[i-1][j-1] + D[i][j-1];
                }
            }
        }
    } 
    
}

int main(int argc, char *argv[]) {

    size_t size;

    if (argc > 1) {
        size = atoi(argv[1]);
    } else {
        fprintf(stdout, "Please specify size\n");
        return 1;
    }

    if(size == 0) {
        fprintf(stdout, "Delannoy number for D(%zu, %zu) = %d\n", size, size, 1);
        return 1;
    }

    unsigned long **delannoy = (unsigned long **)malloc((size + 1) * sizeof(unsigned long *));
    if (delannoy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (size_t i = 0; i <= size; i++) {
        delannoy[i] = (unsigned long *)malloc((size + 1) * sizeof(unsigned long));
    }

    for (size_t i = 0; i <= size; i++) {
        delannoy[i] = (unsigned long *)malloc((size + 1) * sizeof(unsigned long));
    }

    double start = omp_get_wtime();
    delannoy_number(delannoy, size);
    double timeTaken = omp_get_wtime() - start;

    fprintf(stdout ,"Delannoy number for D(%zu, %zu) = %ld, time taken %f\n", size, size, delannoy[size][size], timeTaken );

    for (size_t i = 0; i <= size; i++) {
        free(delannoy[i]);
    }
}