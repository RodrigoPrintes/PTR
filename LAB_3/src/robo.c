

/*Recebe u da linearização e cospe y e x
-> (xc,yc) posição do centro de massa do robo e teta a sua orientação
*/
#include <math.h>
#include "matrix.h"

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

Matrix robo_xdet(Matrix x, Matrix u){

    Matrix x_aux;

    x_aux.ncols= 2;
    x_aux.nlins= 3;

    matrix_value(x_aux,0,0,cos(X3(x,2,0)));
    matrix_value(x_aux,1,0,sin(X3(x,2,0)));

    matrix_value(x_aux, 2,0,0);
    matrix_value(x_aux, 0,1,0);
    matrix_value(x_aux, 1,1,0);
    matrix_value(x_aux, 2,0,0);
    matrix_value(x_aux, 2,1,0);

    return matrix_mult(x_aux,u);
}


Matrix x_al(double xc, double yc, double teta){
    Matrix x; x.ncols = 1; x.nlins = 3;

    matrix_value(x, 0, 0, xc);
    matrix_value(x, 0, 1, yc);
    matrix_value(x, 0, 2, teta);

    return x;
}
Matrix x( Matrix x_det, double limInf, double limSup){

    return matrix_integral(limInf,limSup,x_det);

}


