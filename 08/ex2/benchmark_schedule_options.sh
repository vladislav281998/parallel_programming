#!/bin/bash
#SBATCH --job-name=benchmark_options
#SBATCH --output=benchmark_options.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

thread_counts=(1 2 4 6 12)


matrix_sizes=(10000 20000 30000)


for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Dynamic: column version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_column_major_dynamic $size
    done
    echo ""
done

for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Dynamic: row version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_row_major_dynamic $size
    done
    echo ""
done

for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Static: column version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_column_major_static $size
    done
    echo ""
done

for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Static: row version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_row_major_static $size
    done
    echo ""
done

for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Guided: column version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_column_major_guided $size
    done
    echo ""
done

for size in "${matrix_sizes[@]}"; do
    echo "Matrix size: $size x $size"
    echo "Schedule Guided: row version"
    for threads in "${thread_counts[@]}"; do
        echo "Number of threads $threads threads:"
        export OMP_NUM_THREADS=$threads
        ./hadamard_row_major_guided $size
    done
    echo ""
done
