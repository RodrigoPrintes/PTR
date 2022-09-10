/*
	context.c: Context Switching implementation
	Author: Andre Cavalcante
	last change: july, 2022
	License: CC BY-SA
*/

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#include "context.h"


static jmp_buf env;
static corrotine_t *corrot;
static unsigned int sz;

void ctx_init(unsigned int size, corrotine_t corrotines[size]) {
	corrot = corrotines;
	sz = size;
}

void ctx_run() {
	int ret, ant=0;

	ret = setjmp(env);
	if(ret == 0) {
		puts("Starting run()");
		ant = 1;
		if(corrot[0])
			corrot[0]();
		return;
	} else {
		printf("Returned de %d\n", ant);
		ant = ret;
	}
	
	if(corrot[ret-1])
		corrot[ret-1]();
	
}

void ctx_yield(int next) {
	longjmp(env, next);
}
