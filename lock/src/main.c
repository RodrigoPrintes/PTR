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
		buffer_append(buf, data);
		buffer_print(buf);
	}
}

void *consumer(void *buf) {
	printf("consumer()\n");

	int data;
	for(;;) {
		buffer_take(buf, &data);
		buffer_print(buf);
		consume(data);
	}
}

int main(int argc, char **argv) {
	pthread_t cons_hdl;
	pthread_t prod_hdl;

	buffer_t buf;

	buffer_init(&buf);

	pthread_create(&cons_hdl, NULL, consumer, &buf);
	pthread_create(&prod_hdl, NULL, producer, &buf);

	pthread_join(cons_hdl, NULL);
	pthread_join(prod_hdl, NULL);

	buffer_destroy(&buf);

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
