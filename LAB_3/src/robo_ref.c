#include <math.h>
#include "matrix.h"
#include <time.h>
#include "mutexes.h"
#include <stdio.h>

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
    Matrix ref = matrix_zeros(1,2);;
    ref.ncols = 2;
    ref.nlins = 1;
   
    matrix_value(ref,0,0, x_ref(t));
    matrix_value(ref,0,1, y_ref(t));

    return matrix_transposta(ref);

}

Matrix robo_ModeloRef(Matrix ref, double t, Matrix Ym){
  
    Matrix ym_det; ym_det.ncols = 2; ym_det.nlins  = 1;

    matrix_value(ym_det, 0, 0, ALPHA1*(matrix_getValue(ref,0,0)-matrix_getValue(Ym,0,0)));
    matrix_value(ym_det, 0, 1, ALPHA2*(matrix_getValue(ref,0,1)-matrix_getValue(Ym,0,1)));

    return matrix_transposta(ym_det); 
}

Matrix robo_ym(Matrix ym_det, double limInf, double limSup){

   return matrix_integral(limInf,limSup,ym_det);
}


void ref_thread(void*) {
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos

    struct timespec ts1, ts2, ts3={0};
    
     Matrix ref = matrix_zeros(2,1);

    while(t <= 13000) {
        clock_gettime(CLOCK_REALTIME, &ts1);

       

        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;
   

        ref = robo_ref(tm);
        matrix_print_name("Ref:", ref); 
        mutexes_setRef(ref);


        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
   
}

