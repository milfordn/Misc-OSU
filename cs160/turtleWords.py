import turtle;

#========== DRAWING FUNCTIONS ==========#
def e(trtl):
	#trtl.setheading(0);
	trtl.pendown();

	trtl.fd(20);
	trtl.bk(20);

	trtl.rt(90);
	trtl.fd(20);

	trtl.lt(90);
	trtl.fd(15);
	trtl.bk(15);

	trtl.rt(90);
	trtl.fd(20);
	
	trtl.lt(90);
	trtl.fd(20);

	trtl.penup();
	trtl.goto(trtl.xcor() - 20, trtl.ycor() + 40);

def t(trtl):
	trtl.setheading(0);
	trtl.pendown();
	trtl.fd(10);

	trtl.rt(90);
	trtl.fd(40);
	trtl.bk(40);

	trtl.lt(90);
	trtl.fd(10);

	trtl.penup();
	trtl.goto(trtl.xcor() - 20, trtl.ycor());

def a(trtl):
	trtl.penup();
	trtl.goto(trtl.xcor(), trtl.ycor() - 40);
	trtl.pendown();

	trtl.goto(trtl.xcor() + 10, trtl.ycor() + 40);
	trtl.goto(trtl.xcor() + 10, trtl.ycor() - 40);
	
	trtl.goto(trtl.xcor() - 5, trtl.ycor() + 20);
	trtl.goto(trtl.xcor() - 10, trtl.ycor());

	trtl.penup();
	trtl.goto(trtl.xcor() - 5, trtl.ycor() + 20);

def o(trtl):
	trtl.up();
	trtl.setx(trtl.xcor() + 5);
	trtl.down();

	trtl.goto(trtl.xcor() - 5, trtl.ycor() - 5);
	trtl.sety(trtl.ycor() - 30);
	trtl.goto(trtl.xcor() + 5, trtl.ycor() - 5);
	trtl.setx(trtl.xcor() + 10);
	trtl.goto(trtl.xcor() + 5, trtl.ycor() + 5);
	trtl.sety(trtl.ycor() + 30);
	trtl.goto(trtl.xcor() - 5, trtl.ycor() + 5);
	trtl.setx(trtl.xcor() - 10);

	trtl.up()
	trtl.goto(trtl.xcor() - 5, trtl.ycor());

def n(trtl):
	trtl.down();
	trtl.sety(trtl.ycor() - 40);
	trtl.sety(trtl.ycor() + 40);
	trtl.goto(trtl.xcor() + 20, trtl.ycor() - 40);
	trtl.sety(trtl.ycor() + 40);
	
	trtl.up();
	trtl.goto(trtl.xcor() - 20, trtl.ycor());

def s(trtl):
	trtl.up();
	trtl.setx(trtl.xcor() + 20);
	trtl.down();
	
	trtl.setx(trtl.xcor() - 15);
	trtl.goto(trtl.xcor() - 5, trtl.ycor() - 10);
	trtl.goto(trtl.xcor() + 5, trtl.ycor() - 10);
	trtl.setx(trtl.xcor() + 10);
	trtl.goto(trtl.xcor() + 5, trtl.ycor() - 10);
	trtl.goto(trtl.xcor() - 5, trtl.ycor() - 10);
	trtl.setx(trtl.xcor() - 15);

	trtl.up();
	trtl.goto(trtl.xcor(), trtl.ycor() + 40);
#========== DRAWING FUNCTIONS ==========#


# MAIN
def turtClick(tortoise):

#	tortoise = turtle.Turtle();
#	window = turtle.Screen();
#	usr_in = ""	 

#	while(True):
	
		tortoise.clear(); 

	#Get user string
		usr_in = ""
		while(usr_in == ""):
			given = input("String to draw to screen ")
			for c in given:
				# to uppercase
				if(c >= 'a'):
					c = chr(ord(c) - (ord('a') - ord('A')))

				# check that c is a valid character
				if(c != 'A' and c != 'E' and c != 'T' and c != 'O' and c != 'S' and c != 'N'):
					print("Invalid Character: " + str(c))
					break;
			
			else:
				usr_in = given

		# Draw each character
#		wait = True;
#		def next(x, y):
		for c in usr_in:
			if(c == 'A' or c == 'a'):
				a(tortoise);
			elif(c == 'E' or c == 'e'):
				e(tortoise);
			elif(c == 'T' or c == 't'):
				t(tortoise);
			elif(c == 'O' or c == 'o'):
				o(tortoise);
			elif(c == 'N' or c == 'n'):
				n(tortoise);
			elif(c == 'S' or c == 's'):
				s(tortoise);
			tortoise.setx(tortoise.xcor() + 30);
#		wait = false;
		
#		turtle.mainloop();
#		tortoise.onclick(next)
#		while(wait):
#			pass;
			#tortoise.onclick(next);
			#tortoise.onclick(lambda x,y:wait = False);

#		tortoise.onclick();
		tortoise.goto(0, 0);

		if(input("Send q to quit, anything else to continue ") == 'q'):
			turtle.Screen().bye();
		else:
			print("Click the turtle to draw some letters" )

def main():
	tortoise = turtle.Turtle();
	window = turtle.Screen();
	tortoise.onclick(lambda x,y:turtClick(tortoise));
	print("Click the turtle to draw some letters");
	turtle.mainloop()

main();
