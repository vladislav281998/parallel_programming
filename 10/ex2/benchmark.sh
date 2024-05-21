#!/bin/bash
#SBATCH --job-name=heat_stencil_benchmark
#SBATCH --output=heat_stencil_benchmark_%j.out
#SBATCH --time=01:00:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12

module load gcc

sizes=(10 20 50 100 200 300 400 500)

# Outer loop to run the entire benchmark 10 times
for run in {1..10}
do
    echo "Run number: $run"
    # Running the executable for different sizes and thread counts
    for size in "${sizes[@]}"
    do
        echo "Size: $size x $size"
        echo "Serial run:"
        /usr/bin/time -f "Time: %E" ./heat_stencil_2D $size serial
        for threads in 1 12
        do
            echo "Parallel run with $threads threads:"
            export OMP_NUM_THREADS=$threads
            /usr/bin/time -f "Time: %E" ./heat_stencil_2D $size parallel
        done
    done
done
