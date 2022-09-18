


#ifndef _ROBO_REF_H
#define _ROBO_REF_H

#include "matrix.h"
#include <semaphore.h>

double x_ref(double t);
double y_ref(double t);


Matrix robo_ym_det(Matrix ref, double t, Matrix Ym);
Matrix robo_ym(Matrix ym_det, double limInf, double limSup);
void* ref_thread(void* args);
void *modeloRef(void*args);
#endif