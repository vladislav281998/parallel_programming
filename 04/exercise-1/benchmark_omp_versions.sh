#!/bin/bash

# Set SLURM directives
#SBATCH --partition=lva                   # Specify the partition
#SBATCH --job-name=mc_pi_benchmark        # Name your job
#SBATCH --output=output_%j.log            # Redirect output stream to this file.
#SBATCH --ntasks=12                       # Maximum number of tasks to start in total
#SBATCH --ntasks-per-node=12              # Maximum number of tasks to start per node
#SBATCH --exclusive                       # Enforce exclusive node allocation

# Define functions for executing and logging results


execute_and_log() {
    ./"$3" "$4" >> "$2"
}

# Benchmark each version with different thread counts
benchmark_version() {
    echo "$1" >> benchmark_result_omp_versions.txt
    for threads in 1 2 4 6 12; do
        execute_and_log "$1" benchmark_result_omp_versions.txt "$2" "$threads"
    done
}

# Run benchmarks for each version
benchmark_version "Atomic" "mc_pi_atomic"
benchmark_version "Pthreads" "mc_pi_pthreads"
benchmark_version "Reduction" "mc_pi_reduction"
benchmark_version "Critical" "mc_pi_critical"


execude_elapsed_time_command() {
    /usr/bin/time -v ./"$3" "$4" 2>&1 | grep -E "User time|Elapsed \(wall clock\) time" >> "$2"
}

# Benchmark each version with different thread counts
benchmark_version() {
    echo "$1" >> wall_clock_statistics.txt
    for threads in 1 2 4 6 12; do
        echo "Nuber of Threads: $threads" >> wall_clock_statistics.txt
        execude_elapsed_time_command "$1" wall_clock_statistics.txt "$2" "$threads"
    done
}

# Run benchmarks for each version
benchmark_version "Atomic" "mc_pi_atomic"
benchmark_version "Pthreads" "mc_pi_pthreads"
benchmark_version "Reduction" "mc_pi_reduction"
benchmark_version "Critical" "mc_pi_critical"
