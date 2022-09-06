

#include "matrix.h"
#include "robo_ydet.h"

Matrix u(Matrix v_t, Matrix x){
   return matrix_mult(L_inversa(x), v_t);     
}
