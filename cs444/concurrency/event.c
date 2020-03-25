#include "event.h"
#include <stdio.h>
#include <unistd.h>
#include "whichRand.h"

int getRandom(int lower, int upper) {
	return rand(lower, upper);
}

void consume(event item){
	sleep(item.wait);
	printf("%d\n", item.print);
}

event produce(){
	event toReturn;
	sleep(getRandom(3, 8));
	toReturn.print = getRandom(0, 100);
	toReturn.wait = getRandom(2, 10);
	return toReturn;
}
