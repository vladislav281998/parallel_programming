#!/bin/bash
#SBATCH --job-name=pi_benchmark
#SBATCH --output=pi_benchmark_%j.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=12
#SBATCH --time=01:00:00

module load gcc

# Define the compiler flags
CFLAGS="-Wall -Wextra -Wpedantic -Werror -std=c17"
LDFLAGS="-lpthread"

# Compile the programs
gcc $CFLAGS monte_carlo_pi_v1.c -o monte_carlo_pi_v1 $LDFLAGS
gcc $CFLAGS monte_carlo_pi_v2.c -o monte_carlo_pi_v2 $LDFLAGS
gcc $CFLAGS monte_carlo_pi_v3.c -o monte_carlo_pi_v3 $LDFLAGS

# Benchmark with different number of threads
for threads in 1 2 4 6 8 10 12; do
    echo "Running with ${threads} threads:"
    ./monte_carlo_pi_v1 ${threads}
    ./monte_carlo_pi_v2 ${threads}
    ./monte_carlo_pi_v3 ${threads}
done

# Recompile the programs with -O3 optimization flag
gcc $CFLAGS -O3 monte_carlo_pi_v1.c -o monte_carlo_pi_v1 $LDFLAGS
gcc $CFLAGS -O3 monte_carlo_pi_v2.c -o monte_carlo_pi_v2 $LDFLAGS
gcc $CFLAGS -O3 monte_carlo_pi_v3.c -o monte_carlo_pi_v3 $LDFLAGS

# Benchmark with different number of threads
for threads in 1 2 4 6 8 10 12; do
    echo "Running with ${threads} threads (optimized):"
    ./monte_carlo_pi_v1 ${threads}
    ./monte_carlo_pi_v2 ${threads}
    ./monte_carlo_pi_v3 ${threads}
done
