#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char print = 0;
char printStack = 0;

void hanoiRecursive(char towA, char towB, char towC, int n){
	if(!n) return;

	if(printStack){	
		int i;
		for(i = n; i < 4; i++){
			putchar('\t');
		}
		printf("hanoiRecursive(%d, %d, %d, %d){\n", towA, towB, towC, n);
	}

	hanoiRecursive(towA, towC, towB, n-1);

	if(print){
		if(printStack){
			int i;
			for(i = n; i < 5; i++){
				putchar('\t');
			}
		}
		printf("Move disk %i from tower %i to tower %i\n", n, towA, towC);
	}

	hanoiRecursive(towB, towA, towC, n-1);

	if(printStack){
		int i;
		for(i = n; i < 4; i++)
			putchar('\t');
		puts("}");
	}
}

int mod(char a, char b){
	if(a < 0) return a + b;
	if(a >= b) return a - b;
}

void move(char diskSpace[], int disk, char towA, char towB){
	
	if(print)
		printf("Move disk %i from tower %i to tower %i\n", disk+1, towA+1, towB+1);

	diskSpace[disk] = towB;
}

void hanoiIterative(n){
	char * disk = calloc(n, sizeof(char));
	memset(disk, 0, n);

	int parity = n % 2 ? -1 : 1;
	
	move(disk, 0, 0, mod(parity, 3));
	while(1){
		int smallestAvailable = 0;
		char onesTower = disk[0];
		char smallestTower;
		int i;
		for(i = 1; i < n; i++){
			if(disk[i] != onesTower){
				smallestAvailable = i;
				smallestTower = disk[i];
				break;
			}
		}

		if(smallestAvailable == 0) return;

		move(disk, smallestAvailable, smallestTower, 3 - (onesTower + smallestTower));
		move(disk, 0, onesTower, mod(onesTower + parity, 3));
	}

	free(disk);
}

int main(int argc, char ** argv){
	if(argc < 3) return -1;

	int n = atoi(argv[1]);
	char method = argv[2][1] == 'i';
	print = argc > 3 && argv[3][1] == 'p';
	printStack = argc > 3 && argv[3][2] == 's';

	struct timespec start;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

	if(method)
		hanoiIterative(n);
	else
		hanoiRecursive(1, 2, 3, n);

	struct timespec end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	long diffInNanos = end.tv_nsec - start.tv_nsec;

	printf("\n----- CPU Time Used: %ld nanoseconds -----\n", diffInNanos);
	return 0;
}
