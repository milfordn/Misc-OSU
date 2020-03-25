#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

struct Tree *newTree(){
	struct Tree *val = malloc(sizeof(struct Tree));
	assert(val);
	val->root = NULL;
	val->size = 0;
	return val;
}

struct Node *newNode(int val){
	struct Node *new = malloc(sizeof(struct Node));
	assert(new);
	new->left = NULL;
	new->right = NULL;
	new->val = val;
	return new;
}

void verifyNode(struct Node *n){
	if(!n || (!n->left && !n->right))
		return;

	if((n->left && n->left->val >= n->val) || 
	   (n->right && n->right->val < n->val))
		printf("Failed at p=%d, l=%d, r=%d\n", n->val, n->left->val, n->right->val);

	if(n->left){
		assert(n->left->val < n->val);
		verifyNode(n->left);
	}
	if(n->right){
		assert(n->right->val >= n->val);
		verifyNode(n->right);
	}
}
	

void verifyTree(struct Tree *t){
	verifyNode(t->root);
}
	

struct Node *addNode(struct Node *n, int val){
	if(!n){
		struct Node *new = newNode(val);
		return new;
	}

	if(val < n->val){
		n->left = addNode(n->left, val);
	}
	else{
		n->right = addNode(n->right, val);
	}
	return n;
}

void addTree(struct Tree *t, int val){
		t->root = addNode(t->root, val);
		t->size++;
}

int containsNode(struct Node *n, int val){
	if(n->val == val)
		return 1;
	else if(!(n->left || n->right))
		return 0;
	else if(val < n->val)
		return containsNode(n->left, val);
	else
		return containsNode(n->right, val);
}

int containsTree(struct Tree *t, int val){
	return containsNode(t->root, val);
}

struct Node *leftMostChild(struct Node *n){
	assert(n);
	while(n->left)
		n = n->left;
	return n;
}

struct Node * removeLeftMost(struct Node *n){
	assert(n);
	struct Node *temp;

	if(n->left){
		n->left = removeLeftMost(n->left);
		return n;
	}

	temp = n->right;
	free(n);
	return temp;
}

struct Node *removeNode(struct Node *n, int val){
	assert(n);
	if(val < n->val){
		n->left = removeNode(n->left, val);
		return n;
	}
	else if(val > n->val){
		n->right = removeNode(n->right, val);
		return n;
	}
	else{
		if(n->right){
			n->val = leftMostChild(n->right)->val;
			n->right = removeLeftMost(n->right);	
			return n;
		}
		else{
			struct Node *replacement = n->left;
			free(n);
			return(replacement);
		}
	}
}

void removeTree(struct Tree *t, int val){
	if(!containsTree(t, val))
		return;

	t->root = removeNode(t->root, val);
	t->size--;
}

int heightTree(struct Tree *t){
	return heightNode(t->root);	
}

int heightNode(struct Node *n){
	if(!n) return 0;
	int l = heightNode(n->left);
	int r = heightNode(n->right);
	if(l < r)
		return l+1;
	else
		return l-1;
}
