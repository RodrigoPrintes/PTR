


#ifndef _ROBO_REF_H
#define _ROBO_REF_H

#include "matrix.h"

double x_ref(double t);
double y_ref(double t);
void ref_thread(void *);
Matrix robo_ref(double t);
#endif