#!/bin/bash
#SBATCH --job-name=delannoy
#SBATCH --output=delannoy_benchmark.out
#SBATCH --time=01:00:00

# Array of sizes to run the program with
sizes=(3 6 9 12 15)

echo "Running sequential version"

for size in "${sizes[@]}"
do
    export OMP_NUM_THREADS=1
    echo "Run for size $size"
    ./delannoy_sequential $size
done

echo "Running benchmark for parallel version"
for size in "${sizes[@]}"
do
    echo "Run for size $size"
    ./delannoy_parallel $size
done


echo "Running benchmark for parallel version 12 Thread"
    export OMP_NUM_THREADS=12
    /usr/bin/time ./delannoy_parallel 12




