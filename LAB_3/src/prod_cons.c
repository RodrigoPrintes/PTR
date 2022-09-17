#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "buffer_circ.h"

sem_t exclusao;
sem_t cheio;
sem_t vazio;

/*Produtores*/
sem_t producerRef, procudeY, produceYm, produceYmdot, produceV, produceX, produceU;
/*Consumidores*/
sem_t consumerRef, consumerY, consumerYm, consumeYmdot, consumeV, consumeX, consumeU;


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
	static double data = 0;

	msleep(random() % 3000);
	data++;
	// printf("produce(): %f\n", data);
	return data;
}

void consume(double data) {
	// printf("consume(): %f\n", data);
	msleep(random() % 3000);
}

void *producer(void *buf) {
	printf("producer()\n");
	
	double data;
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

	double data;
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


void teste() {
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


}