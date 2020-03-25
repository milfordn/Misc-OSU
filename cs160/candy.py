coupons = input("Enter number of tokens ")
coupons = int(coupons)

candyBars = coupons // 10
coupons %= 10

gumballs = coupons // 3

print("Candy Bars: " + str(candyBars) + "\nGumballs: " + str(gumballs))
