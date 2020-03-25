#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//#define TRACE

#define ROOM_NAME_SIZE 15
#define ROOM_COUNT 7
#define ROOM_FILE_HEADER "milfordn.rooms."

#define TYPE_START_ROOM 0
#define TYPE_MID_ROOM 1
#define TYPE_END_ROOM 2
#define TYPE_UNDEFINED -1

char * roomTypes[3];

//Rooms fundamental type
struct connectionType {
	int ID;
	char name[ROOM_NAME_SIZE];
};
struct room {
	char name[ROOM_NAME_SIZE];
	int ID;
	struct connectionType * connections;
	int numConnections;
	int type;
};

//linked list for keeping track of path
struct pathLink{
	char * name;
	struct pathLink *next;	
};
struct path{
	int size;
	struct pathLink *start;
	struct pathLink *end;
};

// ***** STRUCTURE FUNCTIONS START HERE *****


void addPathLink(struct path * p, char * str){
	struct pathLink *new = malloc(sizeof(struct pathLink));
	new->name = str;
	new->next = NULL;

	#ifdef TRACE
	if(!(p->end) || !(p)) printf("OH SHIT WE FUCKED UP");
	#endif

	p->end->next = new;
	p->end = new;
	p->size++;
}

struct path newPath(){
	struct path p;
	struct pathLink *new = malloc(sizeof(struct pathLink));
	new->name = NULL;
	new->next = NULL;

	p.start = new;
	p.end = new;
	p.size = 0;
	return p;
}

void deletePath(struct path *p){
	struct pathLink *pl = p->start;
	while(pl){
		struct pathLink *temp = pl->next;
		free(pl);
		pl = temp;
	}

	p->start = p->end = NULL;
	p->size = 0;
}

struct room newRoom(int id){
	struct room r;
	r.connections = malloc(sizeof(struct connectionType) * 6);
	r.ID = id;
	r.type = TYPE_UNDEFINED;
	r.numConnections = 0;
	memset(r.name, '\0', ROOM_NAME_SIZE);
	
	return r;
}

void deleteRoom(struct room *r){
	free(r->connections);
	r->connections = NULL;
}

void addConnection(struct room * r, char * name){
	strcpy(r->connections[r->numConnections++].name, name);
}

// ***** STRUCTURE FUNCTIONS END HERE *****
//
// ***** ROOM PARSING STARTS HERE *****

//reads a room type as string, converts to room type as enumerator
int getRoomType(char * roomName){
	int i;
	for(i = 0; i < 3; i++){
		if(strcmp(roomTypes[i], roomName) == 0) return i;
	}

	return -1;
}

//parses a room from a file
int readRoom(FILE *f, struct room * r){
	#define SCAN_NAME 0
	#define SCAN_CONNECTION 1
	#define SCAN_TYPE 2
	#define COMPLETE 3

	char line[50];
	line[0] = '\0';

	int currentState = SCAN_NAME;

	#ifdef TRACE
	int lineCount = 0;
	#endif

	//state machine: room.name -> room.connections +> room.type
	//(with a really bad       ^                   v
	//flow chart)              |-------------------|
	do {		
		//read line
		if(fgets(line, 50, f) == NULL){
			#ifdef TRACE
			printf("Successfully read %d lines\n", lineCount);
			#endif
			return 1;
		}

		#ifdef TRACE
		lineCount++;
		#endif

		//scan name
		if(currentState == SCAN_NAME){
			if(sscanf(line, "ROOM NAME: %s", r->name) == 1){

				#ifdef TRACE
				printf("Successfully scanned room name %s\n", r->name);
				#endif
				
				//on success, move to connections
				currentState = SCAN_CONNECTION;
				continue;
			}
		}

		if(currentState == SCAN_CONNECTION){

			char tempName[ROOM_NAME_SIZE];
			memset(tempName, '\0', ROOM_NAME_SIZE);		
			if(sscanf(line, "CONNECTION %*d: %s", tempName) == 0){
				//on failure, move to type
				currentState = SCAN_TYPE;
			}
			else{
				#ifdef TRACE
				printf("Adding Connection %s\n", tempName);
				#endif
				addConnection(r, tempName);
			}

		}

		if(currentState == SCAN_TYPE){

			#ifdef TRACE
			printf("Successfully read %d connections\n", r->numConnections);
			#endif

			char roomTypeTemp[15];
			if(sscanf(line, "ROOM TYPE: %s", roomTypeTemp) != 1){
				return 1;
			}

			r->type = getRoomType(roomTypeTemp);

			#ifdef TRACE
			if(r->type == -1){
				printf("Failed to scan room type %s\n", roomTypeTemp);
			}
			#endif

			//when finished, move to complete
			currentState = COMPLETE;
		}			
	} while(currentState != COMPLETE);

	return 0;
}

