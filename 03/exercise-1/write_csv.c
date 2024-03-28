#include <stdio.h>

// Assumes `filename` exists and is the path to the CSV file where the data will be appended.
// `program_name` is a string identifier for the program, and `execution_time` is the time in seconds.
void append_to_csv(const char *filename, const char *program_name, double execution_time) {
    FILE *file = fopen(filename, "a"); // Open in append mode
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "%s,%.6f\n", program_name, execution_time);
    fclose(file);
}
