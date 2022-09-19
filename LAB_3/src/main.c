/*	
	author: Mj RD
	date: sep, 2022
	license: CC BY-SA
*/

#include <pthread.h>
#include "mutexes.h"

#include <stdio.h>

#include "robo_ref.h"
#include "robo_controller.h"
#include "robo_linear.h"
#include "robo.h"

#define Tmax 15000 // maximo de execução 13s



void* print_outs (void* args){
  
    double t = 0;       //tempo calculado
    double tm = 0;      //tempo medido
    double T = 30;      //milissegundos
    struct timespec ts1, ts2, ts3={0};
    
    Matrix ref, ym, ym_dot, V, U, X, Y, Xdot; 

	FILE *pfile;
	pfile = fopen("ArqGrav.csv", "wt");

    while(t <= 14000) {
        clock_gettime(CLOCK_REALTIME, &ts1);
        tm = 1000000 * ts1.tv_nsec - tm;
        t = t + T;

        mutexes_getRef(&ref);
        mutexes_getYm(&ym);
        mutexes_getYmdot(&ym_dot);
        mutexes_getV(&V);
        mutexes_getU(&U);
        mutexes_getX(&X);
        mutexes_getY(&Y);
        mutexes_getXdot(&Xdot);
        fprintf(pfile,"%.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f\n", matrix_getValue(ref,0,0),matrix_getValue(ref,1,0)
												, matrix_getValue(ym,0,0),matrix_getValue(ym,1,0)
												, matrix_getValue(ym_dot,0,0),matrix_getValue(ym_dot,1,0)
												, matrix_getValue(V,0,0),matrix_getValue(V,1,0)
												, matrix_getValue(U,0,0),matrix_getValue(U,1,0)
												, matrix_getValue(X,0,0),matrix_getValue(X,1,0)
												, matrix_getValue(Xdot,0,0),matrix_getValue(Xdot,1,0)
												, matrix_getValue(Y,0,0),matrix_getValue(Y,1,0));

        printf("t = %.4f tm = %.4f",t,tm);
        // printf(		  "%.4f,%.4f, %.4f, ", t, matrix_getValue(ref,0,0),matrix_getValue(ref,1,0));
        // printf("%.4f, %.4f, ", matrix_getValue(ym,0,0),matrix_getValue(ym,1,0));
        // printf("%.4f, %.4f ", matrix_getValue(ym_dot,0,0),matrix_getValue(ym_dot,1,0));
        
		
		// printf("%.4f, %.4f, ", matrix_getValue(V,0,0),matrix_getValue(V,1,0));
        // printf("%.4f, %.4f, ", matrix_getValue(U,0,0),matrix_getValue(U,1,0));
        // printf("%.4f, %.4f, %.4f, ", matrix_getValue(X,0,0),matrix_getValue(X,1,0), matrix_getValue(X,2,0));
        // printf("%.4f, %.4f, %.4f, ", matrix_getValue(Xdot,0,0),matrix_getValue(Xdot,1,0),matrix_getValue(Xdot,2,0));
        // printf("%.4f, %.4f\n", matrix_getValue(Y,0,0),matrix_getValue(Y,1,0));

        clock_gettime(CLOCK_REALTIME, &ts2);
        ts3.tv_sec = 0;
        ts3.tv_nsec = T*1000000 - (ts2.tv_nsec - ts1.tv_nsec);
        nanosleep(&ts3, &ts3);
    }
	fclose(pfile);
    return 0;
} 

int main(int argc, char **argv) {
	
	mutexes_init();
	
	pthread_t ref_Thread, modeloRef_Thread, control_Thread, linearThread,roboThread,tprint;

	pthread_create(&ref_Thread,NULL, ref_thread, NULL);
	pthread_create(&modeloRef_Thread, NULL, modeloRef, NULL);
	pthread_create(&control_Thread,NULL, controller_thread, NULL);
	pthread_create(&linearThread,NULL, linear_thread, NULL);
	pthread_create(&roboThread,NULL, robo_thread, NULL);
	pthread_create(&tprint,NULL,print_outs,NULL);

	pthread_join(ref_Thread,NULL);
	pthread_join(modeloRef_Thread,NULL);
	pthread_join(control_Thread,NULL);
	pthread_join(linearThread,NULL);
	pthread_join(roboThread,NULL);
	pthread_join(tprint,NULL);


	mutexes_destroy();
	return 0;
}