#ifndef _ROBO_CONTROLLER_H
#define _ROBO_CONTROLLER_H

#include <semaphore.h>
#include "matrix.h"

Matrix controller_v(Matrix y,Matrix Ym, Matrix Ym_det);
void* controller_thread(void *args);

#endif