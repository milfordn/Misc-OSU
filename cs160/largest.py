import sys

#Open the file
f = open(sys.argv[1]);

#Read the entire file
s_in = f.read();

#Split the values at spaces
vals_str = s_in.split();

#Start a list to put numbers in
vals_num = []

#convert string list to number list and find the largest number
largest = -99999;
for s in vals_str:
	temp = int(s);

	if(temp > largest):
		largest = temp;

	vals_num.append(int(s));

#open an output file
o = open(sys.argv[2], "w");
o.write(str(largest));

#File contents to output
print(vals_num);
