#!/bin/bash
#SBATCH --job-name=exercise2
#SBATCH --output=exercise2_runtime.log
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

thread_counts=(1 2 4 6 12)

matrix_sizes=(10000 20000 30000)


echo "Schedule: auto"
for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"

    for threads in "${thread_counts[@]}"; do
            echo "Parallel implementation with $threads threads:"
            export OMP_NUM_THREADS=$threads
            echo "Row version"
            ./hadamard_row_major_auto $size
            echo "Column version"
            ./hadamard_column_major_auto $size
    done
    echo ""
done


echo "Schedule: runtime"
for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"

    for threads in "${thread_counts[@]}"; do
        echo "Parallel implementation with $threads threads:"
        export OMP_NUM_THREADS=$threads
        echo "Row version"
        ./hadamard_row_major_runtime $size
        echo "Column version"
        ./hadamard_column_major_runtime $size
    done
    echo ""
done