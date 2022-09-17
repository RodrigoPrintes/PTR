/*	
	author: Mj RD
	date: sep, 2022
	license: CC BY-SA
*/

#include "prod_cons.h"
#include "mutexes.h"
#include <time.h>
#include <stdio.h>
#include "robo_ref.h"

#define Tmax 13 // maximo de execução 13s


int main(int argc, char **argv) {
	
	mutexes_init();
	// ref_thread(NULL,Tmax);
	
	return 0;
}