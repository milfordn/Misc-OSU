#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define ROOM_COUNT 10
#define OUT_ROOM_COUNT 7

#define UNASSIGNED_ROOM -1
#define START_ROOM 0
#define MID_ROOM 1
#define END_ROOM 2

char * roomTypes[3];
char * roomNames[ROOM_COUNT];
int out_rooms [OUT_ROOM_COUNT];

//main room structure
struct room
{
	int roomID; // serves as index location in maze
	int numConnections;
	int * connections;
	int roomType;
};

struct room maze [OUT_ROOM_COUNT];

//determine which rooms will be used in this maze
//fills the out_rooms array with indices from roomNames
void setUsedRooms(){
	int iter = -1;
	int i;
	for(i = 0; i < OUT_ROOM_COUNT; i++){
		int r = rand() % 10;

		if(r > 7 && iter < ROOM_COUNT - i){
			iter += 2; //skip one
		}
		else{
			iter += 1; //don't skip this one
		}

		out_rooms[i] = iter;
	}
}

//creates a new, empty room
struct room newRoom(int roomID){
	struct room c;
	c.roomID = roomID;
	c.numConnections = 0;

	//max 6 connections
	c.connections = malloc(sizeof(int) * 6);
	
	c.roomType = UNASSIGNED_ROOM;
	
	return c;
}

void deleteRoom(struct room * r){
	free(r->connections);
}

//fill the maze with new, empty rooms
void initGraph() {
	int i;
	for(i = 0; i < OUT_ROOM_COUNT; i++){
		maze[i] = newRoom(out_rooms[i]);
	}
}

//determines if room A already connects to room B
int hasConnection(struct room * roomA, struct room * roomB){
	int i;
	for(i = 0; i < roomA->numConnections; i++){
		if (roomA->connections[i] == roomB->roomID)
			return 1;
	}
	
	return 0;
}

//adds a two way connection between rooms
//returns 1 if successful, 0 if not
int addConnection(struct room * roomA, struct room * roomB){
	if(roomA->numConnections == 6 || //room A connections are full
		roomB->numConnections == 6 || //room B connections are full
		roomA->roomID == roomB->roomID || //they are the same room
		hasConnection(roomA, roomB) || //they are already connected
		(roomA->roomType == START_ROOM && roomB->roomType == END_ROOM) || //For fun: don't have the start room connect to the end room
		(roomB->roomType == START_ROOM && roomA->roomType == END_ROOM)
		)
		return 0;

	roomA->connections[roomA->numConnections++] = roomB->roomID;
	roomB->connections[roomB->numConnections++] = roomA->roomID;

	return 1;
}

//gives all room types (start, mid, end)
void assignRooms(struct room rooms[]){
	int startRoom = rand() % OUT_ROOM_COUNT;
	int endRoom = rand() % (OUT_ROOM_COUNT - 1);

	if(startRoom == endRoom) endRoom++;

	int i;
	for(i = 0; i < OUT_ROOM_COUNT; i++){
		int type = MID_ROOM;
		if(i == startRoom) type = START_ROOM;
		if(i == endRoom) type = END_ROOM;

		rooms[i].roomType = type;
	}
}

//tests for completeness of the maze (3 connections per room)
int graphComplete(struct room rooms[]){
	int i;
	for(i = 0; i < OUT_ROOM_COUNT; i++){
		if(rooms[i].numConnections < 3){
			return 0;
		}
	}

	return 1;
}

//adds connections until the graph is complete as per graphComplete() above
void fillGraph(struct room rooms[]){
	while(!graphComplete(rooms)){
		int roomA = rand() % OUT_ROOM_COUNT;	
		int roomB = rand() % (OUT_ROOM_COUNT - 1);
		if (roomB >= roomA) roomB++;

		addConnection(rooms + roomA, rooms + roomB);
	}
}

//writes rooms to files
void writeRooms(struct room rooms[]){
	int i, j;
	
	char dirName[40];
	char fname[40];
	char pname[80];

	sprintf(dirName, "./milfordn.rooms.%d", getpid());

	mkdir(dirName, 0700);

	for(i = 0; i < OUT_ROOM_COUNT; i++){
		assert(i >= 0 && i < ROOM_COUNT);
		struct room r = rooms[i];

		sprintf(fname, "%s.room", roomNames[r.roomID]);
		strcpy(pname, dirName);
		strcat(pname, "/");
		strcat(pname, fname);

		FILE *fp = fopen(pname, "w+");
	
		fprintf(fp, "ROOM NAME: %s\n", roomNames[r.roomID]);
		
		for(j = 0; j < r.numConnections; j++){
			int connectionID = r.connections[j];
			fprintf(fp, "CONNECTION %i: %s\n", j+1, roomNames[connectionID]);
		}

		fprintf(fp, "ROOM TYPE: %s\n\n", roomTypes[r.roomType]);
	}
}


int main(int argc, char **argv){
	srand(time(NULL));

	roomTypes[0] = "START_ROOM";
	roomTypes[1] = "MID_ROOM";
	roomTypes[2] = "END_ROOM";

	roomNames[0] = "Bushes";
	roomNames[1] = "Field";
	roomNames[2] = "Cave";
	roomNames[3] = "Forest";
	roomNames[4] = "Desert";
	roomNames[5] = "Beach";
	roomNames[6] = "City";
	roomNames[7] = "Snow";
	roomNames[8] = "Wasteland";
	roomNames[9] = "River";

	setUsedRooms();
	initGraph();
	assignRooms(maze);
	fillGraph(maze);
	writeRooms(maze);

	int i;
	for(i = 0; i < OUT_ROOM_COUNT; i++){
		deleteRoom(&(maze[i]));
	}
	
	//printf("%s\n", roomNames[9]);

	return 0;
}


