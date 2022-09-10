/*****************************************************************************/
/**** FTL066 - Programação de Sistemas de Tempo Real                      ****/
/**** Prof. André Cavalcante                                              ****/
/**** Data: 22/11/2016                                            		  ****/
/**** Descrição: Monitores para o sistema      							  ****/
/****		     Arquivo de cabeçalho									  ****/
/*****************************************************************************/

#ifndef __MONITOR_H__
#define __MONITOR_H__

/* Incudes */

#include "main.h"

/* Defines */

/* Vars */

/* Prototypes */

/*Inicializa os monitores*/
extern void monitor_init(void);

/*Finaliza os monitores*/
extern void monitor_delete(void);

/*Funções do Monitor para mutexTime*/
extern void monitor_addtime(long ideal, long real);
extern aTime monitor_gettime(void);

#endif

