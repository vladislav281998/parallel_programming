#!/bin/bash
#SBATCH --job-name=vector_job
#SBATCH --output=vector_job_%j.out
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --cpus-per-task=4

# Load necessary modules (if applicable)
module load gcc/10.2.0

# Set any environment variables
export ENVVAR_SIZE="1000000"

# Run your application
./vector_operations