//loop through all files in directory, reading rooms from each
void readRoomsDir(char * dirName, struct room rooms[]){
	DIR *d;
	struct dirent *dir;
	d = opendir(dirName);

	char pname[80];

	int i = 0;
	while((dir = readdir(d)) != NULL){
		if(dir->d_name[0] == '.') //ignore . and .. directories
			continue;

		strcpy(pname, dirName);
		strcat(pname, "/");
		strcat(pname, dir->d_name);

		#ifdef TRACE
		printf("Reading room file %s at path %s\n", dir->d_name, pname);
		#endif

		FILE *fp = fopen(pname, "r");

		if(!fp){
			printf("Error opening file %s\n", dir->d_name);
			return;
		}

		if(readRoom(fp, &rooms[i]) != 0){
			fprintf(stderr, "Successfully read %d rooms; was supposed to read %d\n", i, ROOM_COUNT);
			break;
		}

		i++;
	}
}

//finds the most recent rooms folder in the directory
int mostRecentFolder(char *buf) {
	DIR * d;
	struct dirent *dir;
	d = opendir(".");

	if(!d) return 1;

	int returnValue = 1;
	time_t newestTime;

	while((dir = readdir(d)) != NULL){
		if(strncmp(dir->d_name, ROOM_FILE_HEADER, strlen(ROOM_FILE_HEADER) - 1) == 0){
			#ifdef TRACE
			printf("Found candidate folder: %s\n", dir->d_name);
			#endif

			struct stat s;
			stat(dir->d_name, &s);
			returnValue = 0;

			if(s.st_mtime > newestTime){
				strcpy(buf, dir->d_name);
				newestTime = s.st_mtime;
			}
		}
	}

	return returnValue;
}

//convert connections of just names to names and corresponding room ID
//returns true on success
int roomConvertConnections(struct room * maze){
	
	//I'm so sorry
	int i, j, k;

	//loop through all rooms
	for(i = 0; i < ROOM_COUNT; i++){
		struct room r = maze[i];

		//all connections for each room
		for(j = 0; j < r.numConnections; j++){

			//find the room name in the maze that corresponds to the connection name
			
			#ifdef TRACE
			printf("Searching for connection to %s from %s\n", r.connections[j].name, r.name);
			#endif

			int found = 0;
			for(k = 0; k < ROOM_COUNT; k++){
				//replace the name with the room ID
				if(strcmp(maze[k].name, r.connections[j].name) == 0){
					#ifdef TRACE
					printf("Matched connection %s with room %s, ID %d\n", r.connections[j].name, maze[k].name, maze[k].ID);
					#endif
					r.connections[j].ID = maze[k].ID;
					found = 1;
					break;
				}
			}//loop k

			if(k == ROOM_COUNT) printf("Search Loop Completed\n"); //this should only happen on failure to find a room
			if(!found){
				printf("Could not find room %s in maze\n", r.connections[j].name);
				return 0;
			}
		}//loop j
	}//loop i

	return 1;

}

// ***** ROOM PARSING ENDS HERE *****
//
// ***** GAME PLAYING STARTS HERE *****

//finds the starting room
struct room * startRoom(struct room * maze){
	int i;
	for(i = 0; i < ROOM_COUNT; i++){
		if(maze[i].type == TYPE_START_ROOM)
			return &maze[i];
	}

	return NULL;
}

//prints the room and connections to the screen
void showRoom(struct room *r){
	printf("CURRENT LOCATION: %s\n", r->name);
	printf("POSSIBLE CONNECTIONS:");
	
	int i;
	for(i = 0; i < r->numConnections - 1; i++){
		printf(" %s,", r->connections[i].name);
	}
	printf(" %s.", r->connections[i].name);

	puts("\n");
}

//gets input from the user
void prompt(char * buffer){
	printf("WHERE TO? >");
	int temp = ROOM_NAME_SIZE;
	getline(&buffer, (size_t *)&temp, stdin);

	//remove new line at end of input
	int i;
	for(i = 0; i < strlen(buffer); i++){
		if(buffer[i] == '\n') buffer[i] = '\0';
	}

	puts("");

	#ifdef TRACE
	printf("Read %s from user\n", buffer);
	#endif
}

