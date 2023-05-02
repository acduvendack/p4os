#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_LINES 1000000
#define THREADS 20
#define LINE_SIZE 2001

struct thread_data {
    char* line;
    int max;
};

// Function to find the maximum ASCII value in a line
int find_max(char* line, int nchars) {
    int max = 0;
    int i;

    for (i = 0; i < nchars; i++) {
        if ((int)line[i] > max) {
            max = (int)line[i];
        }
    }

    if (nchars > 0) {
        return max;
    } else {
        return 0;
    }
}

// Function to be executed by each thread
void* process_lines(void* arg) {
    struct thread_data* data = (struct thread_data*)arg;
    int nchars = strlen(data->line);
    data->max = find_max(data->line, nchars);
    return NULL;
}

int main() {
    int i, j, k, rc;
    FILE* fd;
    char* line[THREADS];
    int err[THREADS];
    struct thread_data data[THREADS];
    pthread_t threads[THREADS];

    // Open the input file
    fd = fopen("/homes/dan/625/wiki_dump.txt", "r");

    // Loop through the input file in chunks of THREADS lines
    for (k = 0; k < MAX_LINES; k += THREADS) {
        // Initialize thread data
        for (i = 0; i < THREADS; i++) {
            data[i].max = 0;
            line[i] = (char*)calloc(LINE_SIZE, sizeof(char));
            // Read a line from the input file
            err[i] = fscanf(fd, "%[^\n]\n", line[i]);
            // If we've reached the end of the file, break out of the loop
            if (err[i] == EOF) {
                break;
            }
            // Set the line data for this thread
            data[i].line = line[i];
        }

        // Create a thread for each line
        for (i = 0; i < THREADS; i++) {
            rc = pthread_create(&threads[i], NULL, process_lines, (void*)&data[i]);
            if (rc != 0) {
                fprintf(stderr, "Failed to create thread %d\n", i);
                exit(1);
            }
        }

        // Wait for each thread to finish and output the results
        for (i = 0; i < THREADS; i++) {
            rc = pthread_join(threads[i], NULL);
            if (rc != 0) {
                fprintf(stderr, "Failed to join thread %d\n", i);
                exit(1);
            }
            printf("%d: %d\n", j++, data[i].max);
            free(line[i]);
        }
    }

    // Close the input file
    fclose(fd);

    return 0;
}
