#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void a2(int N, int a[], int b[]) {
    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }
}


int main() {
    int N = 9; 
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a[N-1];

    a2(N, a, b);
}