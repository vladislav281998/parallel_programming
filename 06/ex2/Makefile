CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm -fopenmp -O3

all: task1_optimized task1_original task2_optimized task2_original task3_optimized task3_original

task1_optimized: task1_optimized.c
	$(CC) $(CFLAGS) -o task1_optimized task1_optimized.c

task1_original: task1_original.c
	$(CC) $(CFLAGS) -o task1_original task1_original.c
	
task2_optimized: task2_optimized.c
	$(CC) $(CFLAGS) -o task2_optimized task2_optimized.c

task2_original: task2_original.c
	$(CC) $(CFLAGS) -o task2_original task2_original.c
	
task3_optimized: task3_optimized.c
	$(CC) $(CFLAGS) -o task3_optimized task3_optimized.c
	
task3_original: task3_original.c
	$(CC) $(CFLAGS) -o task3_original task3_original.c
		
clean:
	rm -f task1_optimized task1_original task2_optimized task2_original task3_optimized task3_original
