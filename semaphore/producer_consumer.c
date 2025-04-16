#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void *producer(void *arg)
{
    int item = 1;

    while (produced_count < MAX_ITEMS)
    {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is full
        while (((in + 1) % BUFFER_SIZE) == out)
        {
            pthread_cond_wait(&empty, &mutex);
        }

        if (produced_count >= MAX_ITEMS) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        buffer[in] = item;
        printf("Produced: %d\n", item);
        fflush(stdout);  // Force flush for correct output order in console
        item++;
        in = (in + 1) % BUFFER_SIZE;

        produced_count++;

        pthread_cond_signal(&full);  // Signal consumer that buffer is not empty
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    while (consumed_count < MAX_ITEMS)
    {
        pthread_mutex_lock(&mutex);

        // Wait if buffer is empty
        while (in == out)
        {
            pthread_cond_wait(&full, &mutex);
        }

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        fflush(stdout);
        out = (out + 1) % BUFFER_SIZE;

        consumed_count++;

        pthread_cond_signal(&empty);  // Signal producer that buffer has space
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producerThread, consumerThread;

    // Initialize mutex and condition variables
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    // Create threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
