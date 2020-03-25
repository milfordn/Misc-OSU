#ifndef QUEUE_H
#define QUEUE_H

#include "event.h"

typedef struct queue {
	event * dataList;
	int listLen;
	int totalItems, startPos;
} queue;

void q_init(queue * q, int len);
event q_pop(queue * q);
int q_push(queue * q, event item);
void q_del(queue * q);

#endif
