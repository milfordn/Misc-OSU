#ifndef BST
#define BST

struct Node {
	int val;
	struct Node *left;
	struct Node *right;
};

struct Tree {
	struct Node *root;
	int size;
};

struct Tree *newTree();
struct Node *newNode(int);
void verifyNode(struct Node *);
void verifyTree(struct Tree *);
struct Node *addNode(struct Node *n, int val);
void addTree(struct Tree *, int);
int containsNode(struct Node *, int);
int containsTree(struct Tree *, int);
struct Node *leftMostChild(struct Node *);
struct Node *removeLeftMost(struct Node *);
struct Node *removeNode(struct Node *, int);
void removeTree(struct Tree *, int);
int heightTree(struct Tree *);
int heightNode(struct Node *);


#endif
