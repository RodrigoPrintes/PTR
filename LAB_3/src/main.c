/*
	
	author: Rodrigo Printes
	date: may, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include <math.h>

#include "matrix.h"
#include "integral.h"
#include <pthread.h>
#include "robo_xdet.h"
#include "linear_robo.h"
#include "robo_controller.h"
#include "robo_ref.h"
#include "robo.h"

void *printH(void *threadid){
	long id;
	id = (long)threadid;//conversão de void pra long
	printf("Thread %ld: Olá mundo!\n", id);
	pthread_exit(NULL); //finalização da thread
}
static void print_matrix(const char *const name, const Matrix m) {

	printf("%s(%u,%u) = [\n", name, m.nlins, m.ncols);

	for(int i = 0; i < matrix_nlins(m); i++) {
		printf("\t[%4.4f", matrix_value_1(m, i, 0));
		for(int j = 1; j < matrix_ncols(m); j++) {
			printf(", %4.4f", matrix_value_1(m, i, j));
		}
		puts("]");
	}
	puts("]");
}






int main(int argc, char **argv) {

	/* pthread_t t1, t2; //criando t1 e t2 do tipo thread
	int create; //variável que recebe o retorno da função pthread_create()
	long num; //identificador da thread
	num = 1;
	printf("Main: criando a thread %ld\n", num);
	create = pthread_create(&t1, NULL, printH, (void *)num); //criando thread 1
	
	num = 2;
	printf("Main: criando a thread %ld\n", num);
	create = pthread_create(&t1, NULL, printH, (void *)num); //criando thread 2
	printf("Main: finalizando\n");

	*/ 
	

	Matrix m; m.ncols = 3; m.nlins = 3;

	m = matrix_zeros(3,3);
	matrix_value(m,2,0,1);
    print_matrix("M",m);

	

	return 0;
}
