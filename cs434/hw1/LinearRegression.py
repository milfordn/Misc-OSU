import numpy as np

#returns X input vector associated with Y output
def getFeatureVector(vString):
	strArr = vString.split(' ')
	strippedArr = filter(lambda x: x != "", strArr)
	numArr = list(map(float, strippedArr))
	yVal = numArr[-1]
	del numArr[-1]
	return numArr, yVal

#adds extra 1 to the start of every measurement vector in the matrix
#assumes there are more samples than the dimension of the measurement vector
def withBiasTerm(X):
	numSamples = max(X.shape)
	return np.concatenate((np.matrix(np.ones(numSamples)).T, X), axis=1)

#adds an extra random feature to the end of every measurement vector
#assumes there are more samples than the dimension of the measurement vector
def addRandomFeature(X):
	numSamples = max(X.shape)
	return np.concatenate((X, np.matrix(np.random.normal(size=(numSamples))).T), axis=1)

#gets X matrix, Y vector from a file
def getXYMatrices(f):
	measurements = []
	outputs = []
	for line in f:
		(measurement, output) = getFeatureVector(line)
		measurements.append(measurement)
		outputs.append(output)
	return np.matrix(measurements), np.matrix(outputs).T

#gets weight vector from X, Y matrices
def getWeights(X, Y):
	#W = (X^T * X)^-1 * X^T * Y
	# yo dawg, I heard you like np.matmul
	return np.matmul(np.matmul(np.matmul(X.T, X).I, X.T), Y)

#calculates squared error from X, Y, weight matrices
def getError(X, Y, W):
	#E = (Y - XW)^T * (Y - XW)
	simpleError = Y - np.matmul(X, W)
	return np.matmul(simpleError.T, simpleError)	

#given a training and testing file with some settings, calculates weight vector, average training error, and average testing error
def wholeEnchilada(trainFile, testFile, addBiases=True, numExtraFeatures=0):
	with open(trainFile) as f:
		trainX, trainY = getXYMatrices(f)

	with open(testFile) as f:
		testX, testY = getXYMatrices(f)

	if addBiases:
		#add bias
		trainX = withBiasTerm(trainX)
		testX = withBiasTerm(testX)

	for _ in range(0, numExtraFeatures):
		trainX = addRandomFeature(trainX)
		testX = addRandomFeature(testX)

	#calculate and display weights
	weights = getWeights(trainX, trainY)

	#calculate and display error
	avgTrainError = getError(trainX, trainY, weights) / trainY.size
	avgTestError = getError(testX, testY, weights) / testY.size

	return weights, avgTrainError, avgTestError

#print solutions to problems
def printSolution(W, avgTrain, avgTest, addBiases=True):
	print("\nWeight Vector" + (" (bias is first element)" if addBiases else ""))
	print("\n".join(map(str, W)))

	print("\nAverage Squared Error (first is training, second is testing)")
	print(avgTrain)
	print(avgTest)

