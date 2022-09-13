#define BUFFER_SIZE 2


/** circular buffer */
typedef struct buffer{
  unsigned int  data[BUFFER_SIZE];
  unsigned int  size;
  unsigned int  in;
  unsigned int  out;
} buffer_circ_t;


int buffer_add(buffer_circ_t *b,int data);

int buffer_remove(buffer_circ_t *b, int *data);

void buffer_print(buffer_circ_t *b);

/*
#define CIRCULAR_BUFFER_DECLARE(b)  \
        buffer_circ_t b = {         \
          .data = {0},                 \
          .size = 0,                  \
          .in = 0,                 \
          .out = 0,                 \
        }*/

int buffer_init(buffer_circ_t *b);

