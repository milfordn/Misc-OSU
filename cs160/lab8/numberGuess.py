import random;

def check_guesses(guesses, nextGuess):
	for guess in guesses:
		if nextGuess == guess:
			return False;
	return True;

def get_guesses(answer):
	guesses = []
	i = 0
	while i < 5:
		guess = input("Which number would you like to guess? ")
		for c in guess:
			if c < '0' or c > '9':
				print("That's not a number")
				break;

			guess = int(guess);

			if(guess < 1 or guess > 20):
				print("That number is out of range")
				break;
			elif(not check_guesses(guesses, guess)):
				print("You have already guessed that")
				break;
		else:
			if(answer == guess):
				print("You guessed correctly!")
				return;
			else:
				print("Incorrect!")
				guesses.append(guess)
				i += 1

	print("The answer was " + str(answer))

def main():
	random.seed();
	get_guesses(random.randint(1, 20))
	#get_guesses(5);
main()
