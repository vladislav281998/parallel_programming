CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm -fopenmp -O3

all: task1-optimized task1-unoptimized task2-optimized task2-unoptimized task3-optimized task3-unoptimized

task1-optimized: task1-optimized.c
	$(CC) $(CFLAGS) $< -o $@

task1-unoptimized: task1-unoptimized.c
	$(CC) $(CFLAGS) $< -o $@

task2-optimized: task2-optimized.c
	$(CC) $(CFLAGS) $< -o $@

task2-unoptimized: task2-unoptimized.c
	$(CC) $(CFLAGS) $< -o $@

task3-optimized: task3-optimized.c
	$(CC) $(CFLAGS) $< -o $@

task3-unoptimized: task3-unoptimized.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f task1-optimized task1-unoptimized task2-optimized task2-unoptimized task3-optimized task3-unoptimized