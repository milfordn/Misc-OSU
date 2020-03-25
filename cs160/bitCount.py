x = int(input("How many bytes? "));
x *= 8 #8 bits per byte 
print(str(-1 * (2 ** (x - 1) - 1)) + " Is the smallest number in a signed system"); 
print(str(2 ** x - 1) + " Is the max number in an unsigned system");
