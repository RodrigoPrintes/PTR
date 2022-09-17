#include "matrix.h"
#include <semaphore.h>
#include <time.h>
#include "mutexes.h"

/*
** recebe as referencias e cospe v(t) e a saida
 */
Matrix controller_v(Matrix y,Matrix Ym, Matrix Ym_det){
    Matrix v;

    v.ncols= 1;
    v.nlins= 2;

    matrix_value(v, 0,0, matrix_getValue(Ym_det,0,0)+alpha1*(matrix_getValue(Ym,0,0) - matrix_getValue(y,0,0)));
    matrix_value(v, 0,0, matrix_getValue(Ym_det,0,1)+alpha2*(matrix_getValue(Ym,0,1) - matrix_getValue(y,0,1)));
    
    return v;
}
void controller_thread(void *args, sem_t *producerV, sem_t *consomerV, sem_t *producerY, sem_t *consomerY,sem_t *produterYmdot, sem_t *consomerYmdot, sem_t *consomerRef){
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 50;      //milissegundos

    struct timespec ts1, ts2, ts3={0};
    
    Matrix V = matrix_zeros(2,1);

    while(t <= tmax) {
        clock_gettime(CLOCK_REALTIME, &ts1);

        sem_wait(consomerV);
        sem_wait(consomerY);
        sem_wait(consomerYmdot);
        sem_wait(producerV);

        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        V = consomerV(tm);
      
        mutexes_setRef(ref);
    
        sem_post(consomerRef);

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
    
}
