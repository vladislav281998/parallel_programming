CC=gcc
CFLAGS=-Wall -O3 -fopenmp -g
EXECUTABLE=heat_stencil_2D
SRC=heat_stencil_2D.c

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

run_serial:
	./$(EXECUTABLE) 500 serial

run_parallel: 
	export OMP_NUM_THREADS=12
	./$(EXECUTABLE) 500 parallel

time_test:
	@echo "Running time tests..."
	@echo "Serial:"
	@time ./$(EXECUTABLE) 500 serial
	@echo "Parallel with 1 thread:"
	@OMP_NUM_THREADS=1 time ./$(EXECUTABLE) 500 parallel
	@echo "Parallel with 12 threads:"
	@OMP_NUM_THREADS=12 time ./$(EXECUTABLE) 500 parallel

clean:
	rm -f $(EXECUTABLE)

.PHONY: all run_serial run_parallel time_test clean
