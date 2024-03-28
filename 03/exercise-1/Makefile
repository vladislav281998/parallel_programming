CFLAGS = -std=gnu11 -Wall -Wextra
LDFLAGS = -lm

.PHONY: all clean

all: mandelbrot

clean:
	$(RM) mandelbrot mandelbrot.png execution_times.csv *.o

mandelbrot: mandelbrot.o measure_time.o write_csv.o
	$(CC) $(LDFLAGS) -o $@ $^

mandelbrot.o: mandelbrot.c
	$(CC) $(CFLAGS) -c $<

measure_time.o: measure_time.c
	$(CC) $(CFLAGS) -c $<

write_csv.o: write_csv.c
	$(CC) $(CFLAGS) -c $<
