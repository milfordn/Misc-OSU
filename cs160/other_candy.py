#Receive Number
number = input("How many coupons? ");
number = int(number);

savedNumber = number // 10;

savedNum2 = number % 10 // 3;

print("Gumballs: " + str(savedNum2) + "\nCandy Bars: " + str(savedNumber));
