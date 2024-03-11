#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name slow_run
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=12
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=12
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

export OMP_NUM_THREADS=1

gcc -o slow_O0 slow.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O0 -fopenmp
echo 'Execution time of slow_O0 with 1 thread:' >> output.log
(time ./slow_O0) 2>> output.log

gcc -o medium_O1 medium.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O1 -fopenmp
echo 'Execution time of medium_O1 with 1 thread:' >> output.log
(time ./medium_O1) 2>> output.log

gcc -o fast_O2 fast.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O2 -fopenmp
echo 'Execution time of fast_O2 with 1 thread:' >> output.log
(time ./fast_O2) 2>> output.log


rm slow_O0 && rm medium_O1 && rm fast_O2

export OMP_NUM_THREADS=12

gcc -o slow_O1 slow.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O1 -fopenmp
echo 'Execution time of slow_O1 with 12 threads:' >> output.log
(time ./slow_O1) 2>> output.log

gcc -o fast_O2 fast.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O2 -fopenmp
echo 'Execution time of fast_O2 with 12 threads:' >> output.log
(time ./fast_O2) 2>> output.log

gcc -o medium_O2 fast.c -std=gnu11 -Wall -Werror -Wextra -fopenmp -O2 -fopenmp
echo 'Execution time of medium_O2 with 12 threads:' >> output.log
(time ./medium_O2) 2>> output.log

rm slow_O1 && rm medium_O2 && rm fast_O2