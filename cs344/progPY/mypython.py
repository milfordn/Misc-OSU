import random;

f1 = open("f1.txt", "w+");
f2 = open("f2.txt", "w+");
f3 = open("f3.txt", "w+");

for i in range(0, 10):
	char = chr(random.randrange(0, 26) + ord('a'));
	f1.write(str(char));

f1.write('\n');

for i in range(0, 10):
	char = chr(random.randrange(0, 26) + ord('a'));
	f2.write(str(char));

f2.write('\n');

for i in range(0, 10):
	char = chr(random.randrange(0, 26) + ord('a'));
	f3.write(str(char));

f3.write('\n');

f1.seek(0);
f2.seek(0);
f3.seek(0);

rand1 = random.randrange(1, 43);
rand2 = random.randrange(1, 43);

print(f1.read()),
print(f2.read()),
print(f3.read()),
print(rand1);
print(rand2);
print(rand1 * rand2);
