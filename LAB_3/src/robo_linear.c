


#include "matrix.h"
#include <math.h>
#include "mutexes.h"
#include <time.h>

#define R  0.6*0.5
#define X3(m ,i,j)(matrix_getValue(m,i,j))

/*
   *
   * Cabeçalho
   * 
*/


Matrix L(Matrix x){
    Matrix L = matrix_zeros(2,2);

    matrix_value(L,0,0,cos(X3(x,2,0)));
    matrix_value(L,1,0,sin(matrix_getValue(x,2,0)));

    matrix_value(L, 0, 1,(-R)*sin(X3(x,2,0)));
    matrix_value(L, 1, 1,R*cos(matrix_getValue(x,2,0)));
    return L;
}

Matrix L_inversa(Matrix x){
    return matrix_inversa(L(x));
}

Matrix robo_ydet(Matrix x, Matrix u){
    return matrix_mult(L(x),u);
}

Matrix robo_ydetLin(Matrix v_t){
   return v_t;
}

Matrix u (Matrix v_t, Matrix x){
   return matrix_mult(L_inversa(x), v_t);     
}

void *linear_thread(void *args){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 20;      //milissegundos

    struct timespec ts1, ts2, ts3={0};

    Matrix V    = matrix_zeros(2,1);
    Matrix X    = matrix_zeros(3,1);
    Matrix U    = matrix_zeros(2,1);
  

    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        mutexes_getX(&X);
        mutexes_getYm(&V);

        U = u(V,X);

        mutexes_setU(U);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    } 
}