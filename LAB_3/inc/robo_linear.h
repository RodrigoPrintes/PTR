#ifndef _LINEAR_ROBO_H
#define _LINEAR_ROBO_H
#include "matrix.h"


Matrix u (Matrix v_t, Matrix x);
void *linear_thread(void *args);
Matrix u (Matrix v_t, Matrix x);
Matrix robo_ydetLin(Matrix v_t);
Matrix robo_ydet(Matrix x, Matrix u);
Matrix L_inversa(Matrix x);
Matrix L(Matrix x);

#endif //"LINEAR_ROBO.H"