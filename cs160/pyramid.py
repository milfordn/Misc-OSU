def makeTri(wid):
	cont = True
	stars = 1
	while cont:
		line = "";
		for x in range(wid):
			if(x < (wid-stars)//2 or x >= wid-((wid-stars)//2)):
				line += " "
			else:
				line +=  "*"

		print(line);
		if(stars == wid):
			cont = False;
		stars += 2

while(True):
	try:
		width = int(input("How many stars?: "))
		if(width % 2 == 0):
			raise ValueError("even number")
		break;
	except(ValueError):
		print("That's not a valid number")

makeTri(width)
