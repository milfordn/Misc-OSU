#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//#define TRACE

#define ENC_CLIENT_ID 'e'
#define ENC_SERVER_ID 'E'
#define DEC_CLIENT_ID 'd'
#define DEC_SERVER_ID 'D'

#define FLAG_READ_KEY 1
#define FLAG_READ_TXT 2
#define FLAG_READ_ID 4

#define TERMINATOR_K '#'
#define TERMINATOR_T '$'
#define TERMINATOR_I '%'
#define TERMINATOR_E '!'

#if (PROGRAM_ID == ENC_CLIENT_ID)
#define MESSAGE_HEADER "ENCODING CLIENT: "
#endif

#if (PROGRAM_ID == DEC_CLIENT_ID)
#define MESSAGE_HEADER "DECODING CLIENT: "
#endif

#if (PROGRAM_ID == ENC_SERVER_ID)
#define MESSAGE_HEADER "ENCODING SERVER: "
#endif

#if (PROGRAM_ID == DEC_SERVER_ID)
#define MESSAGE_HEADER "DECODING SERVER: "
#endif

#define BUFFER_SIZE 131072 //1024 + message terminator + null terminator
#define ID_SIZE 2 //1 + null terminator

const char TERMINATORS[5] = {TERMINATOR_K, TERMINATOR_T, TERMINATOR_I, TERMINATOR_E, '\0'};
const char ERROR_MESSAGE[2] = {TERMINATOR_E, '\0'};

char getTerminator(char * buffer){
	return buffer[strcspn(buffer, TERMINATORS)];
}

void writeToSocket(int sockFD, char * buffer){
	int charsWritten = 0;
	int len = strlen(buffer);
	while(charsWritten < len){
		int tempWritten = send(sockFD, buffer + charsWritten, len - charsWritten, 0);
		if(tempWritten < 0) {
			perror(MESSAGE_HEADER);
			perror("ERROR writing to socket");
			exit(0);
		}
		else{
			charsWritten += tempWritten;
		}
	}
}

void getIllegalChars(char * buffer){
	char c;
	int i;
	#ifdef TRACE
	puts("STARTING ILLLEGAL CHAR BUILDER");
	#endif

	for(c = 1, i = 0; c < ' '; c++, i++) //insert c++ joke here
		buffer[i] = c;

	#ifdef TRACE
	printf("I: %d\n", i);
	#endif

	for(c = ' ' + 1; c < 'A'; c++, i++)
		buffer[i] = c;

	#ifdef TRACE
	printf("I: %d\n", i);
	#endif

	for(c = 'Z' + 1; c < 127; c++, i++)
		buffer[i] = c;

	#ifdef TRACE
	printf("I: %d\n", i);
	#endif

	buffer[i] = '\0';

	#ifdef TRACE
	printf("DONE BUILDING ILLEGAL CHARS\n");
	//printf("BUILT ILLEGAL CHARS LIST: %s\n", buffer);
	#endif
}

//returns number of characters until the terminator
//to get the number of characters read, call strlen() on the buffer
int readFromSocket(int sockFD, char * buffer, int maxlen){
	int charsRead = 0;
	while(strcspn(buffer, TERMINATORS) == charsRead){
		int tempRead = recv(sockFD, buffer + charsRead, maxlen - charsRead, 0);
		if(tempRead < 0){
			perror(MESSAGE_HEADER);
			perror("ERROR reading from socket");
			exit(0);
		}
		else{
			charsRead += tempRead;
		}
	}

	return strcspn(buffer, TERMINATORS);
}

//leftover parts remain in buffer
int readAll(char * buffer, char  * keyBuffer, char * txtBuffer, char * idBuffer){
	int readFlags = 0;
	int last = 0;

	//while the terminator still exists in the string and the string is not empty
	while( (last = strcspn(buffer, TERMINATORS)) != strlen(buffer) 
		&& strlen(buffer) > 0 
		&& readFlags != (FLAG_READ_TXT | FLAG_READ_KEY | FLAG_READ_ID) ){

		char temp[BUFFER_SIZE];
		memset(temp, BUFFER_SIZE, '\0');

		//if there is more to the string after the terminator
		if(last == BUFFER_SIZE - 1 || buffer[last + 1] != '\0'){
			//copy the rest to a temp array
			strcpy(temp, (buffer + last + 1));
		}

		char * copyBuffer;

		if(buffer[last] == TERMINATOR_T && !(readFlags & FLAG_READ_TXT)){
			#ifdef TRACE
			printf("RECEIVED TEXT\n");
			#endif
			copyBuffer = txtBuffer;
			readFlags |= FLAG_READ_TXT;
		}
		else if(buffer[last] == TERMINATOR_K && !(readFlags & FLAG_READ_KEY)){
			#ifdef TRACE
			printf("RECEIVED KEY\n");
			#endif
			copyBuffer = keyBuffer;
			readFlags |= FLAG_READ_KEY;
		}
		else if(buffer[last] == TERMINATOR_I){
			#ifdef TRACE
			printf("RECEIVED ID\n");
			#endif
			copyBuffer = idBuffer;
			readFlags |= FLAG_READ_ID;
		}
		else if(buffer[last] == TERMINATOR_E){
			#ifdef TRACE
			printf("RECEIVED ERROR\n");
			#endif
			return -1;
		}
		else{
			#ifdef TRACE
			printf("RECEIVED UNIDENTIFIED\n");
			#endif
			return -1;
		}	

		//buffer[last] = '\0'; //remove terminating char
		memcpy(copyBuffer, buffer, last); //save parsed text to output buffer
		memcpy(buffer, temp, BUFFER_SIZE);
		#ifdef TRACE
		printf("SERVER: PARSED %s\n", copyBuffer);
		#endif
	}

	#ifdef TRACE
	printf("EXITING PARSE LOOP\n");
	#endif
	return readFlags;
}

void sendIdentifier(int sockFD){
	char msg[3] = {PROGRAM_ID, TERMINATOR_I, '\0'};
	writeToSocket(sockFD, msg);
}

void sendError(int sockFD){
	char msg[2] = {TERMINATOR_E, '\0'};
	writeToSocket(sockFD, msg);
}

int checkIdentifier(char givenID){
	return (PROGRAM_ID == 'E' && givenID == 'e') || (PROGRAM_ID == 'D' && givenID == 'd');
}

void errorManual(const char * msg, int code){
	perror(msg);
	exit(code);
}

void error(const char * msg) {errorManual(msg, 1);}

FILE * safeOpen(const char * name){
	FILE * fp = fopen(name, "r");
	if(!fp){
		fprintf(stderr, MESSAGE_HEADER);
		fprintf(stderr, "ERROR: could not open file %s\n", name);
		exit(2);
	}
	return fp;
}
