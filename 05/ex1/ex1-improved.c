#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do                     \
	{                      \
		PERROR;            \
		goto label;        \
	} while (0)

// Redefined INIT_ARRAY macro to allocate a contiguous memory block for the entire matrix.
// This reduces the number of malloc calls and can improve cache locality, leading to better performance.
#define INIT_ARRAY(arr, label)                  \
	do                                          \
	{                                           \
		(arr) = malloc(sizeof(*(arr)) * n * n); \
		if (!(arr))                             \
			PERROR_GOTO(label);                 \
		for (long i = 0; i < n; ++i)            \
			for (long j = 0; j < n; ++j)        \
				(arr)[i * n + j] = 0;           \
	} while (0)

// Simplified free_2d_array function to handle the linearly allocated array
void free_2d_array(int *arr)
{
	if (arr)
	{
		free(arr);
	}
}

int main(int argc, char **argv)
{
	// handle input
	if (argc != 2)
	{
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0)
	{
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str)
	{
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0)
	{
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

	// allocate memory
	int status = EXIT_FAILURE;
	int *a; // Using a single pointer to represent the matrix
	INIT_ARRAY(a, error_a);
	int *b; // Using a single pointer to represent the matrix
	INIT_ARRAY(b, error_b);
	int *c; // Using a single pointer to represent the matrix
	INIT_ARRAY(c, error_c);
	unsigned *local_res = malloc(omp_get_max_threads() * sizeof(*local_res));
	if (!local_res)
		PERROR_GOTO(error_c);
	status = EXIT_SUCCESS;

	// fill matrix
	srand(7);
	for (long i = 0; i < n; ++i)
	{
		for (long j = 0; j < n; ++j)
		{
			a[i * n + j] = rand(); // Access as a linear array to match the new memory layout
			b[i * n + j] = rand(); // Access as a linear array to match the new memory layout
		}
	}

	double start_time = omp_get_wtime();
#pragma omp parallel default(none) shared(n, a, b, c, local_res)
	{
// matrix multiplication
// Swapped the order of the loops to improve cache locality and reduce cache misses.
// Replace #pragma omp parallel for with #pragma omp for to avoid creating nested parallel regions.
#pragma omp for schedule(static)
		for (long j = 0; j < n; ++j)
		{
			for (long i = 0; i < n; ++i)
			{
				for (long k = 0; k < n; ++k)
				{
					c[i * n + j] += a[i * n + k] * b[k * n + j]; // Using linear indexing
				}
			}
		}

// sum of matrix c
// Swapped the order of the loops to improve cache locality and reduce cache misses.
// Replace #pragma omp parallel for with #pragma omp for to avoid creating nested parallel regions.
#pragma omp for schedule(static)
		for (long j = 0; j < n; ++j)
		{
			for (long i = 0; i < n; ++i)
			{
				local_res[omp_get_thread_num()] += c[i * n + j]; // Using linear indexing
			}
		}
	}
	unsigned long res = 0;
	for (int l = 0; l < omp_get_num_threads(); ++l)
	{
		res += local_res[l];
	}
	double end_time = omp_get_wtime();
	printf("res: %lu, time: %2.2f seconds\n", res, end_time - start_time);

	// cleanup
	free(local_res);
error_c:
	free_2d_array(c); // Using the simplified free_2d_array function
error_b:
	free_2d_array(b); // Using the simplified free_2d_array function
error_a:
	free_2d_array(a); // Using the simplified free_2d_array function
	return status;
}
