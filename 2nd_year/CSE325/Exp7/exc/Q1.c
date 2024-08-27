#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

pthread_mutex_t mutex;
int buffer[BUFFER_SIZE];
int count = 0;

void produce(int item) {
    buffer[count] = item;
    count++;
}

int consume() {
    count--;
    return buffer[count];
}

void* producer() {
    int item = 1;
    int i = 10;
    while (i > 0) {
        pthread_mutex_lock(&mutex);
        if (count == 0 || count < BUFFER_SIZE) {
//        if (count == 0) {
            produce(item);
            printf("Produced: %d, Count: %d\n", item, count);
            item++;
        }
        sleep(1);
        pthread_mutex_unlock(&mutex);
        i--;
    }
}

void* consumer() {
    int i = 10;
    while (i > 0) {
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            int item = consume();
            printf("Consumed: %d, Count: %d\n", item, count);
        }
        sleep(1);
        pthread_mutex_unlock(&mutex);
        i--;
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
