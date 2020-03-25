#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char **argv){
	char * thing = "thing2";
	char * thung = "thing1";

	int i;
	for( i = 0; strncmp(thing, thung, i) == 0; i++){
		printf("%s == %s at %d bytes\n", thing, thung, i);
	}

	return 0;
}
