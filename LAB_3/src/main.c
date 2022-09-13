/*
	
	author: Mj RD
	date: may, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "mutexes.h"
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>

#include "prod_cons.h"
#include <pthread.h>
#include "buffer_circ.h"

// void *printH(void *threadid){
// 	long id;
// 	id = (long)threadid;//conversão de void pra long
// 	printf("Thread %ld: Olá mundo!\n", id);
// 	pthread_exit(NULL); //finalização da thread
// }
// static void print_matrix(const char *const name, const Matrix m) {

// 	printf("%s(%u,%u) = [\n", name, m.nlins, m.ncols);

// 	for(int i = 0; i < matrix_nlins(m); i++) {
// 		printf("\t[%4.4f", matrix_value_1(m, i, 0));
// 		for(int j = 1; j < matrix_ncols(m); j++) {
// 			printf(", %4.4f", matrix_value_1(m, i, j));
// 		}
// 		puts("]");
// 	}
// 	puts("]");
// }





int main(int argc, char **argv) {
	teste();
	return 0;
}
