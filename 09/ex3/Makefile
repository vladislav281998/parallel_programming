CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -O1 -fno-tree-vectorize -fopenmp
TARGET = float_vectorization_intrinsics

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
