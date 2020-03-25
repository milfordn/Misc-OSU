/* CS261 - HW1 - Program2.c */
/* Name: Nicholas Milford
 * Date: 4/6/2017
 * Solution Description: uses structures to store information?
 */

#import <stdlib.h>
#import <stdio.h>
#import <time.h>

struct student{
	char initials[2];
	int score;
};

struct student * allocate(){
	return (struct student *)malloc(sizeof(struct student) * 10);
}

void generate(struct student *students){
	int i;
	for(i = 0; i < 10; i++){
		struct student *temp = students + i;
		temp->initials[0] = rand() % 26 + 'A';
		temp->initials[1] = rand() % 26 + 'A';
		temp->score = rand() % 101;
	}
}

void output(struct student *students){
	int i;
	for(i = 0; i < 10; i++){
		struct student *temp = students + i;
		printf("%i. %c%c %d\n", i+1, temp->initials[0], temp->initials[1], temp->score);
	}
}

void summary(struct student *students){
	int min, max, avg, i;
	max = avg = 0;
	min = 100;
	for(i = 0; i < 10; i++){
		int aScore = students[i].score;

		if(aScore < min)
			min = aScore;

		if(aScore > max)
			max = aScore;
	
		avg += aScore;
	}

	avg /= 10;

	printf("Minimum Score: %d\nMaximum Score: %d\nAverage Score: %d\n", min, max, avg);
}

void deallocate(struct student *stud){
	if(stud)
		free(stud);
}

int main(int argc, char **argv){
	struct student *st = 0;
	
	st = allocate();
	generate(st);
	output(st);
	summary(st);
	deallocate(st);

	return st[1].score;
}
