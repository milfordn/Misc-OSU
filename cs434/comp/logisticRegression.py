import math
import numpy as np
import sys
import pca
import common

def getRandomTrainingSample(X, Y):
	sX = []
	sY = []
	sizeSample = 1000

	while len(sY) < sizeSample / 3:
		idx = np.random.randint(len(X))
		if Y[idx] == 1:
			sX.append(X[idx])
			sY.append(Y[idx])

	while len(sY) < sizeSample:
		idx = np.random.randint(len(X))
		if Y[idx] == 0:
			sX.append(X[idx])
			sY.append(Y[idx])

	return sX, sY

def sigmoid(weights, X):
	try:
		return 1 / (1 + math.exp(-np.dot(weights, X)))
	except OverflowError: #only occurs on output of exp
		return 0

def getEnsembleAccuracy(x, y, ws):
	correct = 0
	for xi, yi in zip(x, y):
		pos = 0
		for w in ws:
			if sigmoid(w, xi) > 0.5:
				pos += 1
		prediction = pos > len(ws) / 2
		if prediction == yi:
			correct += 1
	return float(correct) / len(y)

# returns new weight and whether the gradient norm is less than some threshold
batchSize = 10000
completionGradient = 0.1
def gradDescent(x, y, w, learning):
	grad = np.zeros(len(w))
	if batchSize < len(x):
		for _ in range(batchSize):
			idx = np.random.randint(len(y))
			prediction = sigmoid(w, x[idx])
			grad += (prediction - y[idx]) * x[idx]
	else:
		for i in range(0, 10000):
			for i in range(len(x)):
				prediction = sigmoid(w, x[i])
				grad += (prediction - y[i]) * x[i]
			sys.stdout.write(str(np.linalg.norm(grad)) + '\r')
			sys.stdout.flush()
			if np.linalg.norm(grad) < completionGradient:
				break
			#grad *= np.linalg.norm(grad)
			grad *= learning
			w -= grad
		return w, True
	#grad /= batchSize
	gLen = np.linalg.norm(grad)
	if gLen == 0:
		return (w, True)
	#grad /= gLen
	grad *= learning
	sys.stdout.write(str(gLen) + '\r')
	sys.stdout.flush()
	return (w - grad, gLen < completionGradient)

# gradient descent plus regularization
def regularizedGradDescent(x, y, w, learning, regularizing):
	grad = np.zeros(len(w))
	for _ in range(batchSize):
		idx = np.random.randint(len(y))
		prediction = sigmoid(w, x[idx])
		grad += (prediction - y[idx]) * x[idx]
	# add regularization
	grad += regularizing * w
	return (w - learning * grad, np.linalg.norm(grad) < completionGradient)

# return a random vector of weights
def randomWeights(x):
	return (np.array(np.random.random_sample(len(x[0]))) - 0.5) * 0.1

def getModelFunction(w):
	return (lambda x: sigmoid(w, x))

def saveEnsemble(ws, weights, acc, fname):
	with open(fname, 'w') as f:
		f.write(str(acc) + "\n")
		for j in range(len(ws)):
			f.write(str(weights[j]))
			for i in range(len(ws[j])):
				f.write("," + str(ws[j][i]))
			f.write("\n")

def loadEnsemble(fname):
	with open(fname) as f:
		header = False
		weights = []
		ws = []
		for line in f:
			if not header:
				header = True
				continue
			strvals = line.split(",")
			weights.append(float(strvals[0]))
			ws.append(np.array(map(float, strvals[1:])))

numRestarts = 11

if __name__ == "__main__":
	
	#X, Y = common.getXY(sys.argv[1])
	#factors = common.getNormalizationFactors(X)
	#l, testX = common.getLabeledX(sys.argv[2])
	
	#if len(sys.argv) > 3 and sys.argv[3] == "pca":
	#	common.normalize(X)
	#	X = pca.getReducedData(X)	

	#common.normalizeBy(X, factors)
	#common.normalizeBy(testX, factors)
	#common.addBias(X)
	#common.addBias(testX)

	tL, X, Y, vL, vX, vY, labels, testX = common.getAllData(sys.argv[1], sys.argv[2])
	
	#tX, tY = common.getEvenSamplingSets(X, Y)

	ws = []
	weights = []

	w = None
	bestAccuracy = 0
	for i in range(numRestarts):
		tempW = randomWeights(X)
		done = False
		tX, tY = getRandomTrainingSample(X, Y)
		while not done:
			(tempW, done) = gradDescent(tX, tY, tempW, 0.00006)
		cmat = common.getConfusionMatrix(getModelFunction(tempW), vX, vY)
		acc = common.getAccuracy(cmat)
		print("Classifier " + str(i+1) + " accuracy: " + str(acc))
		ws.append(tempW)
		weights.append(acc)
		common.printConfusionMatrix(cmat)

	weights = map(lambda x: x / sum(weights), weights)

	X = np.concatenate((X, vX), axis=0)
	l = np.concatenate((tL, vL), axis=0)

	fn = common.getEnsembleModelFunction(map(getModelFunction, ws), weights)
	cmat = common.getConfusionMatrix(fn, vX, vY)
	acc = common.getRawAccuracy(cmat)
	print(acc)
	common.printConfusionMatrix(cmat)
	common.writePredictionFile(fn, l, X, "predictions/pred_"+sys.argv[1], invert=False)
	common.writePredictionFile(fn, labels, testX, "predictions/pred_"+sys.argv[2], invert=False)
