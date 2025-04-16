#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    void *shared_mem_ptr;
    int shared_mem_id;
    char input_buffer[100];

    // Create or access a shared memory segment with the given key
    shared_mem_id = shmget((key_t)1222, 1024, 0666 | IPC_CREAT);
    if (shared_mem_id == -1) {
        perror("Failed to create/get shared memory");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory identifier: %d\n", shared_mem_id);

    // Attach this process to the shared memory segment
    shared_mem_ptr = shmat(shared_mem_id, NULL, 0);
    if (shared_mem_ptr == (void *)-1) {
        perror("Failed to attach shared memory");
        exit(EXIT_FAILURE);
    }

    printf("Process attached at address: %p\n", shared_mem_ptr);

    // Prompt user for input to write into shared memory
    printf("Enter some data to write: ");
    fflush(stdout);  // Ensure prompt is displayed

    // Read up to 100 bytes from standard input
    ssize_t bytes_read = read(STDIN_FILENO, input_buffer, sizeof(input_buffer) - 1);
    if (bytes_read < 0) {
        perror("Failed to read input");
        exit(EXIT_FAILURE);
    }

    input_buffer[bytes_read] = '\0';  // Null-terminate the string

    // Copy user input into shared memory
    strcpy((char *)shared_mem_ptr, input_buffer);

    printf("You wrote: %s\n", (char *)shared_mem_ptr);

    return 0;
}
