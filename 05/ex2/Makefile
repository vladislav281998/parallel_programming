CC=gcc
CFLAGS=-o -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3

TARGETS=ex2

.PHONY: all clean

all: $(TARGETS)

clean: $(RM) $(TARGETS)

%: %.c $(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)