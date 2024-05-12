#!/bin/bash
#SBATCH --job-name=exercise1_benchmark
#SBATCH --output=exercise1_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=6
#SBATCH --time=01:00:00

module load gcc

export OMP_DISPLAY_AFFINITY=true
export OMP_AFFINITY_FORMAT="Thread Affinity: %0.3L %.8n %.15{thread_affinity} %.12H"

echo "Running with all threads in one place"
for i in {1..10}
do
    OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK OMP_PROC_BIND=true OMP_PLACES={0:1:1} ./atomic_increment
done

echo "Running with threads spread across sockets"
for i in {1..10}
do
    OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK OMP_PROC_BIND=true OMP_PLACES=sockets ./atomic_increment
done

echo "Running without OMP_PLACES specified:"
for i in {1..10}
do
    OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK OMP_PROC_BIND=true ./atomic_increment
done

echo "Running without OMP_PLACES & OMP_PROC_BIND specified:"
for i in {1..10}
do
    OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK ./atomic_increment
done