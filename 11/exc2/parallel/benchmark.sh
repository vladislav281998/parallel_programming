#!/bin/bash
#SBATCH --job-name=exercise2_benchmark
#SBATCH --output=exercise2_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

module load gcc

make

# Benchmark parallel version with different thread counts (each 10 times)
for THREADS in 1 2 6 12; do
    echo "Parallel Benchmark ($THREADS threads):"
    export OMP_NUM_THREADS=$THREADS
    for i in {1..10}; do
        TIMEFORMAT=%R
        time_taken=$( { time ./real_parallel > /dev/null; } 2>&1 )
        echo "Run $i took $time_taken seconds"
    done
done