#include <stdio.h>
#include "queue.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char ** argv){
	queue q;
	q_init(&q, 10); 
	
	char command[2];
	char val [50];

	while(1){
		scanf("%s %s", command, val);
		
		if(command[0] == 'u'){
			char * alloc = malloc(sizeof(char) * strlen(val));
			strcpy(alloc, val);
			q_push(&q, alloc);
		}
		else if(command[0] == 'p'){
			char * ret = q_pop(&q);
			puts(ret);
			free(ret);
		}
		else if(command[0] == 'l'){
			printf("%d\n", q.totalItems);
		}
	}
}
