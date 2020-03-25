prog: event.o queue.o whichRand.o mt19937.o concurrency.c
	gcc -o prog event.o queue.o whichRand.o mt19937.o concurrency.c -lpthread

clean:
	rm prog event.o queue.o

whichRand.o: whichRand.h whichRand.c
	gcc -c whichRand.c
mt19937.o: mt19937.h mt19937.c
	gcc -c mt19937.c
event.o: event.h event.c
	gcc -c event.c
queue.o: queue.h queue.c
	gcc -c queue.c
