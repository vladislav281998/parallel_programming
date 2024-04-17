#!/bin/bash
#SBATCH --job-name=matrix_mult_benchmark
#SBATCH --output=matrix_mult_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

module load gcc/9.2.0   # Modify as needed to load the correct gcc module available on LCC3

# Define the compiler flags
CFLAGS="-std=gnu11 -Wall -Wextra -lm -fopenmp"

# Compile the original and improved programs
gcc $CFLAGS ex1.c -o ex1
gcc $CFLAGS ex1-improved.c -o ex1-improved

# Define matrix size
MATRIX_SIZE=1500

# Function to run benchmarks
run_benchmarks () {
    local program=$1
    local threads=$2
    local n=$3
    local iteration=$4
    echo "Run $iteration: Running ${program} with ${threads} threads and matrix size ${n}"
    OMP_NUM_THREADS=$threads ./$program $n
}

# Loop over thread counts and program versions
for threads in 1 2 4 6 12; do
    for program in ex1 ex1-improved; do
        for i in {1..10}; do   # Repeat each configuration 10 times
            run_benchmarks $program $threads $MATRIX_SIZE $i
        done
    done
done
