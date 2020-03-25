#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "common.h"

int main(int argc, char *argv[])
{
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char txtbuffer[BUFFER_SIZE];
	char keybuffer[BUFFER_SIZE];
	char recbuffer[BUFFER_SIZE];
	char illegalbuffer[128];
   
	if (argc < 4) { fprintf(stderr,"USAGE: %s plaintext key port\n", argv[0]); exit(0); } // Check usage & args

	//open files
	FILE * txtfile = safeOpen(argv[1]);
	FILE * keyfile = safeOpen(argv[2]);

	memset(keybuffer, '\0', sizeof(keybuffer)); // Clear out the buffer array
	memset(txtbuffer, '\0', sizeof(txtbuffer)); // Clear out the buffer array
	fgets(keybuffer, BUFFER_SIZE, keyfile);
	fgets(txtbuffer, BUFFER_SIZE, txtfile);

	int keylen = strlen(keybuffer) - 1, txtlen = strlen(txtbuffer) - 1;
	keybuffer[keylen] = '\0';
	txtbuffer[txtlen] = '\0';

	getIllegalChars(illegalbuffer);
	char illegalkey = keybuffer[strcspn(keybuffer, illegalbuffer)];
	char illegaltxt = txtbuffer[strcspn(txtbuffer, illegalbuffer)]; 
	if( illegalkey != '\0' ||  illegaltxt != '\0'){
		#ifdef TRACE
		printf("Potential illegal chars: %c, %c\n", illegalkey, illegaltxt);
		#endif
		error("Illegal character found");
	}

	keybuffer[keylen] = TERMINATOR_K; //get rid of trailing new line
	txtbuffer[txtlen] = TERMINATOR_T; //and add message terminator

	if(keylen < txtlen){
		printf("Error: key '%s' is too short\n", argv[2]);
		exit(1);
	}

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
	{
		fprintf(stderr, MESSAGE_HEADER);
		errorManual(": ERROR connecting", 2);
	}
	
	// Send message to server
	sendIdentifier(socketFD);
	writeToSocket(socketFD, txtbuffer);
	writeToSocket(socketFD, keybuffer);	

	// Get return message from server
	memset(recbuffer, '\0', sizeof(recbuffer)); // Clear out the buffer again for reuse

	charsRead = recv(socketFD, recbuffer, sizeof(recbuffer) - 1, 0); // Read data from the socket, leaving \0 at end
	if(recbuffer[0] == TERMINATOR_E){
		fprintf(stderr, MESSAGE_HEADER);
		error("CLIENT: Received error. Did you try to connect to otp_dec_d?");
	}

	if (charsRead < 0) error("CLIENT: ERROR reading from socket");
	printf("%s\n", recbuffer);

	close(socketFD); // Close the socket
	return 0;
}