//converts the room name given by the user to the ID
//returns room ID on success, -1 on failure
int newRoomID(struct room *r, char * newRoomName){
	int i;
	for(i = 0; i < r->numConnections; i++){
		#ifdef TRACE
		printf("Attempting to match room name %s with read value %s\n", r->connections[i], newRoomName);
		#endif

		//match the connection name to the user's input
		if(strcmp(r->connections[i].name, newRoomName) == 0){
			#ifdef TRACE
			printf("Found connection %s; ID: %d\n", newRoomName, r->connections[i].ID);
			#endif
			return r->connections[i].ID;
		}
	}

	return -1;
}

//gets a new room from the room ID, adds to the path
struct room * changeRoom(int roomID, struct room * maze, struct path * p){
	struct room * next = &maze[roomID];
	addPathLink(p, next->name);
	return next;
}

//determines if the current room is the final room
int isFinished(struct room * r){
	return r->type == TYPE_END_ROOM;
}

//prints finishing text
void finishGame(struct path * p){
	puts("YOU FOUND THE END ROOM! CONGRATULATIONS!");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", p->size);

	struct pathLink * pl;
	for(pl = p->start->next; pl; pl = pl->next){
		printf("%s\n", pl->name);
	}
}

// ***** GAME PLAYING ENDS HERE *****
//
// ***** TIME KEEPING STARTS HERE *****

#define TIME_FILE "currentTime.txt"
pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;
FILE *f;

//time thread function
void * timeLoop(void * _){
	
	time_t rawTime;
	struct tm * formatTime;
	char timeBuffer[50];

	while(1){
		//make time string
		time(&rawTime);
		formatTime = localtime(&rawTime);
		strftime(timeBuffer, 59, "%I:%M, %A, %B %e, %G", formatTime);

		//write to file and rewind
		pthread_mutex_lock(&timeMutex);
		
		fprintf(f, timeBuffer);
		rewind(f);
		
		pthread_mutex_unlock(&timeMutex);
		sleep(30);
	}
}

void showTime(){
	char timeBuffer[50];

	//read from file and rewind
	pthread_mutex_lock(&timeMutex);
	fgets(timeBuffer, 50, f);
	rewind(f);
	pthread_mutex_unlock(&timeMutex);

	//write to screen
	puts(timeBuffer);
	puts("");
}

// ***** TIME KEEPING ENDS HERE *****
//
// ***** MAIN STARTS HERE *****


int main(int argc, char ** argv){
	//TIME SETUP
	f = fopen(TIME_FILE, "w+");
	if(!f){
		printf("we fukt up");
		fclose(fopen(TIME_FILE, "w"));
		f = fopen(TIME_FILE, "rw");
	}
	pthread_t timeThread;
	pthread_create(&timeThread, NULL, timeLoop, NULL);

	//PARSING GAME
	roomTypes[0] = "START_ROOM";
	roomTypes[1] = "MID_ROOM";
	roomTypes[2] = "END_ROOM";

	char fileNameBuffer[25];
	struct room maze[ROOM_COUNT];

	int i;
	for(i = 0; i < ROOM_COUNT; i++){
		maze[i] = newRoom(i);
	}

	if(mostRecentFolder(fileNameBuffer) != 0){
		printf("Failed to find file of type %s[PID]\n", ROOM_FILE_HEADER);
		exit(1);
	}

	readRoomsDir(fileNameBuffer, maze);

	#ifdef TRACE
	for(i = 0; i < ROOM_COUNT; i++){
		printf("ROOM %d: %s TYPE: %s CONNECTIONS:%d ID: %d\n", maze[i].ID, maze[i].name, roomTypes[maze[i].type], maze[i].numConnections, maze[i].ID);
	}
	#endif

	if(!roomConvertConnections(maze)) return 1;

	//PLAYING GAME
	
	struct path p = newPath();
	struct room * current = startRoom(maze);
	char inputBuffer[ROOM_NAME_SIZE];	

	while(!isFinished(current)){
		memset(inputBuffer, '\0', ROOM_NAME_SIZE);
		showRoom(current);
	PROMPT: prompt(inputBuffer);
		
		if(strcmp(inputBuffer, "time") == 0){
			showTime();
			goto PROMPT;
		}

		int id;
		if((id = newRoomID(current, inputBuffer)) == -1){
			puts("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
			continue;
		}

		current = changeRoom(id, maze, &p);
	}
	finishGame(&p);

	//CLEANUP

	pthread_cancel(timeThread);
	fclose(f);	

	deletePath(&p);
	for(i = 0; i < ROOM_COUNT; i++){
		deleteRoom(&maze[i]);
	}

	return 0;
}

