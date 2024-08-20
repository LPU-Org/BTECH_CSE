#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 5

sem_t mutex;
sem_t write_mutex;
int read_count = 0;
int shared_data = 0;
int i = 1;

void* reader() {
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_mutex);
    }
    sem_post(&mutex);

    printf("Reader %d read: %d\n", i++, shared_data);
    // i++;

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&write_mutex);
    }
    sem_post(&mutex);
}

void* writer() {
    sem_wait(&write_mutex);
    
    shared_data++;
    printf("Writer wrote: %d\n", shared_data);
    sem_post(&write_mutex);
}

int main() {
    pthread_t readers[MAX_READERS], writer_thread;
    int reader_ids[MAX_READERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    pthread_create(&writer_thread, NULL, writer, NULL);

    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    printf("Shared Data: %d\n", shared_data);
    
    return 0;
}