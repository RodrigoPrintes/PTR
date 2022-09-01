/*
    * gera a derivada apartir do espaço de estado xdet = f(x,u) = x_ponto;
*/

#include "matrix.h"
#include <math.h>



Matrix robo_xdet(Matrix x, Matrix u){

    Matrix x_aux;

    x_aux.ncols= 2;
    x_aux.nlins= 3;

    matrix_value(x_aux,0,0,cos(matrix_getValue(x,2,0)));
    matrix_value(x_aux,1,0,sin(matrix_getValue(x,2,0)));

    matrix_value(x_aux, 2,0,0);
    matrix_value(x_aux, 0,1,0);
    matrix_value(x_aux, 1,1,0);
    matrix_value(x_aux, 2,0,0);
    matrix_value(x_aux, 2,1,0);

    return matrix_mult(x_aux,u);
}