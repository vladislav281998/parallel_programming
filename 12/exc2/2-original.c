#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void b2(int N, double *a) {
    for (int i = 0; i < N; ++i) {
        a[i] *= hypot(0.3, 0.4);
    }
}


int main() {
    int N = 9;
    
    double a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    b2(N, a);
}