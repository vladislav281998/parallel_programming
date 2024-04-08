#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void hadamard_product_col_major(int32_t** a, int32_t** b, int32_t** c, size_t n) {
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please specify matrix size.\n", argv[0]);
        return 1;
    }

    size_t n = atoi(argv[1]);

    int32_t **a = malloc(n * sizeof(int32_t *));
    int32_t **b = malloc(n * sizeof(int32_t *));
    int32_t **c = malloc(n * sizeof(int32_t *));
    int32_t *a_data = malloc(n * n * sizeof(int32_t));
    int32_t *b_data = malloc(n * n * sizeof(int32_t));
    int32_t *c_data = malloc(n * n * sizeof(int32_t));

    for (size_t i = 0; i < n; ++i) {
        a[i] = &a_data[i * n];
        b[i] = &b_data[i * n];
        c[i] = &c_data[i * n];
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            a[i][j] = 1;
            b[i][j] = 1;
        }
    }

    hadamard_product_col_major(a, b, c, n);

    free(a);
    free(b);
    free(c);
    free(a_data);
    free(b_data);
    free(c_data);

    return 0;
}
