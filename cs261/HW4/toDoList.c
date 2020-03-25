#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

    param:  priority    priority of the task
    param:  desc    	pointer to the description string
    pre:    none
    post:   none
	ret: 	a task with description and priority
*/
TYPE createTask (int priority, char *desc) 
{
	TYPE newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*  Save the list to a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file to which the list is saved
    pre:    The list is not empty
    post:   The list is saved to the file in tab-delimited format.
			Each line in the file stores a task, starting with the 
			task priority, followed by a tab character (\t), and 
			the task description.
			
			The tasks are not necessarily stored in the file in 
			priority order. 
	
*/
void saveList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */
	int i;
	for(i = 0; i < heap->size; i++){
		TYPE task = heap->data[i];
		fprintf(filePtr, "%d\t%s\n", task.priority, task.description);
	}
	putchar('\n');
}

/*  Load the list from a file

    param:  heap    pointer to the list
    param:  filePtr	pointer to the file
    pre:    none
    post:   The tasks are retrieved from the file and are added to the list.
	    Refer to the saveList() function for the format of tasks in the file				
*/
void loadList(DynArr *heap, FILE *filePtr)
{
  	/* FIX ME */
		
	while(!feof(filePtr)){
		int priority = 867;
		char desc[100];
		char *temp;

		fscanf(filePtr, "%d\t", &priority);
		fgets(desc, 100, filePtr);
		temp = strchr(desc, '\n');
		if(temp) *temp = '\0';
		if(feof(filePtr)) return;
		addHeap(heap, createTask(priority, desc));
	}
}

/*  Print the list

    param:  heap    pointer to the list
    pre:    the list is not empty
    post:   The tasks from the list are printed out in priority order.
	    The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
  	/* FIX ME  */
	int i = 0;
	sortHeap(heap);

	/*reverse array*/
	for(i = 0; i < heap->size/2; i++){
		swapDynArr(heap, i, heap->size-(i+1));
	}

	for(i = 0; i < heap->size; i++){
		TYPE task = heap->data[i];
		printf("%s\n\n", task.description);
	}
}

/*  Compare two tasks by priority

    param:  left    first task
    param:  right 	second task
    pre:    none
    post:   none
    ret: 	-1 if priority of left < priority of right
		1 if priority of left > priority of right
		0 if priority of left = priority of right
*/
int compare(TYPE left, TYPE right)
{
	if (left.priority < right.priority)
		return -1;
	else if (left.priority > right.priority)
		return 1;
	else
		return 0;
}
