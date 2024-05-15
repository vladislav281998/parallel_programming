# Compiler settings - Can change to clang if preferred
CC=gcc
CFLAGS=-O2 -fopenmp

# Build target executable:
TARGET=vector_operations

all: $(TARGET)

$(TARGET): vector_operations.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

