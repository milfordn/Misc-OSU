#ifndef CONCURRENCY_H
#define CONCURRENCY_H

typedef struct event {
	int print;
	int wait;
} event;

int getRandom();
void consume(event item);
event produce();

#endif
