CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm

all: vector_optimized vectorized_no_optimization vectorized_with_optimization

vector_optimized: vectorized.c
	$(CC) $(CFLAGS) -O2 $< -o $@

vectorized_with_optimization: vectorized.c
	$(CC) $(CFLAGS) -O2 -ftree-vectorize $< -o $@

vectorized_no_optimization: vectorized.c
	$(CC) $(CFLAGS) -O0 -ftree-vectorize $< -o $@


clean: 
	rm -f vector_optimized vectorized_no_optimization vectorized_with_optimization