#include <stdio.h>
#include <stdlib.h>



 void a2_unrolled(int N, int a[], int b[]) {
    int bt; 
     for (int i = 0; i < N - 1; i+=2) {
        bt = b[i+1];
         a[i] = b[i] + bt;
         a[i+1] = bt + b[i+2];
     }
 }

int main() {
    int N = 9; 
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a_unrolled[N-1];

     a2_unrolled(N, a_unrolled, b);
}