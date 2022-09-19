#include <math.h>
#include "matrix.h"
#include <time.h>
#include "mutexes.h"
#include <stdio.h>
#include <stdlib.h>
#include "robo_controller.h"


#define ALPHA1 2.9
#define ALPHA2 3.1

double x_ref(double t){
    if( t < 0 && t > 4*M_PI)
        return 0;   

    else if(t>=0 && t < 2*M_PI)
        return 0.5 - 0.5*cos(t);

    else 
        return -0.5+0.5*cos(t) ;
}

double y_ref(double t){

    if( t < 0 && t > 4*M_PI)
        return 0;  

    else if(t>=0 && t < 2*M_PI)
        return 0.5*sin(t);

    else    
        return -0.5*sin(t) ;
}

Matrix robo_ref(double t){
    Matrix ref = matrix_zeros(2,1);
   
    matrix_value(ref,0,0, x_ref(t));
    matrix_value(ref,1,0, y_ref(t));

    return ref;
}

Matrix robo_ym_det(Matrix ref, Matrix Ym){
  
    Matrix ym_det = matrix_zeros(1,2);
    
    matrix_value(ym_det, 0, 0, ALPHA1*(matrix_getValue(ref,0,0)-matrix_getValue(Ym,0,0)));
    matrix_value(ym_det, 0, 1, ALPHA2*(matrix_getValue(ref,1,0)-matrix_getValue(Ym,1,0)));
    
    return matrix_transposta(ym_det); 
}

Matrix robo_ym(Matrix ym, Matrix ym_aux, double t){

    Matrix m = matrix_zeros(2,1);

    double ym1  =(t)*((matrix_getValue(ym,0,0)+matrix_getValue(ym_aux,0,0))/2),
           ym2  =(t)*((matrix_getValue(ym,1,0)+matrix_getValue(ym_aux,1,0))/2);

    matrix_value(m,0,0,ym1);
    matrix_value(m,1,0,ym2);

    return m;
}

void* ref_thread(void* args) {

    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos

    struct timespec ts1, ts2, ts3={0};

    Matrix ref = matrix_zeros(2,1);
    
    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;

        t = t + T;

        ref = robo_ref(t/1000);
        mutexes_setRef(ref);  
         
        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
 
}  

void *modeloRef(void*args){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos

    struct timespec ts1, ts2, ts3={0};

    Matrix ref    = matrix_zeros(2,1);
    Matrix ym     = matrix_zeros(2,1);
    Matrix ym_aux     = matrix_zeros(2,1);
    Matrix ym_dot = matrix_zeros(2,1);
    Matrix ym_dot_aux = matrix_zeros(2,1);

    while(t <= 14000) {

        clock_gettime(CLOCK_REALTIME, &ts1);


        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        mutexes_getRef(&ref);
        mutexes_getYmdot(&ym_dot_aux);
        mutexes_getYm(&ym_aux);

        ym_dot = robo_ym_det(ref,ym);
        ym = robo_ym(ym_dot,ym_dot_aux,T/1000);

        mutexes_setYmdot(ym_dot);
        mutexes_setYm(ym);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
} 