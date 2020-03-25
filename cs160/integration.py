def f1(x):
	return 5*x**4+3*x**3-10*x+2;
def f2(x):
	return x**2-10;
def f3(x):
	return 40*x+5;
def f4(x):
	return x**3;
def f5(x):
	return 20*x**2+10*x-2;

# Main loop
while(True):

	# get function from user (or quit, that's cool too)
	fnSelect = input("Choose a function (1, 2, 3, 4, 5, other/quit): ")
	selectedFn = ""	

	if(fnSelect == "" or fnSelect[0] < '1' or fnSelect[0] > '5'):
		break;
	elif fnSelect == "1":
		selectedFn = "5x^4 + 3x^3 - 10x + 2"
	elif fnSelect == "2":
		selectedFn = "x^2 - 10"
	elif fnSelect == "3":
		selectedFn = "40x + 5"
	elif fnSelect == "4":
		selectedFn = "x^3"
	elif fnSelect == "5":
		selectedFn = "20x^2 + 10x - 2"

	# get trapezoid or rectabgle mode
	mTrapz = False;
	mRect = False;

	while(not (mTrapz or mRect)):
		mode = input("Would you like to calculate the area using rectangles, trapezoids, or both (1, 2, 3): ");
		if(mode == "1" or mode == "3"):
			mRect = True;
		if(mode == "2" or mode == "3"):
			mTrapz = True;

	# get number of trapezoids and rectangles
	numTrapz, numRects = 0, 0
	while(mTrapz and numTrapz == 0):
		try:
			numTrapz = int(input("How many trapezoids do you want? "))
		except(ValueError):
			print("Not a Number")
	while(mRect and numRects == 0):
		try:
			numRects = int(input("How many rectangles do you want? "))
		except(ValueError):
			print("Not a Number")

	# get start and end points
	while(True):
		try:
			start = float(input("Please select a starting point: "))
			break;
		except(ValueError):
			print("Not a Number");
	
	while(True):
		try:
			end = float(input("Please select an ending point: "))
			break;
		except(ValueError):
			print("Not a Number");

	#start integration
	#Rectangles
	if(mTrapz):
		trapWidth = (end - start) / numTrapz
		accum = 0;
		x = start;
		while(x < end):
			xn = x + rectWidth;
			if(fnSelect == "1"):
				accum += (f1(x) + f1(xn)) * trapWidth / 2;
			elif(fnSelect == "2"):
				accum += (f2(x) + f2(xn)) * trapWidth / 2;
			elif(fnSelect == "3"):
				accum += (f3(x) + f3(xn)) * trapWidth / 2;
			elif(fnSelect == "4"):
				accum += (f4(x) + f5(xn)) * trapWidth / 2;
			elif(fnSelect == "5"):
				accum += (f5(x) + f5(xn)) * trapWIdth / 2;
			x += trapWidth;
		
		print("The area under "+selectedFn+" between "+str(start)+" and "+str(end)+" is "+str(accum))

	#Trapezoids
	if(mRect):
		rectWidth = (end - start) / numRects
		accum = 0;
		x = start;
		while(x<end):
			if(fnSelect == "1"):
				accum += (f1(x)) * rectWidth;
			elif(fnSelect == "2"):
				accum += (f2(x)) * rectWidth;
			elif(fnSelect == "3"):
				accum += (f3(x)) * rectWidth;
			elif(fnSelect == "4"):
				accum += (f4(x)) * rectWidth;
			elif(fnSelect == "5"):
				accum += (f5(x)) * rectWIdth;
			x += rectWidth;	

		print("The area under "+selectedFn+" between "+str(start)+" and "+str(end)+" is "+str(accum)); 
