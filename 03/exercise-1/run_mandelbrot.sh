#!/bin/bash

# Specify the partition
#SBATCH --partition=lva
# Name your job
#SBATCH --job-name=mandelbrot
# Redirect output stream to this file.
#SBATCH --output=output_%j.log
# Maximum number of tasks to start in total
#SBATCH --ntasks=1
# Maximum number of tasks to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation
#SBATCH --exclusive

# Maximum number of runs
MAX_RUNS=10
# File to track the number of runs
RUN_FILE="run_count.txt"

# Check if run count file exists and read the count, else initialize to 0
if [[ -f $RUN_FILE ]]; then
  RUN_COUNT=$(<"$RUN_FILE")
else
  RUN_COUNT=0
fi

# Run the mandelbrot program
./mandelbrot

# Increment the run count
((RUN_COUNT++))

# Write the new run count to the file
echo "$RUN_COUNT" > "$RUN_FILE"

# Check if we've reached the max runs. If not, submit the job again
if [[ $RUN_COUNT -lt $MAX_RUNS ]]; then
  sbatch "$0"
else
  echo "Reached maximum number of runs: $MAX_RUNS"
fi
