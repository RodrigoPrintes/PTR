/*
	main.c: Produtor/Consumirdor test program
	author: Andre Cavalcante
	date: agosto, 2022
	license: CC BY-SA
*/

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "buffer.h"

sem_t exclusao;
sem_t cheio;
sem_t vazio;

int msleep(long msec) {
	struct timespec ts;
    int res;

	if(msec < 0) {
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
	
	do {
		res = nanosleep(&ts, &ts);
	}while(res && errno == EINTR);

	return res;
}

int produce(void) {
	static int data = 0;

	msleep(random() % 3000);
	data++;
	printf("produce(): %d\n", data);
	return data;
}

void consume(int data) {
	printf("consume(): %d\n", data);
	msleep(random() % 3000);
}

void *producer(void *buf) {
	printf("producer()\n");
	
	int data;
	for(;;) {
		data = produce();

		sem_wait(&cheio);
			sem_wait(&exclusao);
				buffer_append(buf, data);
				buffer_print(buf);
			sem_post(&exclusao);
		sem_post(&vazio);
	}
}

void *consumer(void *buf) {
	printf("consumer()\n");

	int data;
	for(;;) {
		sem_wait(&vazio);
			sem_wait(&exclusao);
				buffer_take(buf, &data);
				buffer_print(buf);
			sem_post(&exclusao);
		sem_post(&cheio);

		consume(data);
	}
}

/*
void *display(void *buf) {
	printf("display()\n");

	for(;;) {
		sem_wait(&exclusao);
			buffer_print(buf);
		sem_post(&exclusao);
		msleep(500);
	}
}
*/

int main(int argc, char **argv) {
	pthread_t cons_hdl;
	pthread_t prod_hdl;
//	pthread_t disp_hdl;

	buffer_t buf;

	buffer_init(&buf);

	sem_init(&exclusao, 0, 1);
	sem_init(&vazio, 0, 0);
	sem_init(&cheio, 0, BUFFER_SIZE);	

	pthread_create(&cons_hdl, NULL, consumer, &buf);
	pthread_create(&prod_hdl, NULL, producer, &buf);
//	pthread_create(&disp_hdl, NULL, display, &buf);

	pthread_join(cons_hdl, NULL);
	pthread_join(prod_hdl, NULL);
//	pthread_join(disp_hdl, NULL);

	sem_destroy(&cheio);
	sem_destroy(&vazio);
	sem_destroy(&exclusao);	

	return 0;
}

int main0(int argc, char **argv) {
	buffer_t b;
	int data;

	buffer_init(&b);
	buffer_print(&b);

	for(int i=1; i<=6; i++) {
		buffer_append(&b, i);
		buffer_print(&b);
	}

	for(int i=1; i<=5; i++) {
		buffer_take(&b, &data);
		printf("data:%d\n", data);
		buffer_print(&b);
	}

	for(int i=1; i<=6; i++) {
		buffer_append(&b, i);
		buffer_print(&b);
	}

	for(int i=1; i<=5; i++) {
		buffer_take(&b, &data);
		printf("data:%d\n", data);
		buffer_print(&b);
	}

	return 0;
}
