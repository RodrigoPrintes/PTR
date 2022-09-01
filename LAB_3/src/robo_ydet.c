/*
    * Referente ao derivada de y y_point = L(x)u(t)
*/
#include "matrix.h"
#include <math.h>

#define R  0.6*0.5
#define X3(m ,i,j)(matrix_getValue(m,i,j))

Matrix linear_L(Matrix x){
    Matrix L;
    
    L.ncols = 2;
    L.nlins = 2;

    matrix_value(L,0,0,cos(X3(x,2,0)));
    matrix_value(L,1,0,sin(matrix_getValue(x,2,0)));

    matrix_value(L, 0, 1,(-R)*sin(X3(x,2,0)));
    matrix_value(L, 1, 1,R*cos(matrix_getValue(x,2,0)));
    return L;
}

Matrix robo_ydet(Matrix x, Matrix u){
    return matrix_mult(linear_L(x),u);
}

