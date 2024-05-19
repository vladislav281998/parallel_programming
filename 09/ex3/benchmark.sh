#!/bin/bash
#SBATCH --job-name=float_vectorization_intrinsics
#SBATCH --output=exercise3_benchmark_%j.out
#SBATCH --time=01:00:00

module load gcc

# Array of sizes to run the program with
sizes=(1024 2048 4096 8192 16384)

for size in "${sizes[@]}"
do
    for i in {1..10}
    do
        echo "Run $i for size $size"
        ./float_vectorization_intrinsics $size
    done
done