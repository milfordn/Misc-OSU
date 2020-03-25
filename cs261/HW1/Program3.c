/* CS261 - HW1 - Program3.c*/
/* Name: Nicholas Milford 
 * Date: 4/6/2017
 * Solution Description: uses insertion sort to sort an array of numbers
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void sort(int *numbers, int n){
	int i, j;
	for(i = 0; i < n; i++){
		int min = numbers[i];
		int index = i;

		for(j = i+1; j < n; j++){
			if(numbers[j] < min){
				min = numbers[j];
				index = j;
			}
		}
		
		numbers[index] = numbers[i];
		numbers[i] = min;
	}
}

int main(int argc, char **argv){
	int *numbers;
	int n = 20;

	numbers = (int *)malloc(sizeof(int) * n);

	srand(time(NULL));

	/*fill array*/
	int i;
	for(i = 0; i < n; i++)
		numbers[i] = rand();

	/*print array*/
	puts("Unsorted:");
	for(i = 0; i < n; i++)
		printf("%d. %d\n", i+1, numbers[i]);

	/*sort array*/
	sort(numbers, n);

	/*print sorted array*/
	puts("\nSorted:");
	for(i = 0; i < n; i++)
		printf("%d. %d\n", i+1, numbers[i]);

	return 0;
}
