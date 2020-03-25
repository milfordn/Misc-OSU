def make_multiplication_table(size):
	toReturn = []
	for i in range(0, size + 1):
		temp = []
		for j in range(0, size + 1):
			temp.append(i * j)
		toReturn.append(temp)
	return toReturn;

def print_multiplication_table(table):
	for row in table:
		toPrint = ""
		for val in row:
			strval = str(val)
			toPrint += strval + (" " * (4 - len(strval)))
		print(toPrint);

def main():
	size = 0
	while(True):
		usr = input("What size would you like your multiplication table to be? ")
		for c in usr:
			if c < '0' or c > '9':
				print("That's not a number")
				break;
		else:
			size = int(usr);
			break;

	table = make_multiplication_table(size);
	print_multiplication_table(table)

main()
