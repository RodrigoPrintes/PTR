




#ifndef _ROBO_H
#define _ROBO_H

#include "matrix.h"

Matrix x( Matrix x_det, double limInf, Matrix x_detAux);
Matrix robo_y(Matrix x);
Matrix robo_xdet(Matrix x, Matrix u);
Matrix robo_x(Matrix X , Matrix xaux, double t);
void *robo_thread(void *args);

#endif