/* CS261 - HW1 - Program4.c */
/* Name: Nicholas Milford
 * Date: 4/6/2017
 * Solution Description: creates a sortable hash code from the student's initials, uses that to sort
 */

#import <stdlib.h>
#import <stdio.h>
#import <time.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student *students, int n){
	int i, j;
	for(i = 0; i < n; i++){
		struct student *min = students + i;
		int minVal = (int)(min->initials[0]) * 100 + (int)min->initials[1];
		
		for(j = i+1; j < n; j++){
			/*get hash code*/
			int curVal = (int)(students[j].initials[0]) * 100 + (int)students[j].initials[1];
			if(curVal < minVal){
				minVal = curVal;
				min = students + j;
			}
		}
		
		struct student temp = students[i];
		students[i] = *min;
		*min = temp;
	}
}

int main(int argc, char **argv){
	struct student *st = 0;
	
	/*declare an integer n and assign it a value*/
	int n = 20;	

	srand(time(NULL));
	
	/*Allocate memory for n students using malloc*/
	st = (struct student *)malloc(sizeof(struct student) * n);
	
	/*Generate random IDs and scores for the n students, using rand()*/
	int i;
	for(i = 0; i < n; i++){
		st[i].initials[0] = rand() % 26 + 'A';
		st[i].initials[1] = rand() % 26 + 'A';
		st[i].score = rand() % 101;
	}

	/*Print the contents of the array of n students*/
	if(!n){
		puts("No students");
	}
	for(i = 0; i < n; i++){
		printf("%d. %c%c %d\n", i+1, st[i].initials[0], st[i].initials[1], st[i].score);
	}

	/*Pass this array along with n to the sort() function*/
	sort(st, n);

	/*print the contents of the array of n students*/
	puts("\nSorted by initials:");
	if(!n){
		puts("No Students");
	}
	for(i = 0; i < n; i++){
		printf("%d. %c%c %d\n", i+1, st[i].initials[0], st[i].initials[1], st[i].score);
	}
		
	free(st);

	return 0;
}
