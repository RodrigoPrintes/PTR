/*
    * gera a derivada apartir do espaço de estado xdet = f(x,u) = x_ponto;
*/

#include "matrix.h"
#include <math.h>

#define R  0.6*0.5

#define X3(m ,i,j)(matrix_getValue(m,i,j))


Matrix robo_y(Matrix x){

    Matrix x_aux1,x_aux2;

    x_aux1.ncols= 3; x_aux2.ncols= 1; 
    x_aux1.nlins= 2; x_aux2.nlins= 2;

   matrix_value(x_aux1, 0,0,1);
   matrix_value(x_aux1, 0,1,0);
   matrix_value(x_aux1, 0,2,0); 

   matrix_value(x_aux1, 1,0,0);
   matrix_value(x_aux1, 1,1,1);
   matrix_value(x_aux1, 1,2,0);

   matrix_value(x_aux2, 0,0,R*cos(X3(x,2,0)));
   matrix_value(x_aux2, 1,0,R*sin(X3(x,2,0)));


   return matrix_soma(matrix_mult(x_aux1,x),x_aux2); 
}
