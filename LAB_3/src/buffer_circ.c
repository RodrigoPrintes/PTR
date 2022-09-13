#include "buffer_circ.h"
#include <stdio.h>
#include <string.h>


int buffer_init(buffer_circ_t *b){
    b->in  = 0;
    b->out = 0;
    b->size= 0;
    memset(b->data, 0 , BUFFER_SIZE*sizeof(int));
}
int buffer_add(buffer_circ_t *b, int data)
{
  // int ret = -1;
  
  // if(b == NULL) {
  //   return(ret);
  // }

  if(b->size < BUFFER_SIZE){
    b->data[b->in] = data;
    b->in  = (b->in+1)% BUFFER_SIZE;
    b->size++;

   // ret = 0;
  }

  return 0;
}
int buffer_remove(buffer_circ_t *b, int *data)
{
  // int ret = -1;
  // if(b == NULL) {
  //   return(ret);
  // }

  if(b->size > 0 ){
    *data = b->data[b->out];
    b->data[b->out] = 0;
    b->out = (b->out+1 ) % BUFFER_SIZE;
    b->size--;

   // ret = 0;
  }

  return 0 ;
}
 

void buffer_print(buffer_circ_t *b) {
    printf("Buffer(in:%d, out:%d, size:%d) [", b->in, b->out, b->size);
    printf("%d", b->data[0]);
    for(int i=1; i<BUFFER_SIZE; i++)
        printf(", %d", b->data[i]);
    printf("]\n");
}