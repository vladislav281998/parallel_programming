CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm -O3

all: hadamard_row_major hadamard_row_major_serial hadamard_row_major_static hadamard_row_major_dynamic hadamard_row_major_guided hadamard_column_major_dynamic hadamard_column_major_guided hadamard_column_major_static hadamard_column_major_runtime hadamard_column_major_auto hadamard_row_major_runtime hadamard_row_major_auto

hadamard_row_major: hadamard_row_major.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_row_major_serial: hadamard_row_major_serial.c
	$(CC) $(CFLAGS) $< -o $@

hadamard_row_major_static: hadamard_row_major_static.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_row_major_dynamic: hadamard_row_major_dynamic.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_row_major_guided: hadamard_row_major_guided.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_row_major_auto: hadamard_row_major_auto.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_row_major_runtime: hadamard_row_major_runtime.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_column_major_static: hadamard_column_major_static.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_column_major_dynamic: hadamard_column_major_dynamic.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_column_major_guided: hadamard_column_major_guided.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_column_major_runtime: hadamard_column_major_runtime.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@

hadamard_column_major_auto: hadamard_column_major_auto.c
	$(CC) $(CFLAGS) -fopenmp $< -o $@


clean: 
	rm -f hadamard_row_major hadamard_row_major_serial hadamard_row_major_static hadamard_row_major_dynamic hadamard_row_major_guided hadamard_column_major_static hadamard_column_major_dynamic hadamard_column_major_guided hadamard_column_major_runtime hadamard_column_major_auto hadamard_row_major_runtime hadamard_row_major_auto
