/* CS261 - HW1 - Program1.c */
/* Name: Nicholas Milford
 * Date: 4/6/2017
 * Solution Description: uh... does what it's supposed to?
 */

#import <stdlib.h>
#import <stdio.h>
#import <time.h>

int foo(int *a, int *b, int c){
	(*a)++;
	(*b)--;
	c = *a - *b;
	return c;
}

int main(int argc, char **argv){
	srand(time(NULL));
	int x, y, z;
	
	x = rand() % 11;
	y = rand() % 11;	/*something something not uniform something unsafe something*/
	z = rand() % 11;

	printf("Before foo: x:%d, y:%d, z:%d\n", x, y, z);
	int temp = foo(&x, &y, z);
	printf("After foo: x:%d, y:%d, z:%d\n", x, y, z);
	printf("Foo returned: %d\n", temp);

	return 0;
}
