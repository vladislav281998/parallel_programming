#include <stdio.h>
#include <time.h>

// Function prototypes
void start_timer(void);
void stop_timer(void);
double get_elapsed_time(void); // Returns time in seconds

static struct timespec start_time, end_time;

void start_timer() {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void stop_timer() {
    clock_gettime(CLOCK_MONOTONIC, &end_time);
}

double get_elapsed_time() {
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0;
    return elapsed_time;
}
