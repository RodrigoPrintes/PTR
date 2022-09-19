


#ifndef _ROBO_REF_H
#define _ROBO_REF_H

#include "matrix.h"

double x_ref(double t);
double y_ref(double t);


Matrix robo_ym_det(Matrix ref, Matrix Ym);
Matrix robo_ym(Matrix ym, Matrix ym_aux, double t);
void* ref_thread(void* args);
void *modeloRef(void*args);
#endif