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


int main(int argc, char **argv) {
	
	mutexes_init();
	ref_thread(NULL);
	
	return 0;
}