#!/bin/bash
#SBATCH --job-name=vectorized_benchmark
#SBATCH --output=exercise2_benchmark.out
#SBATCH --time=01:00:00

# Array of sizes to run the program with
sizes=(1024 2048 4096 8192 16384)

echo "Running vector benchmark with -O2 optimization"

for size in "${sizes[@]}"
do
    echo "Run for size $size"
    ./vector_optimized $size
done

echo "Running optimized vectorisation with O2 benchmark"

for size in "${sizes[@]}"
do
    echo "Run for size $size"
    ./vectorized_with_optimization $size
done

echo "Running vectorisation program with no optimisation benchmark"

for size in "${sizes[@]}"
do
    echo "Run for size $size"
    ./vectorized_no_optimization $size
done
