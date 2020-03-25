#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include "event.h"
#include "queue.h"

#define BUFFER_LEN 32

queue q;
sem_t access, available, using;
pthread_t produceThread, consumeThread;

void * produceLoop(void * _){
	while(1){
		event e = produce();
		sem_wait(&available);
		sem_wait(&access);
		puts("PRODUCE");
		q_push(&q, e);
		sem_post(&access);
		sem_post(&using);
	}
}

void * consumeLoop(void * _){
	while(1){
		sem_wait(&using);
		sem_wait(&access);
		//event e = q_pop(&q);
		sem_post(&access);
		//sem_post(&available);
		//consume(e);
	}
}

int main(int argc, char ** argv){
	sem_init(&access, 0, 1);
	sem_init(&available, 0, BUFFER_LEN);
	sem_init(&using, 0, 0);

	q_init(&q, BUFFER_LEN);

	int succ1 = pthread_create(&produceThread, NULL, produceLoop, NULL);
	int succ2 = pthread_create(&consumeThread, NULL, consumeLoop, NULL);

	getRandom(0, 1);

	if(succ1 || succ2){
		printf("SOMEONE FUCKED UP! %d %d\n", succ1, succ2);
	}
	else{
		for(;;);
	}
	return 0;
}
