import turtle
window = turtle.Screen()
tortoise = turtle.Turtle()

while(True):
	while(True):
		try:
			numSides = int(input("How many sides? "))
			break;
		except(ValueError):
			print("NAN")
	
	angle = 360 / numSides
	
	for i in range(0, numSides):
		tortoise.forward(400 / numSides)
		tortoise.rt(angle)
	
	if(input("Quit? ") == "q"):
		break;
	
	tortoise.clear()
