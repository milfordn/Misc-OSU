
while True:
	weight = float(input("Give weight: "))
	raduis = float(input("Give radius: "))
	
	volume = 4 * 3.14159 * (raduis ** 3) / 3
	force = volume * 62.4
	
	if(force > weight):
		print("This sphere will float")
	else:
		print("This sphere will sink")
	
	if(input("Continue? ") == "y"):
		continue;
	else:
		break;


