#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"

// WARNING: THIS WILL OVERWRITE THE MESSAGE
int encode(char * key, char * msg){
	while(*msg != '\0'){
		if(*msg == ' ') *msg = 'Z' + 1;
		if(*key == ' ') *key = 'Z' + 1;

		if(*msg < 'A' || *msg > 'Z' + 1) return 0; //illegal character
		*msg -= 'A'; //26 based
		*key -= 'A';
		
		*msg += *key;
		*msg %= 27;
		*msg += 'A';
		if(*msg == 'Z' + 1) *msg = ' ';

		msg++; key++;
	}
	return 1;
}

void processRequest(int connection){
	char buffer[BUFFER_SIZE];
	char key[BUFFER_SIZE], txt[BUFFER_SIZE], id[ID_SIZE];

	

	memset(buffer, BUFFER_SIZE, '\0');
	int flags = 0;
	// wait for key and text to be sent
	while(flags != (FLAG_READ_KEY | FLAG_READ_TXT | FLAG_READ_ID)){
		
		#ifdef TRACE
		printf("SERVER: STARTING RECEIVE AND READ LOOP\n");
		#endif

		//read to buffer starting from the end of buffer, because there might be leftovers
		//in there (see readAll in common.h)
		int last = readFromSocket(connection, buffer + strlen(buffer), BUFFER_SIZE);

		#ifdef TRACE
		printf("SERVER: read %s\n", buffer);
		#endif
		int res = readAll(buffer, key, txt, id);
		#ifdef TRACE
		printf("SERVER: leftover in buffer: %s\n", buffer);
		#endif
		if(res == -1){
			error("SERVER: ERROR READING");
		}
		flags |= res;

		#ifdef TRACE
		printf("SERVER: READING STATUS %d\n", flags);
		#endif
	}

	#ifdef TRACE
	printf("SERVER: got key %s\n", key);
	printf("SERVER: got text %s\n", txt);
	printf("SERVER: got ID %s\n", id);
	#endif

	if(!checkIdentifier(id[0])){
		sendError(connection);
	}
	else{
		// Send encoded message back to the client
		encode(key, txt);
		
		#ifdef TRACE
		printf("ENCODED: %s\n", txt);
		printf("RETURNING TO SENDER\n");
		#endif

		writeToSocket(connection, txt);
	}

	close(connection); // Close the existing socket which is connected to the client
}

int main(int argc, char *argv[])
{
	int listenSocketFD, establishedConnectionFD, portNumber, numChildren;
	socklen_t sizeOfClientInfo;
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

	// Accept a connection, blocking if one is not available until one connects
	sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
	
	numChildren = 0;

	while(1){
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
	
		int pid = fork();
		if(!pid){ //child breaks out of loop and continues with communication
			if (establishedConnectionFD < 0) error("ERROR on accept");
			processRequest(establishedConnectionFD);
			exit(0);
		}
		else{
			if(++numChildren >= 5){
				wait();
				numChildren--;
			}
			continue;
		}
	}
	close(listenSocketFD); // Close the listening socket
	return 0;
}

