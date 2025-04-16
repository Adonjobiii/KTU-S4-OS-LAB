#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    void *shared_mem_ptr;
    int shared_mem_id;
    char read_buffer[100];

    // Obtain the shared memory segment using the specified key
    shared_mem_id = shmget((key_t)1222, 1024, 0666);
    if (shared_mem_id == -1) {
        perror("Failed to access shared memory");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory identifier: %d\n", shared_mem_id);

    // Attach the current process to the shared memory
    shared_mem_ptr = shmat(shared_mem_id, NULL, 0);
    if (shared_mem_ptr == (void *)-1) {
        perror("Failed to attach shared memory");
        exit(EXIT_FAILURE);
    }

    printf("Process attached at address: %p\n", shared_mem_ptr);

    // Read and display the content from the shared memory
    printf("Data retrieved from shared memory: %s\n", (char *)shared_mem_ptr);

    return 0;
}
