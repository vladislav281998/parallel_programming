#include <stdio.h>
#include <stdlib.h>


void c2(int N, int a[], int b[], int c[]) {
    for (int i = 0; i < N; ++i) {
        if (N % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }
}


int main() {
    int N = 9; 
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int c[] = {2,4,6,7,8,9,10,15,15,11,14,16};
    int a[N];

    c2(N, a, b, c);
}