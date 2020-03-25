#include "linklist.h"
#include <stdlib.h>

struct Llink *newLink(){
	struct Llink *l = malloc(sizeof(struct Llink));
	l->next = NULL;
	return l;
}

void initLL(struct LList *l){
	l->start = newLink(); //start sentinel;
	l->size = 0;
}

int isEmptyLL(struct LList *l){
	return l->start->next == NULL;
}

void freeLL(struct LList *l){
	struct Llink *k = l->start;
	while(!isEmptyLL(l)) rmNextLink(k);
}

void pushLL(struct LList *l, T_LL val){
	struct Llink *nl = newLink();
	nl->value = val;
	nl->next = l->start->next;
	l->start->next = nl;
	l->size++;
}

void rmNextLink(struct Llink *l){
	struct Llink * toRm = l->next;
	l->next = toRm->next;
	free(toRm);
}

T_LL firstLL(struct LList *l){
	return l->start->next->value;
}


