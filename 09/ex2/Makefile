CC=gcc
CFLAGS=-O1 -std=c99
OMPFLAGS=-fopenmp
LDFLAGS=-lm

# Executable names
TARGET_FLOAT=omp_vectorized_float
TARGET_DOUBLE=omp_vectorized_double

# Default target
all: $(TARGET_FLOAT) $(TARGET_DOUBLE)

$(TARGET_FLOAT): omp_vectorized_float.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

$(TARGET_DOUBLE): omp_vectorized_double.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $^ -o $@ $(LDFLAGS)

run_float:
	@echo "Running OpenMP Vectorized Version with float"
	./$(TARGET_FLOAT)

run_double:
	@echo "Running OpenMP Vectorized Version with double"
	./$(TARGET_DOUBLE)

clean:
	rm -f $(TARGET_FLOAT) $(TARGET_DOUBLE)

.PHONY: all run_float run_double clean
