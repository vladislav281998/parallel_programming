CC=gcc
CFLAGS=-std=gnu11 -Wall -Wextra -lm -fopenmp -O3
TARGET=atomic_increment

all: $(TARGET)

$(TARGET): atomic_increment.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
