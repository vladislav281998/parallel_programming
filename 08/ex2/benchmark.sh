#!/bin/bash
#SBATCH --job-name=exercise2_benchmark
#SBATCH --output=exercise2_benchmark.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

thread_counts=(1 2 4 6 12)


matrix_sizes=(10000 20000 30000)


for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"

    echo "Serial implementation:" 
    echo "Size $size: " 
    ./hadamard_row_major_serial $size

    for threads in "${thread_counts[@]}"; do
        echo "Parallel implementation with $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_row_major $size
    done
    echo ""
done
