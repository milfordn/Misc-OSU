#include "queue.h"
#include <stdlib.h>

void q_init(queue * q, int len){
	q->dataList = malloc(sizeof(QUEUE_DATA) * len);
	q->listLen = len;
	q->startPos = 0;
	q->totalItems = 0;
}

int adjust_position(int req_posn, int start, int queue_len){
	int adj_posn = req_posn + start;
	if(adj_posn > queue_len)
		adj_posn -= queue_len;

	return adj_posn;
}

QUEUE_DATA q_pop(queue * q){
	if(q->totalItems == 0)
		;//And here is where I would throw an exception or something

	QUEUE_DATA item = q->dataList[q->startPos];
	q->startPos = adjust_position(1, q->startPos, q->listLen);
	q->totalItems--;

	return item;
}

int q_push(queue * q, QUEUE_DATA item){
	if(q->totalItems >= q->listLen)
		return 1; //fail case

	q->dataList[adjust_position(q->totalItems, q->startPos, q->listLen)] = item;
	q->totalItems++;

	return 0;
}

void q_del(queue * q){
	free(q);
}
