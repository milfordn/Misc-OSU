##########################################################
# Function: is_pangram
# Description: determines if the given string is a pangram
# Parameters: string
# Return values: boolean
# Pre-conditions: none
# Post-conditions: none
##########################################################
def is_pangram(s_in):
	for c in range(ord('a'), ord('z')+1):
		if not (str(chr(c)) in s_in):
			return False;
	return True;

##########################################################
# Function: main
# Description: program entry point
# Parameters: none
# Return Values: none
# Pre-conditions: none
# Post-conditions: none
#########################################################
def main():
	s_in = input("Enter string: ");
	if is_pangram(s_in):
		print("It is a pangram!!!!!!!!!!!!!!")
	else:
		print("Boo, hoo! It is not a pangram!")

main()
