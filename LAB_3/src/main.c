/*
	
	author: Rodrigo Printes
	date: may, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include "matrix.h"
#include "integral.h"
#include <pthread.h>


void *printH(void *threadid){
	long id;
	id = (long)threadid;//conversão de void pra long
	printf("Thread %ld: Olá mundo!\n", id);
	pthread_exit(NULL); //finalização da thread
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

	Matrix *xT = NULL; 


	return 0;
}
