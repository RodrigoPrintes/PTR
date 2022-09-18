

/*Recebe u da linearização e cospe y e x
-> (xc,yc) posição do centro de massa do robo e teta a sua orientação
*/
#include "matrix.h"
#include <math.h>
#include "mutexes.h"
#include <time.h>

#define R  0.6*0.5
#define X3(m ,i,j)(matrix_getValue(m,i,j))

Matrix robo_y(Matrix x){

    Matrix x_aux1 = matrix_zeros(3,1),x_aux2 = matrix_zeros(2,2);

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

Matrix robo_xdet(Matrix x, Matrix U){

    Matrix x_aux = matrix_zeros(3,1);

    matrix_value(x_aux,0,0,cos(X3(x,2,0)));
    matrix_value(x_aux,1,0,sin(X3(x,2,0)));
    matrix_value(x_aux,2,0,0);

    matrix_value(x_aux, 0,1,0);
    matrix_value(x_aux, 1,1,0);
    matrix_value(x_aux, 2,1,1);



    return matrix_mult(x_aux,U);
}

Matrix x_al(double xc, double yc, double teta){
    Matrix x; x.ncols = 1; x.nlins = 3;

    matrix_value(x, 0, 0, xc);
    matrix_value(x, 0, 1, yc);
    matrix_value(x, 0, 2, teta);

    return x;
}

Matrix x( Matrix x_det, double limInf, Matrix x_detAux){
    
   
    Matrix x_aux = matrix_zeros(3,1);

    double x1 = (limInf*matrix_getValue(x_det,0,0)+matrix_getValue(x_detAux,0,0))/2,
           x2 = (limInf*matrix_getValue(x_det,1,0)+matrix_getValue(x_detAux,1,0))/2,
           x3 = (limInf*matrix_getValue(x_det,2,0)+matrix_getValue(x_detAux,2,0))/2;

    matrix_value(x_aux,0,0,x1);
    matrix_value(x_aux,1,0,x2);
    matrix_value(x_aux,2,0,x3);
  


    return x_aux;
}


void *robo_thread(void *args){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 10;      //milissegundos

    struct timespec ts1, ts2, ts3={0};//"0..01"

    Matrix U    = matrix_zeros(2,1);
    Matrix X    = matrix_zeros(3,1);
    Matrix Xdet = matrix_zeros(3,2);
    Matrix XdetAux = Xdet;
    Matrix Y    = matrix_zeros(2,1);
    while(t <= 13000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        mutexes_getU(&U);
        mutexes_getX(&X);
        XdetAux = Xdet;
        // Xdet = robo_xdet(X,U);
        // X = x(Xdet,(t-(t-0.01)),XdetAux);

        // mutexes_setX(X);
        
        // Y = robo_y(X);

        // mutexes_setY(Y);

        clock_gettime(CLOCK_REALTIME, &ts2);

        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    } 
}