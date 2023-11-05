#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

void *producer(void *arg);
void *consumer(void *arg);

int buffer[BUFFER_SIZE];
sem_t empty, full, mutex;
int in = 0, out = 0;
int iterations = 5;

int main()
{
    pthread_t ptid, ctid;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < iterations; i++) {
        pthread_create(&ptid, NULL, producer, NULL);
        pthread_create(&ctid, NULL, consumer, NULL);

        pthread_join(ptid, NULL);
        pthread_join(ctid, NULL);
    }

    return 0;
}

void *producer(void *arg)
{
    for (int i = 0; i < iterations; i++) {
        int item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        printf("Producer produced: %d\n", item);

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

void *consumer(void *arg)
{
    for (int i = 0; i < iterations; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        printf("Consumer consumed: %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }
}