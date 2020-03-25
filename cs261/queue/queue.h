#ifndef QUEUE_H
#define QUEUE_H

//#DEFINE QUEUE_DATA some_data_type

typedef struct queue {
	QUEUE_DATA * dataList;
	int listLen;
	int totalItems, startPos;
} queue;

void q_init(queue * q, int len);
QUEUE_DATA q_pop(queue * q);
int q_push(queue * q, QUEUE_DATA item);
void q_del(queue * q);

#endif
