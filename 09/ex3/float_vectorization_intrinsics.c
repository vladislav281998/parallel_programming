#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#include <xmmintrin.h>

#define REPETITIONS 1e6
#define DEFAULT_SIZE 2048

void multiplyAdd(float* a, const float* b, const float* c, size_t size) {
    __m128 a_vec, b_vec, c_vec, result_vec;

    for (int run = 0; run < REPETITIONS; ++run) {
        for (size_t i = 0; i < size; i += 4) {

            b_vec = _mm_load_ps(&b[i]);
            c_vec = _mm_load_ps(&c[i]);

            result_vec = _mm_mul_ps(b_vec, c_vec);

            a_vec = _mm_load_ps(&a[i]);

            a_vec = _mm_add_ps(a_vec, result_vec);

            _mm_store_ps(&a[i], a_vec);
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

    double start = omp_get_wtime();
    multiplyAdd(a, b, c, size);
    double timeTaken = omp_get_wtime() - start;

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
