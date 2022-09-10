/*****************************************************************************/
/**** FTL066 - Programação de Sistemas de Tempo Real                      ****/
/**** Prof. André Cavalcante                                              ****/
/**** Data: 22/11/2016                                            		  ****/
/**** Descrição: Mostra os dados no video                                 ****/
/*****************************************************************************/

/* Include */

#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <pthread.h>

#include "main.h"
#include "monitor.h"

/* Defines */

/* Variaveis Globais */

char sbuf[80];

/*
    Thread que pega os valores e mostra no vídeo
*/
void* display(void* p)
{
	long dif;
    aTime dados;

    syslog(LOG_DEBUG, "[DISPLAY]: Start");
    
    /*tempo para as outras tarefas iniciarem antes dessa - 10ms*/
    usleep(10000);
    
    
    /*faz o que tem o que fazer*/
   
    syslog(LOG_DEBUG, "[DISPLAY]: Esperando dados");

	puts("Ideal(ns)  Real(ns)  Dif(ns)");

    do {
        /*pega os dados*/
        dados = monitor_gettime();
        dif = dados.ideal-dados.real;

		/*formata os dados*/
       	sprintf(sbuf, "%ld  %ld  %ld\n",
                dados.ideal, 
                dados.real,
                (dif<0)?-dif:dif
       	);
            
		/*mostra no video*/
        printf("%s", sbuf);
            
		/*tempo para as outras tarefas executarem suas funções - 1ms*/
    	usleep(1000);
    }while(dados.ideal>=0);
    
    syslog(LOG_DEBUG, "[DISPLAY]: Stop");
	
    /*acaba a thread*/
    pthread_exit(0);

    return 0;
}

