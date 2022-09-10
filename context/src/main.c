/*
	main.c: ADT test program template file
	author: Andre Cavalcante
	date: july, 2022
	license: CC BY-SA
*/

#include <stdio.h>
#include <unistd.h>

#include <context.h>

void f1();
void f2();
void f3();

corrotine_t corrotines[] = {f1, f2, f3};

int main(int argc, char **argv) {
	puts("Starting...");
	
	ctx_init((sizeof(corrotines)/sizeof(corrotines[0])), corrotines);
	ctx_run();
	
	puts("Bye!");  //não deve imprimir nada
	return 0;
}


void f1() {
	puts("I'm in f1()");
	sleep(2);
	ctx_yield(3);
}

void f2() {
	puts("I'm in f2()");
	sleep(1);
	ctx_yield(1);
}

void f3() {
	puts("I'm in f3()");
	sleep(1);
	ctx_yield(2);
}
