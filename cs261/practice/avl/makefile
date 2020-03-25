default: prog

avl.o: avl.c avl.h
	gcc -Wall -ansi -c avl.c

prog: avl.o main.c
	gcc -Wall -ansi -o prog avl.o main.c

clean:
	rm bst.o
