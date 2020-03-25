#include <cstdlib>
#include <cstdio>
#include <cmath>

#define MAX_SIZE 9

int solutions;

void printBoard(int board[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i] == j) putchar('Q');
			else putchar('.');
		}
		putchar('\n');
	}
}

int nextOpenSpace(int start, int col, int board[], int size) {
	if (col == 0) return start;
	
	//check all rows past the starting row
	for (int row = start; row < size; row++) {
		int valid = 1;

		//look at all queen locations for previous columns
		for (int i = 0; i < col; i++) {
			int qLoc = board[i];
			
			//in the same row or diagonal as another queen
			if (qLoc == row || qLoc + (col - i) == row || qLoc - (col - i) == row) {
				valid = 0;
				break;
			}
		}
		
		//If this row was valid, return it
		if (valid) return row;
	}

	//return failure to find a spot
	return -1;
}

void rotate(int board[], int size) {
	int buffer[MAX_SIZE];

	for (int i = 0; i < size; i++) {
		buffer[size - board[i] - 1] = i;
	}
	for (int i = 0; i < size; i++) {
		board[i] = buffer[i];
	}
}

int hash(int board[], int size) {
	int toReturn = 0;
	for (int i = 0; i < size; i++) {
		toReturn += pow(10, size - i - 1) * board[i];
	}
	return toReturn;
}

int isNewSolution(int board[], int size) {
	int buffer[MAX_SIZE];

	for (int i = 0; i < size; i++) buffer[i] = board[i]; //copy board into buffer

	int boardVal = hash(board, size);

	//first three other rotations
	for (int i = 0; i < 4; i++) {
		rotate(buffer, size);
		if (hash(buffer, size) < boardVal) return 0;
	}

	//horizontal mirror
	for (int i = 0; i < size; i++) {
		buffer[i] = size - buffer[i] - 1;
	}
	if (hash(buffer, size) < boardVal) return 0;

	//mirrored rotations
	for (int i = 0; i < 4; i++) {
		rotate(buffer, size);
		if (hash(buffer, size) < boardVal) return 0;
	}

	return 1;
}

void placeNextQueen(int col, int board[], int size) {
	//we made it to the end of the board
	if (col == size) {
		//don't report it if it isn't an isomorphically unique solution
		if (!isNewSolution(board, size)) return;

		puts("\nSolution Found!\n");
		printBoard(board, size);

		solutions++;
		return;
	}

	//try all queen placements for this row
	for (int i = 0; i < size;) {
		//find the next open space
		int next = nextOpenSpace(i, col, board, size);

		//if there is no next open space, move on.
		if (next == -1) break;

		//printf("Placed Queen on column %d at row %d for %dx%d board\n", col, next, size, size);

		//place a queen in the next open space and move to the next column
		board[col] = next;
		placeNextQueen(col + 1, board, size);

		//go to the next row.
		i = next + 1;
	}
}

int main(int argc, char ** argv) {

	int board[MAX_SIZE];
	
	int i = 4;
	for (int i = 1; i <= 9; i++) {
		solutions = 0;
		placeNextQueen(0, board, i);

		printf("Number of Solutions for %dx%d board: %d\n", i, i, solutions);
	}

	getchar();
	return 0;
}
