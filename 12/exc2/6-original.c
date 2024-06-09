#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

const int N = 1000000000;
int main() {
    int *a = malloc(N * sizeof(int));
    int *b = malloc(N * sizeof(int));
    int *c = malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        b[i] = i * 2;
        c[i] = i * 3;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < N; ++i) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
    }

    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + microseconds * 1e-6;
    printf("Original loop time: %.6f seconds\n", elapsed);

    free(a);
    free(b);
    free(c);
    return 0;
}