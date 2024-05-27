#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delannoy_number(unsigned long **D, size_t N) {
     for (size_t i = 0; i <= N; i++) {
         D[i][0] = 1;
        D[0][i] = 1;
     }

     for (size_t i = 1; i <= N; i++) {
         for (size_t j = 1; j <= N; j++) {
             D[i][j] = D[i-1][j] + D[i-1][j-1] + D[i][j-1];
         }
     }
}

int delannoy_number_rec(int n, int m) {
    if (m == 0 || n == 0)
        return 1;

    return delannoy_number_rec(m - 1, n) + 
          delannoy_number_rec(m - 1, n - 1) +
          delannoy_number_rec(m, n - 1);
}

int main(int argc, char *argv[]) {

    size_t size;

    if (argc > 1) {
        size = atoi(argv[1]);
    } else {
        printf("Please specify size\n");
        return 1;
    }

    if(size == 0) {
        printf("Delannoy number for D(%zu, %zu) = %d\n", size, size, 1);
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


    clock_t start_time = clock();
    delannoy_number(delannoy, size);
    clock_t end_time = clock();
    double timeTaken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Delannoy number for D(%zu, %zu) = %ld, time taken %f\n", size, size, delannoy[size][size], timeTaken);

    start_time = clock();
    delannoy_number_rec(size, size);
    end_time = clock();
    timeTaken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Delannoy recursive number for D(%zu, %zu) = %ld, time taken %f\n", size, size, delannoy[size][size], timeTaken);

    for (size_t i = 0; i <= size; i++) {
        free(delannoy[i]);
    }
    free(delannoy);
}