/*
    Circular Buffer
*/
#pragma once

#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct buffer {
    int in;
    int out;
    int size;
    int buf[BUFFER_SIZE];
    pthread_mutex_t mut_buffer;
    sem_t cheio;
    sem_t vazio;
} buffer_t;

void buffer_init(buffer_t *b);
void buffer_destroy(buffer_t *b);
void buffer_append(buffer_t *b, int item);
void buffer_take(buffer_t *b, int *item);
void buffer_print(buffer_t *b);