#!/bin/bash
#SBATCH --job-name=exercise2_benchmark
#SBATCH --output=exercise2_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

module load gcc

make

# Benchmark sequential version (10 times)
echo "Sequential Benchmark:"
for i in {1..10}; do
    TIMEFORMAT=%R
    time_taken=$( { time ./real > /dev/null; } 2>&1 )
    echo "Run $i took $time_taken seconds"
done