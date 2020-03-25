default: skipList

test: skipList.c skipList.h main.c
	gcc -Wall -ansi -o "skipTest" main.c skipList.c

skipList: skipList.c skipList.h 
	gcc -Wall -ansi -c skipList.c	
		
clean:
	rm skipTest
	rm *.o
