CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c17 -g
LDFLAGS=-lpthread

TARGETS=monte_carlo_pi_v1 monte_carlo_pi_v2 monte_carlo_pi_v3

.PHONY: all clean

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
