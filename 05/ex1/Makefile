CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp

.PHONY: all clean

all: ex1 ex1-improved

ex1: ex1.c
	$(CC) $(CFLAGS) -o $@ $^

ex1-improved: ex1-improved.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) ex1 ex1-improved
