import turtle;

window = turtle.Screen();
tortoise = turtle.Turtle();
#tortoise.hideTurtle();
tortoise.penup();
tortoise.goto(-125, 125);
tortoise.pendown();

def draw(x, y):
	tortoise.clear();
	for i in range(0, 5):
		tortoise.fd(250);
		tortoise.left(180+180/5);

tortoise.onclick(draw);

turtle.mainloop();
#tortoise.done();
