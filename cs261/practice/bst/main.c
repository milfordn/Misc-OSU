#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

int main(int argc, char **argv){

	struct Tree *t = newTree();
	assert(t);
	
	verifyTree(t);
	
	srand(time(NULL));

	puts("Starting add...");
	int i;
	for(i = 0; i < 20; i++){
		assert(i == t->size);
		addTree(t, rand() % 101);
		verifyTree(t);
		puts("Add Verified");
	}

	assert(containsTree(t, t->root->val));
	puts("Contains Verified");

	while(t->size > 0){
		removeTree(t, t->root->val);
		verifyTree(t);
		puts("Remove Verified");
	}

	return 0;
}
