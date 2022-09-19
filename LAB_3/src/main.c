/*	
	author: Mj RD
	date: sep, 2022
	license: CC BY-SA
*/

#include <pthread.h>
#include "mutexes.h"

#include <stdio.h>
#include "jitter.h"
#include "robo_ref.h"
#include "robo_controller.h"
#include "robo_linear.h"
#include "robo.h"
#include "out.h"
#define Tmax 14000 // maximo de execução 14s





int main(int argc, char **argv) {
	puts("init process... wait");
	mutexes_init();
	jitter_init();
	
	pthread_t ref_Thread, modeloRef_Thread, control_Thread, linearThread,roboThread,tprint;

	pthread_create(&ref_Thread,NULL, ref_thread, NULL);
	pthread_create(&modeloRef_Thread, NULL, modeloRef, NULL);
	pthread_create(&control_Thread,NULL, controller_thread, NULL);
	pthread_create(&linearThread,NULL, linear_thread, NULL);
	pthread_create(&roboThread,NULL, robo_thread, NULL);
	pthread_create(&tprint,NULL,saida,NULL);

	pthread_join(ref_Thread,NULL);
	pthread_join(modeloRef_Thread,NULL);
	pthread_join(control_Thread,NULL);
	pthread_join(linearThread,NULL);
	pthread_join(roboThread,NULL);
	pthread_join(tprint,NULL);


	mutexes_destroy();
	puts("end process.\nEstatistics:\n");



	return 0;
}