/*
    Implementa o buffer circular
*/

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "buffer.h"

void buffer_init(buffer_t *b) {
    b->in = 0;
    b->out = 0;
    b->size = 0;
    memset(b->buf, 0, BUFFER_SIZE*sizeof(int));
    pthread_mutex_init(&(b->mut_buffer), NULL);
    sem_init(&(b->cheio), 0, BUFFER_SIZE);
    sem_init(&(b->vazio), 0, 0);
}

void buffer_destroy(buffer_t *b) {
    b->in = 0;
    b->out = 0;
    b->size = 0;
    memset(b->buf, 0, BUFFER_SIZE*sizeof(int));
    pthread_mutex_destroy(&(b->mut_buffer));
    sem_destroy(&(b->cheio));
    sem_destroy(&(b->vazio));
}

static void append(buffer_t *b, int item) {
    if(b->size < BUFFER_SIZE) {
        b->buf[b->in] = item;
        b->in = (b->in + 1) % BUFFER_SIZE;
        b->size++;
    }
}

void buffer_append(buffer_t *b, int item) {
    sem_wait(&(b->cheio));
    pthread_mutex_lock(&(b->mut_buffer));
        append(b, item);
    pthread_mutex_unlock(&(b->mut_buffer));
    sem_post(&(b->vazio));
}

static void take(buffer_t *b, int *item) {
    if(b->size > 0) {
        *item = b->buf[b->out];
        b->buf[b->out] = 0;
        b->out = (b->out + 1) % BUFFER_SIZE;
        b->size--;
    }
}

void buffer_take(buffer_t *b, int *item) {
    sem_wait(&(b->vazio));
    pthread_mutex_lock(&(b->mut_buffer));
        take(b, item);
    pthread_mutex_unlock(&(b->mut_buffer));
    sem_post(&(b->cheio));
}

static void print(buffer_t *b) {
    printf("Buffer(in:%d, out:%d, size:%d) [", b->in, b->out, b->size);
    printf("%d", b->buf[0]);
    for(int i=1; i<BUFFER_SIZE; i++)
        printf(", %d", b->buf[i]);
    printf("]\n");
}

void buffer_print(buffer_t *b) {
    pthread_mutex_lock(&(b->mut_buffer));
        print(b);
    pthread_mutex_unlock(&(b->mut_buffer));
}
