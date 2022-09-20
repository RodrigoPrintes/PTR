#include "matrix.h"

#include <time.h>
#include "mutexes.h"
#include "jitter.h"

#define ALPHA1 2.9
#define ALPHA2 3.1
/*
** recebe as referencias e cospe v(t) e a saida
 */

Matrix controller_v(Matrix y,Matrix Ym, Matrix Ym_det){

    Matrix v = matrix_zeros(2,1);
    matrix_value(v, 0,0, matrix_getValue(Ym_det,0,0)+ALPHA1*(matrix_getValue(Ym,0,0) - matrix_getValue(y,0,0)));
    matrix_value(v, 1,0, matrix_getValue(Ym_det,1,0)+ALPHA2*(matrix_getValue(Ym,1,0) - matrix_getValue(y,1,0)));
    
    return v;
}

void *controller_thread(void *args){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    int i = 0 ;
    struct timespec ts1, ts2, ts3={0};

    Matrix Y    = matrix_zeros(2,1);
    Matrix V    = matrix_zeros(2,1);
    Matrix YMDOT= matrix_zeros(2,1);
    Matrix YM   = matrix_zeros(2,1);

    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        setJitter_Control(t, ts1.tv_nsec,tm, &i , T);

        tm = (double) ts1.tv_nsec/1000000;
        t = t + T;
      
        mutexes_getY(&Y);
        mutexes_getYm(&YM);
        mutexes_getYmdot(&YMDOT);

        V = controller_v(Y,YM, YMDOT);
        mutexes_setV(V);
      

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    } 
}