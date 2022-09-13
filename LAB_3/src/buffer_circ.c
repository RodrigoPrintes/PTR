
#include <stdio.h>
#include <string.h>
#include "buffer_circ.h"


void buffer_init(buffer_t *b) {
    b->in = 0;
    b->out = 0;
    b->size = 0;
    memset(b->buf, 0, BUFFER_SIZE*sizeof(double));
}

void buffer_append(buffer_t *b, double item) {
    if(b->size < BUFFER_SIZE) {
        b->buf[b->in] = item;
        b->in = (b->in + 1) % BUFFER_SIZE;
        b->size++;
    }
}

void buffer_take(buffer_t *b, double *item) {
    if(b->size > 0) {
        *item = b->buf[b->out];
        b->buf[b->out] = 0;
        b->out = (b->out + 1) % BUFFER_SIZE;
        b->size--;
    }
}

void buffer_print(buffer_t *b) {
    printf("Buffer(in:%d, out:%d, size:%d) [", b->in, b->out, b->size);
    printf("%f", b->buf[0]);
    for(int i=1; i<BUFFER_SIZE; i++)
        printf(", %f", b->buf[i]);
    printf("]\n");
}

