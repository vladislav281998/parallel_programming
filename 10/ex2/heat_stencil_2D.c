#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>
#include <string.h>

#define RESOLUTION_WIDTH 50
#define RESOLUTION_HEIGHT 50

// Heat diffusion constants
#define HEAT_DIFFUSION_FACTOR (0.01)

// Enumeration for the execution mode
typedef enum {
    SERIAL_MODE,
    PARALLEL_MODE
} ExecutionMode;

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do { \
		PERROR; \
		goto label; \
	} while (0)

// Declaration of the functions used in the program to avoid implicit declaration warnings
void assignNewValue(double *A, double *B, int x, int y, int source_x, int source_y, int N);

// -- vector utilities --

#define IND(y, x) ((y) * (N) + (x))

void printTemperature(double *m, int N, int M);

// -- simulation code ---

// Function that executes the heat propagation step in parallel using OpenMP
void executeParallelStep(double **B_param, double **A_param, int N, int source_x, int source_y)
{
    double *B = *B_param;
    double *A = *A_param;

// Parallel execution of the heat propagation step using OpenMP
#pragma omp parallel for collapse(2) schedule(guided)
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            assignNewValue(A, B, x, y, source_x, source_y, N);
        }
    }

    // Swap the temperature arrays for the next iteration
    double *temp = B;
    B = A;
    A = temp;
    *B_param = B;
    *A_param = A;
}
// Function that executes the heat propagation step in serial
void executeSerialStep(double **B_param, double **A_param, int N, int source_x, int source_y)
{
    double *B = *B_param;
    double *A = *A_param;

    // Serial execution of the heat propagation step
    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            assignNewValue(A, B, x, y, source_x, source_y, N);
        }
    }

    // Swap the temperature arrays for the next iteration
    double *temp = B;
    B = A;
    A = temp;
    *B_param = B;
    *A_param = A;
}
// Function that calculates the new temperature value based on the neighboring cells
double calculateNewValue(double leftVal, double rightVal, double upperVal, double lowerVal, double centerVal)
{
    return centerVal + HEAT_DIFFUSION_FACTOR * ((leftVal - 273) + (rightVal - 273) - 4 * (centerVal - 273) + (lowerVal - 273) + (upperVal - 273));
}

// Function that assigns the new temperature value to the current cell based on the neighboring cells
void assignNewValue(double *A, double *B, int x, int y, int source_x, int source_y, int N)
{
    if (x == source_x && y == source_y)
    {
        B[IND(x, y)] = A[IND(x, y)];
    }
    else
    {
        // Calculate the indices of the neighboring cells
        int leftIdx_x = (x == 0) ? x : x - 1;
        int leftIdx_y = y;
        int rightIdx_x = (x == N - 1) ? x : x + 1;
        int rightIdx_y = y;
        int centerIdx_x = x;
        int centerIdx_y = y;
        int upperIdx_x = x;
        int upperIdx_y = (y == N - 1) ? y : y + 1;
        int lowerIdx_x = x;
        int lowerIdx_y = (y == 0) ? y : y - 1;

        // Calculate the new temperature value based on the neighboring cells
        B[IND(x, y)] = calculateNewValue(
            A[IND(leftIdx_x, leftIdx_y)],
            A[IND(rightIdx_x, rightIdx_y)],
            A[IND(upperIdx_x, upperIdx_y)],
            A[IND(lowerIdx_x, lowerIdx_y)],
            A[IND(centerIdx_x, centerIdx_y)]);
    }
}

int main(int argc, char **argv) {
    int N = 200; // Default problem size
    if (argc > 1) {
        N = atoi(argv[1]);
    }

    // Set the execution mode based on the command-line argument
    int executionMode = SERIAL_MODE; // Default execution mode
    if (argc > 2) {
        if (strcmp(argv[2], "parallel") == 0) {
            executionMode = PARALLEL_MODE;
        } else if (strcmp(argv[2], "serial") != 0) {
            printf("Unknown execution mode '%s'. Using default 'serial'.\n", argv[2]);
        }
    }

    int T = N * 10;
    printf("Computing heat-distribution for room size %dX%d for T=%d timesteps\n", N, N, T);

    // ---------- setup ----------

    // create a buffer for storing temperature fields
    double *A =  malloc(sizeof(double) * N * N);

    if(!A) PERROR_GOTO(error_a);

    // set up initial conditions in A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[IND(i,j)] = 273; // temperature is 0° C everywhere (273 K)
        }
    }

    // and there is a heat source
    int source_x = N / 4;
    int source_y = N / 4;
    A[IND(source_x,source_y)] = 273 + 60;

    printf("Initial:");
    printTemperature(A, N, N);
    printf("\n");

    // ---------- compute ----------

    // create a second buffer for the computation
    double *B = malloc(sizeof(double) * N * N);
    if(!B) PERROR_GOTO(error_b);
    // for each time step ..
    for (int t = 0; t < T; t++) {
        // Execute the heat propagation step based on the selected execution mode
        switch (executionMode) {
            case SERIAL_MODE:
                executeSerialStep(&B, &A, N, source_x, source_y);
                break;
            case PARALLEL_MODE:
                executeParallelStep(&B, &A, N, source_x, source_y);
                break;
            default:
                printf("Invalid execution mode. Value was %d\n", executionMode);
                break;
        }

        // every 1000 steps show intermediate step
        if (!(t % 1000)) {
            printf("Step t=%d\n", t);
            printTemperature(A, N, N);
            printf("\n");
        }
    }


    // ---------- check ----------

    printf("Final:");
    printTemperature(A, N, N);
    printf("\n");

    // simple verification if nowhere the heat is more then the heat source
    int success = 1;
    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < N; j++) {
            double temp = A[IND(i,j)];
            if (273 <= temp && temp <= 273 + 60)
                continue;
            success = 0;
            break;
        }
    }

    printf("Verification: %s\n", (success) ? "OK" : "FAILED");

    // todo ---------- cleanup ----------
    error_b:
    free(B);
    error_a:
    free(A);
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void printTemperature(double *m, int N, int M) {
    const char *colors = " .-:=+*^X#%@";
    const int numColors = 12;

    // boundaries for temperature (for simplicity hard-coded)
    const double max = 273 + 30;
    const double min = 273 + 0;

    // set the 'render' resolution
    int W = RESOLUTION_WIDTH;
    int H = RESOLUTION_HEIGHT;

    // step size in each dimension
    int sW = N / W;
    int sH = M / H;

    // upper wall
    printf("\t");
    for (int u = 0; u < W + 2; u++) {
        printf("X");
    }
    printf("\n");
    // room
    for (int i = 0; i < H; i++) {
        // left wall
        printf("\tX");
        // actual room
        for (int j = 0; j < W; j++) {
            // get max temperature in this tile
            double max_t = 0;
            for (int x = sH * i; x < sH * i + sH; x++) {
                for (int y = sW * j; y < sW * j + sW; y++) {
                    max_t = (max_t < m[IND(x,y)]) ? m[IND(x,y)] : max_t;
                }
            }
            double temp = max_t;

            // pick the 'color'
            int c = ((temp - min) / (max - min)) * numColors;
            c = (c >= numColors) ? numColors - 1 : ((c < 0) ? 0 : c);

            // print the average temperature
            printf("%c", colors[c]);
        }
        // right wall
        printf("X\n");
    }
    // lower wall
    printf("\t");
    for (int l = 0; l < W + 2; l++) {
        printf("X");
    }
    printf("\n");
}
