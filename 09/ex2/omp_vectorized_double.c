#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h> 

#define REPETITIONS 1e6
#define DEFAULT_SIZE 2048

void multiplyAdd(double* a, const double* b, const double* c, size_t size) {
    for (int run = 0; run < REPETITIONS; ++run) {
#pragma omp simd 
        for (size_t i = 0; i < size; ++i) {
            a[i] += b[i] * c[i];
        }
    }
}

int main(int argc, char *argv[]) {

    size_t size;
    if (argc > 1) {
        size = atoi(argv[1]);
    } else {
        size = DEFAULT_SIZE;
    }
    
    double* a = (double*)malloc(size * sizeof(double));
    double* b = (double*)malloc(size * sizeof(double));
    double* c = (double*)malloc(size * sizeof(double));
    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    // Initialize vectors with constant values
    for (size_t i = 0; i < size; ++i) {
        a[i] = 0;
        b[i] = 1.0;
        c[i] = 2.0;
    }

    double start = omp_get_wtime();
    multiplyAdd(a, b, c, size);
    double timeTaken = omp_get_wtime() - start;

    int correctResult = 1;
    double tolerance = 1e-5;
    for (size_t i = 0; i < size; ++i) {
        if (fabs(a[i] - (b[i] * c[i] * REPETITIONS)) > tolerance) {
            correctResult = 0;
            break;
        }
    }

    printf("%ld, %lf, %d\n", size, timeTaken, correctResult);

    free(a);
    free(b);
    free(c);

    return 0;
}