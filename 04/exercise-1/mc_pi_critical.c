#define _POSIX_C_SOURCE 199506L

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define START_SEED 0

typedef uint64_t timepoint_t;
typedef uint32_t count_t;


static double monte_carlo_pi(count_t total_iterations, uint32_t num_of_threads);

int main(int argc, char** argv) {
    // read input arguments
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<thread_count>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const int32_t requested_threads = (argc <= 1) ? 1 : atoi(argv[1]);
    const uint32_t num_threads = (requested_threads < 1) ? 1 : (uint32_t) requested_threads;

    const count_t total_iterations = ((count_t) 700) * 1000 * 1000;

    double start_time = omp_get_wtime();

    double pi_approximation = monte_carlo_pi(total_iterations, num_threads);

    double end_time = omp_get_wtime(); 

    printf("Approximation of PI took  %.3f seconds with %u threads - value: %.10f\n",
             end_time - start_time, num_threads, pi_approximation);

    return EXIT_SUCCESS;
}

static double monte_carlo_pi(count_t total_iterations, uint32_t num_of_threads) {
    count_t points_in_circle = 0;

    #pragma omp parallel num_threads(num_of_threads)
    {   
        unsigned int seed = START_SEED + omp_get_thread_num();

        #pragma omp for schedule(static)
        for (count_t i = 0; i < total_iterations; ++i) {
            float x = (rand_r(&seed) / (float) RAND_MAX);
            float y = (rand_r(&seed) / (float) RAND_MAX);

            if (x * x + y * y <= 1.0f) {
                #pragma omp critical(c1)
                {
                    ++points_in_circle;
                }
            }
        }
    }

    return 4.0 * (points_in_circle / (double) total_iterations);
}
