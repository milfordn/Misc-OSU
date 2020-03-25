#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>

/*#define DEBUG*/

/* ************************************************************************
Main Function
 ************************************************************************ */
/* Test function:
 param: no parameters
 pre:	no parameres
 post: prints out the contents of the skip list */

void test(){
	puts("starting test");
	int i,j;
	int M;
	struct skipList *slst;
	/*test();*/
	
	srand ( time(NULL) );
	
	slst=(struct skipList *)malloc(sizeof(struct skipList));  /*2*/
	assert(slst);
	
	
	/*  Initialize the skip list */
	#ifdef DEBUG
	printf("Initializing...");
	#endif

 	initSkipList(slst);

	#ifdef DEBUG
	puts("Done");
	#endif

	/*  Add to the skip list  M = 20 random integers in [0,100] */
	M = 20;
	j = 7; /*why is J here?"*/
	i = j;
	
	#ifdef DEBUG
	printf("Adding elements...");
	#endif

        for(i = 0; i < M; i++){
		int randNum = rand() % 101;

		#ifdef DEBUG
		printf(" %d ", randNum);
		#endif
		addSkipList(slst, (double)randNum);
	}

	#ifdef DEBUG
	puts("Done");
	#endif

	
	/*  Print out the contents of the skip list in the breadth-first order, 
            starting from top. 
	    While printing the elements, 
            move to a new line every time you reach the end of one level, 
	    and move down to the lower level of the skip list. 
	    For example, the print out of a skip list with 5 elements 
            should look like
	 
	    7
	    7 14 29
	    3 7 9 14 20
	*/

	#ifdef DEBUG
	puts("Printing...");
	#endif

	printSkipList(slst);

	#ifdef DEBUG
	puts("Done");
	#endif
	
	/* Develop 3 test cases for printing out the contents of skip list 
           after remove function:  
	         int removeSkipList(struct skipList *slst, TYPE e)
	*/
	
	#ifdef DEBUG
	printf("Removing...");
	#endif

        struct skipLink *slink = slst->topSentinel;

	/*remove a top-level link*/
	#ifdef DEBUG
	printf(" Test 1 ");
	#endif
	removeSkipList(slst, slink->next->value);
	
	/*remove a value that probably only exists at the bottom level*/
	#ifdef DEBUG
	printf(" Test 2 ");
	#endif
	while(slink->down != 0) slink = slink->down;
	slink = slink->next;
	removeSkipList(slst, slink->value);

	/*remove an element that doesn't exist anymore*/
	#ifdef DEBUG
	printf(" Test 3 ");
	#endif
	removeSkipList(slst, slink->value);
	
	#ifdef DEBUG
	puts("Done");
	#endif

        /* Develop 3 test cases corresponding to the above 3 test cases
           for printing out the output of contains function when e is equal to
           the elements you removed above:  
		   int containsSkipList(struct skipList *slst, TYPE e) 
	*/
	#ifdef DEBUG
	printf("Contains...");
	#endif
	slink = slst->topSentinel;

	/*contains first value*/
	#ifdef DEBUG
	printf(" Test 1 ");
	#endif
	while(slink->next == 0) slink = slink->down;
	assert(containsSkipList(slst, slink->next->value));

	/*contains a bottom-level value*/
	while(slink->down != 0) slink = slink->down;
	slink = slink->next;
	#ifdef DEBUG
	printf(" Test 2 ");
	#endif
	assert(containsSkipList(slst, slink->value));

	/*contains an element that doesn't exist anymore*/
	removeSkipList(slst, slink->value);
	#ifdef DEBUG
	printf(" Test 3 ");
	#endif
	assert(!containsSkipList(slst, slink->value));

	#ifdef DEBUG
	puts("Done");
	#endif

	#ifdef DEBUG
	printf("Merge...\n");
	#endif

	struct skipList *l1, *l2;
	l1 = malloc(sizeof(struct skipList));
	l2 = malloc(sizeof(struct skipList));
	initSkipList(l1);
	initSkipList(l2);

	for(i = 0; i < 10; i++){
		addSkipList(l1, rand() % 101);
		addSkipList(l2, rand() % 101);
	}

	printSkipList(l1);
	puts("\n");
	printSkipList(l2);
	puts("\n");
	mergeSkipList(l1, l2);
	printSkipList(l1);
}


/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function:
 param: 	no parameters
 pre:	no parameres
 post: output is a random intiger number in {0,1} */
int flipSkipLink(void)
{
	return rand() % 2; 	
}

