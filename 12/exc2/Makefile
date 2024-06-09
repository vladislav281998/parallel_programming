# List of exercise numbers
EXERCISES = 1 2 3 4 5

# Compiler and flags
CC = gcc
CFLAGS = -O3

# Perf options
PERC_FLAGS = -e cycles,instructions,cache-references,cache-misses

# Build and profile each pair of original and transformed programs
all: $(EXERCISES)

$(EXERCISES):
	$(CC) $(CFLAGS) $@-original.c -o $@-original
	$(CC) $(CFLAGS) $@-transformed.c -o $@-transformed
	@echo "Profiling $@-original..."
	@perf stat $(PERF_FLAGS) ./$@-original
	@echo "Profiling $@-transformed..."
	@perf stat $(PERF_FLAGS) ./$@-transformed

clean:
	rm -f $(foreach n,$(EXERCISES),$n-original $n-transformed)

.PHONY: all clean
