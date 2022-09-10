/*
	main.c: test program
	author: Andre Cavalcante
	date: july, 2022
	license: CC BY-SA
*/

#include <setjmp.h>
#include <stdio.h>


void f1();
void f2();
void f3();

jmp_buf env;

int main(int argc, char **argv) {
	puts("Starting...");
	
	int ret = setjmp(env);
	if(!ret) {
		puts("setjmp returned with value 0");
		f1();
	}
	else
		printf("setjmp returned with value %d\n", ret);

	puts("Bye!");
	return 0;
}

void f1() {
	puts("I'm in f1()");
	f2();
	puts("I returned from f2()");
	puts("I'm leaving f1()");
}

void f2() {
	puts("I'm in f2()");
	f3();
	puts("I returned from f3()");
	puts("I'm leaving f2()");
}

void f3() {
	int error = 10;
	puts("I'm in f3()");
	if(error)
		longjmp(env, error);
	puts("I'm leaving f3()");
}