/* Move to the right as long as the next element is smaller than the input value:
 param: 	current -- pointer to a place in the list from where we need to slide to the right
 param:	e --  input value
 pre:	current is not NULL
 post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	return current;
}


/* Create a new skip link for a value
	param: e	 -- the value to create a link for
	param: nextLnk	 -- the new link's next should point to nextLnk
	param: downLnk -- the new link's down should point to downLnk
	pre:	none
	post:	a link to store the value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	return tmp;
}


/* Add a new skip link recursively
 param: current -- pointer to a place in the list where the new element should be inserted
 param: e	 -- the value to create a link for
 pre:	current is not NULL
 post: a link to store the value */
struct skipLink* skipLinkAdd(struct skipLink * current, TYPE e) {

	struct skipLink *newLink = 0;

	if(current->down == 0){ /*at bottom*/
		newLink = newSkipLink(e, current->next, 0); /*new link is at bottom*/
		current->next = newLink;
	}
	else{
		struct skipLink *downLink = skipLinkAdd(slideRightSkipList(current->down, e), e); /*recursive call, add a link a layer below at the correct location*/
		if(downLink && flipSkipLink()){
			newLink = newSkipLink(e, current->next, downLink);
			current->next = newLink;
		}
	}

	return newLink;
}


/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list:
 param:  slst -- pointer to the skip list
 pre:	slst is not null
 post: the sentinels are allocated, the pointers are set, and the list size equals zero */
void initSkipList (struct skipList *slst) 
{

	slst->size=0;
	slst->topSentinel=(struct skipLink * )malloc(sizeof(struct skipLink));
	assert(slst->topSentinel);
	slst->topSentinel->next=NULL;
	slst->topSentinel->down=NULL;
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *tmp = slst->topSentinel;
	while (tmp != 0) {  /* 2pts */
		tmp = slideRightSkipList(tmp, e); /* 1pt */
		if ((tmp->next != 0) && EQ(e, tmp->next->value)) /* 2pts */
			return 1;
		tmp = tmp->down;  /* 1pt */
	}
	return 0;
}


/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *current, *tmp;
	current = slst->topSentinel; /* 1pts */
	while (current != 0) {  /* 2pts */
		current = slideRightSkipList(current, e);
		if (current->next != 0 && EQ(e, current->next->value)) {  /* 2pts */
			tmp = current->next; /* 2pts */
			current->next = current->next->next;
			free(tmp);    /* 2pts */
			if (current->down == NULL)
				slst->size--;   /* 2pts */
		}
		current = current->down; /* 1pt */
	}
}




/* Add a new element to the skip list:
	param: slst -- pointer to the skip list
	param: e -- element to be added
	pre:	slst is not null
	post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *newLink = skipLinkAdd(slideRightSkipList(slst->topSentinel, e), e);
	if(newLink && flipSkipLink()){	/*add a new layer above the top*/
		struct skipLink *topLink = newSkipLink(e, 0, newLink);
		slst->topSentinel = newSkipLink(0, topLink, slst->topSentinel);
	}
	slst->size++;
}

/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre:	slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst){
	
	return slst->size;
	
}


/* Print the links in the skip list:
	param: slst -- pointer to the skip list
	pre:	slst is not null and slst is not empty
	post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)
{
	struct skipLink *sentinel = slst->topSentinel;
	
	if(slst->size == 0){
		puts("Empty List");
		return;
	}

	while(sentinel != 0){
		struct skipLink *val = sentinel->next;
		
		while(val != 0){
			printf("%.1f ", val->value);
			val = val->next;
		}

		printf("\n");
		sentinel = sentinel->down;
	}
}


/* Merge two skip lists, by adding elements of skip list 2 to skip list 1 
 that are not already contained in skip list 1. 
 The function is also supposed to remove the entire skip list 2 from the memory.
 param: slst1 -- pointer to the skip list 1
 param: slst2 -- pointer to the skip list 2
 pre: slst1 and slst2 are not null, and skip list 1 and skip list 2 are not empty
 post: slst1 points to the merger skip list,  slst2 is null*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)
{

	struct skipLink *slink2 = slst2->topSentinel;

	while(slink2->down != 0) slink2 = slink2->down; /*find bottom of list 2*/
	slink2 = slink2->next; /*skip the sentinel*/

	while(slink2->next != 0){ /*add new items to list 1*/
		if(!containsSkipList(slst1, slink2->value))
			addSkipList(slst1, slink2->value);

		slink2 = slink2->next;
	}
	
	/*free list 2*/
	slink2 = slst2->topSentinel;
	struct skipLink *rowSent = slink2->down;

	do {
		while(slink2->next != 0){ /*free individual link*/
			struct skipLink *temp = slink2;
			slink2 = slink2->next;
			free(temp);
		} /*loop across the row/level/whatever you want to call it*/

		slink2 = rowSent; /*move to the start of the next row*/
		rowSent = slink2->down; 
 
	} while(rowSent != 0);

	free(slst2);
	slst2 = 0;

} /* end of the function */
	


