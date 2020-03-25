import LinearRegression
import sys

weights, trainError, testError = LinearRegression.wholeEnchilada(sys.argv[1], sys.argv[2])
LinearRegression.printSolution(weights, trainError, testError)
