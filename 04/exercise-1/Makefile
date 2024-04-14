CC=gcc
CFLAGS=-o -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3

.PHONY:all clean

all:mc_pi_critical mc_pi_atomic mc_pi_pthreads mc_pi_reduction

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	$(RM) *.o mc_pi_critical mc_pi_pthreads mc_pi_atomic mc_pi_reduction

