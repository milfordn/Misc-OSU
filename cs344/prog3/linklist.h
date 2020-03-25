#ifndef H_LINKLIST
#define H_LINKLIS

#define T_LL int

struct Llink{
	T_LL value;
	struct Llink * next;
};
struct LList{
	struct Llink * start;
	int size;
};

void initLL(struct LList *);
void freeLL(struct LList *);
int isEmptyLL(struct LList *);
void pushLL(struct LList *, T_LL);
void rmNextLink(struct Llink *);
T_LL firstLL(struct LList *);

#endif
