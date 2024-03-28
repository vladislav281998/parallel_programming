#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

// Include the header for timing (assuming you've made it a header or declare the functions here)
extern void start_timer(void);
extern void stop_timer(void);
extern double get_elapsed_time(void);

// Include the header or declare the function for CSV writing
extern void append_to_csv(const char *filename, const char *program_name, double execution_time);

void calc_mandelbrot(uint8_t image[Y][X]) {
    for (int y_pixel = 0; y_pixel < Y; ++y_pixel) {
        for (int x_pixel = 0; x_pixel < X; ++x_pixel) {
            double x = 0.0;
            double y = 0.0;
            double cx = (x_pixel * 3.5 / X) - 2.5; // Map to [-2.5, 1]
            double cy = (y_pixel * 2.0 / Y) - 1.0; // Map to [-1, 1]
            int iteration = 0;
            
            while ((x * x + y * y <= 4.0) && (iteration < MAX_ITER)) {
                double x_tmp = x * x - y * y + cx;
                y = 2.0 * x * y + cy;
                x = x_tmp;
                iteration++;
            }
            
            uint8_t norm_iteration = (uint8_t)(iteration % 256); // Normalize to [0, 255]
            image[y_pixel][x_pixel] = norm_iteration;
        }
    }
}

int main() {
    start_timer(); // Start the timer

    uint8_t image[Y][X];
    calc_mandelbrot(image);

    const int channel_nr = 1, stride_bytes = 0;
    stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);

    stop_timer(); // Stop the timer

    // Append the execution time to a CSV file
    append_to_csv("execution_times.csv", "Mandelbrot Calculation", get_elapsed_time());

    return EXIT_SUCCESS;
}