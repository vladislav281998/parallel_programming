CC=gcc
CC_FLAGS=-O3 -g3 -lm -pg
OMP_FLAGS=-fopenmp
NUM_THREADS=4
.PHONEY: all
all: real_parallel

SRC=$(wildcard *.c)
	
real_parallel: $(SRC)
	@$(CC) $(CC_FLAGS) $(OMP_FLAGS) $(SRC) -o real_parallel	

.PHONEY: clean
clean:
	@rm real_parallel

.PHONEY: run_parallel
	
run_parallel: real_parallel
	@echo "Running parallel version with $(NUM_THREADS) threads..."
	@OMP_NUM_THREADS=$(NUM_THREADS) ./real_parallel