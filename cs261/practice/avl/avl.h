#ifndef AVL
#define AVL

struct Node {
	int val;
	struct Node *left, *right;
	int height;
};

struct Tree {
	int size;
	struct Node *root;
};

void verifyTree(struct Tree *);
void verifyNode(struct Node *);

struct Node *newNode(int);
struct Tree *newTree();

struct Node *addNode(struct Node *, int);
void addTree(struct Tree *, int);
struct Node *removeNode(struct Node *, int);
void removeTree(struct Tree *, int);
int containsNode(struct Node *, int);
int containsTree(struct Tree *, int);

struct Node *rotateL(struct Node *);
struct Node *rotateR(struct Node *);
struct Node *rotate(struct Node *);
struct Node *leftMostChild(struct Node *);
struct Node *removeLeftMost(struct Node *);
void setHeight(struct Node *);
int height(struct Node *);

#endif
