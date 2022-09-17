#include <math.h>
#include "matrix.h"
#include <time.h>
#include "mutexes.h"
#include <stdio.h>
#include "robo_controller.h"
#include <semaphore.h>

#define ALPHA1 2.9
#define ALPHA2 3.1

double x_ref(double t){
    if( t < 0 && t > 4*M_PI)
        return 0;   

    else if(t>=0 && t < 2*M_PI)
        return 0.5 - 0.5*cos(t);

    else    
        return -0.5+cos(t) ;
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
    Matrix ref = matrix_zeros(1,2);
   
    matrix_value(ref,0,0, x_ref(t));
    matrix_value(ref,0,1, y_ref(t));

    return matrix_transposta(ref);
}

Matrix robo_ym_det(Matrix ref, double t, Matrix Ym){
  
    Matrix ym_det = matrix_zeros(1,2);
    
    matrix_value(ym_det, 0, 0, ALPHA1*(matrix_getValue(ref,0,0)-matrix_getValue(Ym,0,0)));
    matrix_value(ym_det, 0, 1, ALPHA2*(matrix_getValue(ref,1,0)-matrix_getValue(Ym,1,0)));
    
    return matrix_transposta(ym_det); 
}

Matrix robo_ym(Matrix ym_det, double limInf, double limSup){

   return matrix_integral(limInf,limSup,ym_det);
}

Matrix robo_newYm(Matrix ym, Matrix ym_dot){
    Matrix m   = matrix_zeros(2,1);

    matrix_value(m, 0, 0 , matrix_getValue(ym, 0 , 0 ) + matrix_getValue(ym_dot, 0 , 0 ) );
    matrix_value(m, 1, 0 , matrix_getValue(ym, 1 , 0 ) + matrix_getValue(ym_dot, 1 , 0 ) );

    return m;
}

void ref_thread(void* args, int tmax, sem_t *produterRef, sem_t *consomerRef) {

    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos

    struct timespec ts1, ts2, ts3={0};
    
    Matrix ref = matrix_zeros(2,1);

    //FILE *pfile;
    //char word[20];
    //pfile = fopen("ref.txt","w");

    while(t <= tmax) {

        clock_gettime(CLOCK_REALTIME, &ts1);

        sem_wait(produterRef);


        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        ref = robo_ref(tm);
        // fprintf(pfile,"%f," ,x_ref(tm));
        // fprintf(pfile,"%f\n",y_ref(tm));
    
        mutexes_setRef(ref);
    
        sem_post(consomerRef);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    // fclose(pfile); 
}

void modeloRef(void*args, int tmax, sem_t *produterYm, sem_t *consomerYm, sem_t *produterYmdot, sem_t *consomerYmdot, sem_t *consomerRef, Matrix ref ){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos

    struct timespec ts1, ts2, ts3={0};

  
    Matrix ym  = matrix_zeros(2,1);
    Matrix ym_dot = matrix_zeros(2,1);
 
    // FILE *pfile;
   // char word[20];
   // pfile = fopen("ref.txt","w");

    while(t <= tmax) {

        clock_gettime(CLOCK_REALTIME, &ts1);

        sem_wait(consomerRef);
        sem_wait(produterYm);
        sem_wait(produterYmdot);

        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        // ref = robo_ref(tm);
        
        // fprintf(pfile,"%f," ,x_ref(tm));
        // fprintf(pfile,"%f\n",y_ref(tm));

        ym_dot = robo_ym_det(ref,tm,ym);
        ym = robo_newYm(ym,ym_dot);

        // mutexes_setY(Y);

        mutexes_setYmdot(ym_dot);
        mutexes_setYm(ym);

        sem_post(consomerRef);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    // fclose(pfile);
} 