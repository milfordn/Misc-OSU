import math
import numpy as np

def getXY(fname):
	X = []
	Y = []
	with(open(fname)) as f:
		for line in f:
			stringVals = line.split(',')
			intVals = map(int, stringVals)
			# extract answer
			Y.append(intVals[-1])
			# add bias
			intVals[-1] = 1
			X.append(np.array(intVals))
	return X, Y

def sigmoid(weights, X):
	return 1 / (1 + math.exp(-np.dot(weights, X)))

# computes proportion of correct predictions given weight, X matrix, and Y vector
def getAccuracy(x, y, w):
	correct = 0
	for xi, yi in zip(x, y):
		prediction = sigmoid(w, xi) > 0.5
		actual = yi > 0.5
		if prediction == yi: #correct prediction
			correct += 1
	return float(correct) / len(y)

# returns new weight and wether the gradient norm is less than some threshold
batchSize = 50
completionGradient = 0.1
def gradDescent(x, y, w, learning):
	grad = np.zeros(len(w))
	for _ in range(batchSize):
		idx = np.random.randint(len(y))
		prediction = sigmoid(w, x[idx])
		grad += (prediction - y[idx]) * x[idx]
	return (w - learning * grad, np.linalg.norm(grad) < completionGradient)

# gradient descent plus regularization
def regularizedGradDescent(x, y, w, learning, regularizing):
	grad = np.zeros(len(w))
	for _ in range(batchSize):
		idx = np.random.randint(len(y))
		prediction = sigmoid(w, x[idx])
		grad += (prediction - y[idx]) * x[idx]
	# ad regularization
	grad += regularizing * w
	return (w - learning * grad, np.linalg.norm(grad) < completionGradient)

# return a random vector of weights
def randomWeights(x):
	return (np.array(np.random.random_sample(len(x[0]))) - 0.5) / 100

