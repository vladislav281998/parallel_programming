#include <stdio.h>

int main() {
    int N = 10000;
    int a[N];
    int min = a[0];
    int sum = a[0];

    // Initialize array with some values
    for (int i = 0; i < N; ++i) {
        a[i] = i;
    }

    // Finding minimum and computing sum in one loop
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
        sum += a[i];
    }

    printf("Min: %d, Sum: %d\n", min, sum);
    return 0;
}
