#include <stdio.h>
#include <omp.h>

#define N 500000000


int main() {
    int sum = 0;
    double start_time, end_time;

    start_time = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
    #pragma omp atomic
        sum++;
    }

    end_time = omp_get_wtime();

    printf("Sum: %d\n", sum);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
