/*
	main.c: Entrada para a simulação
	author: Andre Cavalcante
	date: agosto, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include <time.h>

#include "mutexes.h"

int main(int argc, char **argv) {
	mutexes_init();


	mutexes_destroy();

	return 0;
}
