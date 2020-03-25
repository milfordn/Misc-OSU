#################################################
# Function Name: getValidInput
# Description: gets the position for a given piece from the user
# Parameters: Piece to ask for the position of
# Pre-Conditions: None
# Post-Contidions: None
# return Values: xy coordinate entered by the user
###################################################
def getValidInput(piece):
	while True:
		x = input("Where would you like to put your " + piece)

		if len(x) != 3:
			print("Just two numbers with a space between them");
			continue;		#Abort if our input is not what we were expecting

		for c in x:
			if c != ' ' and (c > '9' or c < '0'):
				print("Those aren't numbers!")
				break;		#Abort if we find an invalid character
		else:				#If all characters were valid
			return int(str(x[0])), int(str(x[2])) 	#Return a point value

##################################################
# Function Name: newBoard
# Description: returns an empty board
# Parameters: None
# Pre-Conditions: None
# Post-Conditions: None
# Return Values: 2d array, all values set to ' '
##################################################
def newBoard():
	return [[' ', ' ', ' '],
		[' ', ' ', ' '],
		[' ', ' ', ' ']]

##################################################
# Funciton Name: isValidLocation
# Description: Determines if the location given is on the board and empty
# Parameters: 2d array, int, int
# Pre-Conditions: board is a 3x3 array
# Post-Conditions: None
# Return Values: boolean, true if the location is on the board and empty
#################################################
def isValidLocation(board, x, y):
	if(x > 2 or x < 0 or y > 2 or y < 0):
		return False
	return board[y][x] == ' ';

###################################################
# Funciton Name: checkWin
# Description: Determines the state of the game after every turn
# Parameters: 2d array
# Pre-Conditions: board is a 3x3 array
# Post-conditions: none
# Return Values: winning char value if a player has won, null (0x00) if the game is still goind, backspace (0x08) if the game is tied
###################################################
def checkWin(board):
	# Tie flag. If an empty space is found, set this to false.
	tie = True

	#check rows for 3 of a kind, also determine tie at this point
	for row in board:
		if(row[0] == ' ' or row[1] == ' ' or row[2] == ' '):
			tie = False
		if(row[0] == row[1] and row[1] == row[2]) and row[1] != ' ':
			return row[1];
	
	#check columns for 3 of a kind.
	for col in range(0, 3):
		if(board[0][col] == board[1][col] and board[1][col] == board[2][col]) and board[1][col] != ' ':
			return board[1][col]

	#check diagonals
	if((board[0][0] == board[1][1] and board[1][1] == board[2][2]) or (board[0][2] == board[1][1] and board[2][0] == board[1][1])) and board[1][1] != ' ':
		return board[1][1];

	#If there was a tie, return a special character
	if(tie):
		return chr(0x08); #Backspace for tie
	return chr(0x00) #Null character for not finished

######################################
# Function Name: showBoard
# Description: prints the board to the screen
# Parameters: 2d array
# pre-confitions: board is a 3x3 char array
# post-conditions: none
# Return values: none
######################################
def showBoard(board):
	for i in range(0, 5):
		if(i % 2 != 0):
			print("-----------")
		else:
			print(" " + board[i//2][0] + " | " + board[i//2][1] + " | " + board[i//2][2]);

##########################################
# Function Name: addPiece
# Description: adds a piece to the board if the xy location is valid
# Parameters: 2d array, char, int x, int y
# Pre-conditions: board is a 3x3 array
# Post-conditions: board's value at x,y is changed to char if this returns true
# Return Values: true if the piece was successfully added to the board
#########################################
def addPiece(board, piece, x, y):
	if(not isValidLocation(board, x, y)):
		return False;
	
	board[y][x] = piece;
	return True;

########################################
# Function Name: takeTurn
# Description: gets input from user and puts that piece on the board
# Parameters: 2d array, char
# Pre-COnditions: board is a 3x3 char array
# Post-Conditions: board's value at the user input is changed to piece
# Return Values: None
#########################################
def takeTurn(board, piece):
	x, y = 0, 0;
	while(True):
		x, y = getValidInput(piece);
		if(not isValidLocation(board, x, y)):
			print("You can't put a piece there")
			continue;
		break;

	addPiece(board, piece, x, y);
	showBoard(board);

#############################################
# Fuction Name; getPlaterPiece
# Description: gets the piece for a player at the start of the game
# Parameters: int
# Pre-COnditions: none
# Post-Contitions: none
# Return Values: char selected by player
#############################################
def getPlayerPiece(playerNumber):
	while(True):
		c = input("Player " + str(playerNumber) + ": Select a character ");
		if(len(c) != 1):
			print("Try again. remember, just a character");
			continue;
		return c[0];

############################################
# Function Name; playGame
# Description: plays the game, and only plays the game
# Parameters: char, char
# Pre-Conditions: none
# Post-COnditions: none
# Return Values: char result form checkWin
##############################################
def playGame(p1, p2):
	board = newBoard();

	turnFlipper = True;
	winner = chr(0x00);
	while(winner == chr(0x00)):
		if(turnFlipper):
			takeTurn(board, p1)
		else:
			takeTurn(board, p2)
	
		turnFlipper = not turnFlipper
		winner = checkWin(board)

	return winner;

##############################################
# Fucntion Name; postGame
# Description: shows win message, asks the player to play again
# Parameters: win condition from checkWin
# pre-conditions: winner is one of the possible results of checkWin
# Post-Conditions: none
# Return values: true if the user wants to continue
###############################################
def postGame(winner):
	if(winner == chr(0x08)):
		print("Tie!")
	else:
		print("Player " + winner + " Wins!!!!!!") #Extra exclamation points to make jennifer happy

	while(True):
		choice = input("Do you want to play again? (y/n): ");
		if(choice != 'y' and choice != 'n'):
			print("Please enter just a \'y\' or \'n\'");
			continue;
		return choice == "y"

################################################
# Function Name: programExit
# Description: shows score, exits program
# Parameters: int, int, int
# Pre-COnditions: none
# Post-conditions: none
# Return Values: none
###############################################
def programExit(p1Score, p2Score, ties):
	print("Total Wins:")
	print("Player 1: " + str(p1Score));
	print("Player 2: " + str(p2Score));
	print("Ties: " + str(ties));

##################################################
# Function Name: main
# Description: begin execution for program here
# Parameters: none
# Pre-Conditions: none
# Post-conditions: none
# Return Values; none
###################################################
def main():
	p1 = getPlayerPiece(1);
	p2 = getPlayerPiece(2);

	p1Score, p2Score, ties = 0, 0, 0;

	while(True):
		winner = playGame(p1, p2);
		
		if(winner == p1):
			p1Score += 1
		elif(winner == p2):
			p2Score += 1
		else:
			ties += 1

		if(not postGame(winner)):
			break;

	programExit(p1Score, p2Score, ties)

main()
