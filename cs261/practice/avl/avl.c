#include "avl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Tree *newTree(){
	struct Tree *val = malloc(sizeof(struct Tree));
	assert(val);
	val->root = 0;
	val->size = 0;
	return val;
}

struct Node *newNode(int val){
	struct Node *new = malloc(sizeof(struct Node));
	assert(new);
	new->left = 0;
	new->right = 0;
	new->val = val;
	new->height = 0;
	return new;
}

int height(struct Node *n){
	if(n) return n->height;
	return -1;
}

void setHeight(struct Node *n){
	int l = height(n->left);
	int r = height(n->right);
	
	if(l >= r)
		n->height = l+1;
	else
		n->height = r+1;
}

void verifyNode(struct Node *n){
	if(!n || (!n->left && !n->right))
		return;

	if(n->left){
		assert(n->left->val < n->val);
		int dh = n->left->height - height(n->right);
		assert(dh <= 1 && dh >= -1);
		verifyNode(n->left);
	}
	if(n->right){
		assert(n->right->val >= n->val);
		int dh = height(n->left) - n->right->height;
		assert (dh <= 1 && dh >= -1);
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
	else if(val > n->val){
		n->right = addNode(n->right, val);
	}
	
	setHeight(n);
	rotate(n);

	int dh = height(n->left) - height(n->right);
	if(!(dh <= 1 && dh >= -1)){
		printf("left height:%d, right height:%d\n", height(n->left), height(n->right));
	}		
	return n;
}

void addTree(struct Tree *t, int val){
	t->root = addNode(t->root, val);
	t->size++;
}

struct Node *leftMostChild(struct Node *n){
	assert(n);
	while(n->left)
		n = n->left;
	return n;
}

struct Node *removeLeftMost(struct Node *n){
	assert(n);
	
	if(n->left){
		n->left = removeLeftMost(n->left);
		return n;
	}
	
	struct Node *temp = n->right;
	free(n);
	return temp;
}

struct Node *removeNode(struct Node *n, int val){
	assert(n);
	if(val < n->val){
		n->left = removeNode(n->left, val);
	}
	if(val > n->val){
		n->right = removeNode(n->right, val);
	}
	else{
		if(n->right){
			n->val = leftMostChild(n->right)->val;
			n->right = removeLeftMost(n->right);
		
		}
		else {
			struct Node *replacement = n->left;
			free(n);
			if(replacement) return rotate(replacement);
			return replacement;
		}
	}

	return rotate(n);
}

void removeTree(struct Tree *t, int val){
	if(!containsTree(t, val)) return;

	t->root = removeNode(t->root, val);
	t->size--;
}

int containsNode(struct Node *n, int val){
	if(!n) return 0;
	assert(n);
	if(val < n->val) return containsNode(n->left, val);
	if(val > n->val) return containsNode(n->right, val);
	return 1;
}

int containsTree(struct Tree *t, int val){
	assert(t);
	return containsNode(t->root, val);
}

struct Node *rotateL(struct Node *n){
	assert(n);
	struct Node *newTop = n->right;
	n->right = newTop->left;
	newTop->left = n;

	setHeight(n);
	setHeight(newTop);
	
	return newTop;
}

struct Node *rotateR(struct Node *n){
	assert(n);
	struct Node *newTop = n->left;
	n->left = newTop->right;
	newTop->right = n;

	setHeight(n);	
	setHeight(newTop);

	return newTop;
}

struct Node *rotate(struct Node *n){
	assert(n);
	setHeight(n);
	int dh = height(n->left) - height(n->right);

	if(dh < -1){ /*Too high on right, rotate left*/
		int heavy = height(n->right->left) - height(n->right->right);
		if(heavy > 0) /*Right child heavy on left*/
			n->right = rotateR(n->right);
		return rotateL(n);
	}
	else if(dh > 1){ /*Too high on left, rotate right*/
		int heavy = height(n->left->left) - height(n->left->right);
		if(heavy < 0) /*left child heavy on right*/
			n->left = rotateL(n->left);
		return rotateR(n);
	}

	setHeight(n);
	return n;
}
