#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char ** argv){
	
	if(argc < 1){
		puts("your bad");
	}

	int amt = atoi(argv[1]);

	char * buffer = malloc(sizeof(char) * (amt + 1));
	buffer[--amt] = '\0';
	srand(time(NULL));
	for(; amt >= 0; amt--){
		int val = rand() % 27;
		if(val == 26) buffer[amt] = ' ';
		else buffer[amt] = 'A' + val;
	}

	puts(buffer);
	return 0;
}
