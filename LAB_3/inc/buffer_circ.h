/*
    Circular Buffer
*/

#define BUFFER_SIZE 2

typedef struct buffer {
    int in;
    int out;
    int size;
    double buf[BUFFER_SIZE];
} buffer_t;

void buffer_init(buffer_t *b);
void buffer_append(buffer_t *b, double item);
void buffer_take(buffer_t *b, double *item);
void buffer_print(buffer_t *b);
