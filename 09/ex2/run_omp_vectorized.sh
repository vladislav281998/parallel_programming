#!/bin/bash
#SBATCH --job-name=omp_vectorized_benchmark
#SBATCH --output=omp_vectorized_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
#SBATCH --time=01:00:00
#SBATCH --mem=1G

module load gcc

# Executable names of the programs
program_float="omp_vectorized_float"
program_double="omp_vectorized_double"

echo "Running Float Version"
# Run the float version of the program 10 times with performance monitoring
for i in {1..10}; do
    echo "Run $i (Float):"
    perf stat -e r1004,r1010,r1080 ./$program_float
done

echo "Running Double Version"
# Run the double version of the program 10 times with performance monitoring
for i in {1..10}; do
    echo "Run $i (Double):"
    perf stat -e r1004,r1010,r1080 ./$program_double
done
