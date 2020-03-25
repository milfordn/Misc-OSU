####################################################
# Function Name: get_user_input
# Description: gets a string from the user
# Parameters: None
# Pre-conditions: None
# Post-conditions: None
# Return Values: String
####################################################
def get_user_input():
	return input("Send me a string ");

####################################################
# Function Name: num_matching_chars
# Description: finds how many chars match in two strings
# Parameters: String 1, String 2
# Pre-Conditions: None
# Post-conditions: None
# Return Values: int
####################################################
def num_matching(str1, str2):
	matching = 0;
	for x in range(min(len(str1), len(str2))):
		if str1[x] == str2[x]:
			matching += 1;
	return matching

####################################################
# Function Name: percent_matching
# Description: funds the percentage of matching chars in two strings
# Parameters: string 1, string 2
# Pre-conditions: None
# Post-conditions: None
# Return Values: double
####################################################
def percent_matching(str1, str2):
	matching = num_matching(str1, str2);
	return matching * 100 / max(len(str1), len(str2));

####################################################
# Function Name: main
# Description: Begin execution for program here
# Parameters: None
# Pre-Conditions: None
# Post-Conditions: None
# Return Values: None
####################################################
def main():
	while True:
		str1 = get_user_input();
		str2 = get_user_input();
		print(str(percent_matching(str1, str2)) + "%");
		
		if(input("Send q to quit ") == 'q'):
			break;

main();
