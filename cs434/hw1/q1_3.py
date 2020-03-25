import LinearRegression
import sys

weights, train, test = LinearRegression.wholeEnchilada(sys.argv[1], sys.argv[2], addBiases=False)
LinearRegression.printSolution(weights, train, test, addBiases=False)
