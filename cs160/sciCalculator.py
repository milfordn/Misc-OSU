
mode = "";

while True :	
	op = "*";
	arg1 = "0";
	arg2 = "0";
	
	#Get mode if we don't have one
	if(mode == "") :
		mode = input("Scientific or Programmer mode? ");

		if(mode == "Programmer" or mode == "programmer"):
			mode = "p";
		elif(mode == "Scientific" or mode == "scientific"):
			mode = "s";
		else:
			print("Invalid Calculator Mode: " + mode);
			mode = "";
			continue;

	#Get operator and operand(s)
	if(mode == "s"):
		op = input("Operation: ");
		arg1 = input("Operand 1: ");
		arg2 = input("Operand 2: ");
	elif (mode == "p"):
		op = input("Binary to Decimal (D) or Decimal to Binary (B): ");
		arg1 = input("Number to Convert: ");
	else :
		print("Invalid Calculator Mode");
		mode = "";
		continue;

	#Verify Operator
	if(op != "*" and op != "**" and op != "/" and op != "-" and op != "+" and op != "D" and op != "B"):
		print("Invalid Operation: " + op);
		continue;

	#Verify operands
	arg1v = 0;
	arg2v = 0;
	try:
		arg1v = float(arg1);
		arg2v = float(arg2);
	except ValueError:
		print("Invalid Operands: " + arg1 + ", " + arg2);
		continue;
	
	if(op == "B"):
		if(arg1v % 1 != 0):
			print("Invalid operand for this operation: " + arg1);
			continue;
		arg1v = int(arg1v);
	if(op == "D"):
		valid = True;
		for c in arg1:
			if(c != '1' and c != '0'):
				valid = False;
				print("Invalid operand for this operation: " + arg1);
				break;
		if(not valid):
			continue;

	#Perform Calculation
	if(op == "+"):
		print(arg1v + arg2v);
	if(op == "-"):
		print(arg1v - arg2v);
	if(op == "*"):
		print(arg1v * arg2v);
	if(op == "/"):
		print(arg1v / arg2v);
	if(op == "**"):
		print(arg1v ** arg2v);
	if(op == "B"):
		result = ""
		while(arg1v > 0):
			result = str(arg1v % 2) + result;
			arg1v //= 2;
		print(result);
	if(op == "D"):
		result = 0
		for c in arg1:
			result *= 2;
			result += int(c);
		print(result);

	#Ask user for next action
	action = input("Send \"S\" to switch calculator modes");
	if(action == "S"):
		mode = "";

