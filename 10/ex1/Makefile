CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm

all: delannoy_sequential delannoy_parallel

delannoy_sequential: delannoy_sequential.c
	$(CC) $(CFLAGS) -O0 $< -o $@

delannoy_parallel: delannoy_parallel.c
	$(CC) $(CFLAGS) $< -fopenmp -o $@

clean: 
	rm -f delannoy_sequential delannoy_parallel