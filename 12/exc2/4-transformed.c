#include <stdio.h>

int main() {
    int N = 10000000;
    int a[N], b[N], c[N];
    int sum_a = 0, sum_b = 0, sum_c = 0;

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = 1;
        b[i] = 2;
        c[i] = 3;
    }

    // Compute sum_a
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
    }
    // Compute sum_b
    for (int i = 0; i < N; ++i) {
        sum_b += b[i];
    }
    // Compute sum_c
    for (int i = 0; i < N; ++i) {
        sum_c += c[i];
    }

    printf("Sum A: %d, Sum B: %d, Sum C: %d\n", sum_a, sum_b, sum_c);
    return 0;
}
