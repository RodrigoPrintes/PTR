/*****************************************************************************/
/**** FTL066 - Programação de Sistemas de Tempo Real                      ****/
/**** Prof. André Cavalcante                                              ****/
/**** Data: 22/11/2016                                            		  ****/
/**** Descrição: Monitores do sistema                                     ****/
/*****************************************************************************/

/* Includes */

#include <pthread.h>
#include <stdio.h>

#include "main.h"


/***********************************
	Monitores para acesso aos 
	Recursos compartilhados 
 ***********************************/

/*
	Variaveis dos monitores
	bufferes de 1 posicao no paradgma produtor-consumidor
	vou utilizar letras maiusculas para nao confundir com as variaveis locais
*/

aTime fifoTime[MAXFIFOBUFFER];
int head = -1;
int tail = -1;

/* Mutexes */

/*cria e inicializa os mutex*/
pthread_mutex_t _mutexTime = PTHREAD_MUTEX_INITIALIZER;

/*mantem interface com poteiros*/
static pthread_mutex_t* mutexTime = &_mutexTime;

/*
    Inicializa os mutexes
*/
void monitor_init(void)
{
    /*inicializa as variaveis - por hora nada porque as variaveis sao iniciadas pelo compilador*/

    /*inicializa o mutex - por hora nada faz porque o mutex eh iniciado com PTHREAD_MUTEX_INITIALIZER*/  
}

/*
    Finaliza os mutexes
*/
void monitor_delete(void)
{
	pthread_mutex_destroy(mutexTime);
}



/*
	Adiciona um Time (ideal, real)
*/
void monitor_addtime(long ideal, long real)
{
	pthread_mutex_lock(mutexTime);
		tail = (tail + 1) % MAXFIFOBUFFER;
		fifoTime[tail].ideal = ideal;
		fifoTime[tail].real = real;
	pthread_mutex_unlock(mutexTime);
}


/*
	Le um Time [ideal, real]
*/
aTime monitor_gettime(void)
{
	aTime tmp;
	
	pthread_mutex_lock(mutexTime);
		if(head == tail) {
			tmp.ideal = -1;					/*indica nenhum dado*/
			tmp.real = -1;
		} else {
			head = (head + 1) % MAXFIFOBUFFER;
			tmp = fifoTime[head];
		}
	pthread_mutex_unlock(mutexTime);

	return tmp;
}


/***********************************/


