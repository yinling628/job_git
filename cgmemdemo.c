#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f = fopen("/dev/urandom", "rb");  // Open the random device in binary mode
    if (!f) {
        perror("Failed to open /dev/urandom");
        return 1;
    }

    char *data_ptr = NULL;         // Dynamic memory pointer
    size_t total_size = 0;         // Total memory size
    int i = 0;
    const size_t chunk_size = 10 * 1024 * 1024;  // 10MB

    while (1) {
        // 1. Allocate a temporary buffer
        char *temp = malloc(chunk_size);
        if (!temp) {
            perror("Failed to allocate temporary buffer");
            break;
        }

        // 2. Read 10MB of data from the device
        size_t bytes_read = fread(temp, 1, chunk_size, f);
        if (bytes_read != chunk_size) {
            perror("Failed to read data");
            free(temp);
            break;
        }

        // 3. Expand the main memory buffer
        char *new_ptr = realloc(data_ptr, total_size + chunk_size);
        if (!new_ptr) {
            perror("Failed to expand memory");
            free(temp);
            break;
        }
        data_ptr = new_ptr;
        memcpy(data_ptr + total_size, temp, chunk_size);  // Append data
        total_size += chunk_size;

        free(temp);  // Free the temporary buffer

        // 4. Print the current memory consumption
        i++;
        printf("%dmb\n", i * 10);
        fflush(stdout);  // Force flush the output buffer
    }

    // Clean up resources
    free(data_ptr);
    fclose(f);
    return 0;
}
