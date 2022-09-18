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


int main(int argc, char **argv) {
	
	mutexes_init();
	
	pthread_t ref_Thread, control_Thread, linearThread,roboThread;

	pthread_create(&ref_Thread,NULL, ref_thread, NULL);
	pthread_create(&control_Thread,NULL, controller_thread, NULL);
	pthread_create(&linearThread,NULL, linear_thread, NULL);
	pthread_create(&roboThread,NULL, robo_thread, NULL);

	ref_thread(NULL);
	modeloRef(NULL);
	controller_thread(NULL);
	// linear_thread(NULL);
	// robo_thread(NULL);

	mutexes_destroy();
	return 0;
}