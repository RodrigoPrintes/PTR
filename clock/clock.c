/*****************************************************************************/
/**** FTL066 - Programação de Sistemas de Tempo Real                      ****/
/**** Prof. André Cavalcante                                              ****/
/**** Data: 22/11/2016                                            		  ****/
/**** Descrição: Gera um clock				                              ****/
/*****************************************************************************/

/* Include */

#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "monitor.h"

/* Defines */

/* Variaveis Globais */

/*
    Thread que gera o clock e coloca no buffer
*/
void* gen_clock(void* p)
{
	
	struct timespec start, stop;
	struct timespec* tp_start = &start;
	struct timespec* tp_stop = &stop;

    long ideal, real, aux;
    long maxtime = *(long *)p;

    syslog(LOG_DEBUG, "[CLOCK]: Start");
    
    /*faz o que tem o que fazer*/
   
    ideal = 0;
    real = 0;

	/*reset a contagem*/
   	clock_gettime(CLOCK_REALTIME, tp_start);
	   	
    do {
    	/*suspende a thread por 1ms*/
    	usleep(1000);
    	
    	/*pega o tempo atual*/
    	clock_gettime(CLOCK_REALTIME, tp_stop);
    	
    	/*calcula o tempo ideal e o tempo real*/
    	ideal++;
    	aux = (tp_stop->tv_sec*1000000000 + tp_stop->tv_nsec) - 
    				(tp_start->tv_sec*1000000000 + tp_start->tv_nsec);
    	real = real+aux;
    	
    	/*manda para o display*/
    	monitor_addtime(ideal*1000*1000, real);    

    	/*reset do tempo*/
	   	clock_gettime(CLOCK_REALTIME, tp_start);
	   	
    } while(ideal < maxtime);
    
    /*encerra a thread display*/
    ideal = -1;
    real = -1;
    monitor_addtime(ideal, real);
    
    syslog(LOG_DEBUG, "[CLOCK]: Stop");
	
    /*acaba a thread*/
    pthread_exit(0);

    return 0;
}

