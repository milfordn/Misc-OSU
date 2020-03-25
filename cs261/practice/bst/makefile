default: prog

bst.o: bst.c bst.h
	gcc -Wall -ansi -c bst.c

prog: bst.o main.c
	gcc -Wall -ansi -o prog bst.o main.c

clean:
	rm bst.o 
