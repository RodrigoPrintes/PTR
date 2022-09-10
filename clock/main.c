/*****************************************************************************/
/**** FTL066 - Programação de Sistemas de Tempo Real                      ****/
/**** Prof: Andre Luiz Duarte Cavalcante                                  ****/
/**** Descrição: Modulo da simulação                                      ****/
/**** Data: 22/11/2016                                                    ****/
/*****************************************************************************/

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <pthread.h>

#include "monitor.h"
#include "clock.h"
#include "display.h"


/* Prototypes */
void showhelp(void);

/* 
    Programa Principal - Ponto de entrada 
*/
int main(int argc, char * args[])
{
	char c;
    pthread_t tskclock, tskdisplay;
    
    unsigned long maxtime = 1000;
    
    syslog(LOG_DEBUG, "[MAIN]: Start");
    
    /********* Interface ***********/
    
    /*Faz o parse dos argumentos*/
	opterr = 0;				/*ver libc manual*/
	while((c = getopt(argc, args, "t:")) != -1)
	{
		switch(c)
		{
		    case 't':
		        maxtime = atol(optarg);
		        break;
			case 'h':
			case '?':
		        showhelp();
		    	return 1;
		    default:
		    	maxtime = 1000;
		}
	}

    /*testa para ver se os argumentos sao validos*/
	if(!maxtime)
	{
	    showhelp();
	    return 1;
	}
	
	/*imprime os dados para confirmar*/
	printf("Max time = %ld ms\n", maxtime);


    /********* Interface ***********/


    /********* Gerenciamento RT ***********/
    
    /*inicializa os monitores*/
    monitor_init();

    /*cria as threads*/
    pthread_create(&tskclock, NULL, gen_clock, (void *)&maxtime);
    pthread_create(&tskdisplay, NULL, display, NULL);
    
    /*espera as threads terminarem*/
    pthread_join(tskclock, NULL);
    pthread_join(tskdisplay, NULL);
    
    /*finaliza os monitores*/
    monitor_delete();
    
    /********* Gerenciamento RT ***********/

    syslog(LOG_DEBUG, "[MAIN]: Stop \n");

    return 0;	
}

/*
    Mostra mensagem de ajuda na tela
*/
void showhelp(void)
{
    puts("Use: clock [-t time_in_ms] [-h]");
    puts("OPTIONS:");
	puts("\t-t\tsets the time in milliseconds to run the clock app\n\t\tThe default value is 1000");
	puts("\t-h\tshows this help");
}

