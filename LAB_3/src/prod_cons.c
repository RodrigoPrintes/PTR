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
				buffer_add(buf, data);
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
				buffer_remove(buf, &data);
				buffer_print(buf);
			sem_post(&exclusao);
		sem_post(&cheio);

		consume(data);
	}
}



