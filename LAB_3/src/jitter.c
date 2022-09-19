#include "jitter.h"
#include <stdlib.h>

#define VALUE(j,i,v)(j.jitterRef[i]= v)

void jRef(Jitter jitters, int i, double data){

       jitters.jitterRef[i] = data;

}
