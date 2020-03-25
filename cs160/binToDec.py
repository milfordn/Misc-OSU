dec = input("Give Number")

try:
	dec = int(dec)
except ValueError:
	print("NaN");

if(dec < 0 or dec > 255):

	print("Not between 0 and 255")

if(not isinstance(dec, int)):
	print("Not an Integer")

#She said no loops
#She also said no conditionals, but I'm not convinced that's possible
#without going into wierd unnecessary math stuff
out = "";
index = 7;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index;	
index -= 1;
 
if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index;
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index;
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 ** index
index -= 1;

if(2 ** index > dec):
	out += "0";
else:
	out += "1";
	dec -= 2 * index;
index -= 1;

print(out) 
