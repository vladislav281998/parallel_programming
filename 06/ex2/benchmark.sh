#!/bin/bash
#SBATCH --job-name=exercise2_benchmark
#SBATCH --output=exercise2_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

module load gcc

run_benchmarks () {
    local program=$1
    local threads=$2
    local iteration=$3
    local output_file=$4

    echo "Run $iteration: Running ${program} with ${threads} threads" >> $output_file

    # Appending execution time and output to the same file
    { time OMP_NUM_THREADS=$threads ./$program; } >> $output_file 2>&1
}

# program arrays
single_thread_programs=(task1_original task2_original task3_original)
programs=(task1_optimized task2_optimized task3_optimized)

# Run non-multithreaded tasks with a single thread
for program in "${single_thread_programs[@]}"; do
    output_file="${program}_benchmark.out"
    for i in {1..10}; do
        run_benchmarks $program 1 $i $output_file
    done
done

# Run multithreaded tasks with varying thread counts
for threads in 1 2 4 6 12; do
    for program in "${multithreaded_programs[@]}"; do
        output_file="${program}_benchmark.out"
        for i in {1..10}; do
            run_benchmarks $program $threads $i $output_file
        done
    done
done