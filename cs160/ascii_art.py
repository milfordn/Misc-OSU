#draws an E
#	#####
#	#
#	###
#	#
#	#####
def e(i):
	if(i == 0 or i == 4):
		return "#####"
	if(i == 1 or i == 3):
		return "#    "
	if(i == 2):
		return "###  "
	
#draws a T
#	#####
#	  #
#	  #
# 	  #
#	  #
def t(i):
	if(i == 0):
		return "#####"
	return "  #  "

#draws an A (I know, it's an ugly A, but it works)
#	  #
#	 # #
#	 ###
#	#   #
#	#   #
def a(i):
	if(i == 0):
		return "  #  "
	if(i == 1):
		return " # # "
	if(i == 2):
		return " ### "
	return "#   #"

#draws an O
#	 ###
#	#   #
#	#   #
#	#   #
#	 ###
def o(i):
	if(i == 0 or i == 4):
		return " ### "
	return "#   #"

#draws an N
#	#   #
#	##  #
#	# # #
#	#  ##
#	#   #
def n(i):
	if(i == 0 or i == 4):
		return "#   #"
	if(i == 1):
		return "##  #"
	if(i == 2):
		return "# # #"
	if(i == 3):
		return "#  ##"

#draws an S
#	 ####
# 	#
#	 ###
#	    #
#	####
def s(i):
	if(i == 0):
		return " ####"
	if(i == 1):
		return "#    "
	if(i == 2):
		return " ### "
	if(i == 3):
		return "    #"
	if(i == 4):
		return "#### " 

def main():
	while(True):

	#Get user string
		usr_in = ""
		while(usr_in == ""):
			given = input("String to make into ASCII ART!!!!!! *explosion sound effect*: ")
			for c in given:
				#rule out all non-letters and letters out of range
				if(c < 'A' or c > 't' or (c > 'T' and c < 'a')):
					print("Invalid Character: " + str(c))
					break;
				
				#Make c uppercase if it is lowercase
				if(c >= 'a'):
					c = chr(ord(c) - (ord('a') - ord('A')))
			
				#check that c is a valid character
				if(c != 'A' and c != 'E' and c != 'T' and c != 'O' and c != 'S' and c != 'N'):
					print("Invalid Character: " + str(c))
					break;
			else: #If we didn't break from the loop, assign s to our given input
				usr_in = given
	
		#Draw each line
		for x in range(0, 5):
			toPrint = ""
			#Draw the character of each line
			for c in usr_in:
				#print(c);
				if(c == 'e' or c == 'E'):
					toPrint += e(x)
				elif(c == 'a' or c == 'A'):
					toPrint += a(x)
				elif(c == 't' or c == 'T'):
					toPrint += t(x)
				elif(c == 's' or c == 'S'):
					toPrint += s(x)
				elif(c == 'o' or c == 'O'):
					toPrint += o(x)
				elif(c == 'n' or c == 'N'):
					toPrint += n(x)
				else:
					toPrint += "Mistakes were made"
				
				toPrint += "  " #Spaces between letters
	
			print(toPrint);
	
		#Ask user for continue
		if(input("q to quit, anything else to not quit: ") == 'q'):
			break;

main()
		
