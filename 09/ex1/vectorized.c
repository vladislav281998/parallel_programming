
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h> 

#define REPETITIONS 1e6

void multiplyAdd(float* a, const float* b, const float* c, size_t size) {
    for (int run = 0; run < REPETITIONS; ++run) {
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
        printf("Please specify size\n");
        return 1;
    }

    float* a = malloc(size * sizeof(float));
    float* b = malloc(size * sizeof(float));
    float* c = malloc(size * sizeof(float));
    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    // Initialize vectors with constant values
    for (size_t i = 0; i < size; ++i) {
        a[i] = 0;
        b[i] = 1;
        c[i] = 2;
    }

    clock_t start_time = clock();
    multiplyAdd(a, b, c, size);
    clock_t end_time = clock();
    double timeTaken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    int correctResult = 1;
    float tolerance = 1e-5;
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
