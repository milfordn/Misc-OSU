import numpy as np

def getXY(fname):
	X = []
	Y = []
	header = False
	with(open(fname)) as f:
		for line in f:
			if not header:
				header = True
				continue
			#have to cut out label
			stringVals = line.split('\t')[1:]
			numVals = list(map(float, stringVals))
			Y.append(numVals[0])
			del numVals[0]
			X.append(np.array(numVals))
	return X, Y

def getLabeledXY(fname):
	X = []
	Y = []
	L = []
	header = False
	with(open(fname)) as f:
		for line in f:
			if not header:
				header = True
				continue
			stringVals = line.split('\t')
			stringVals = filter(lambda x: x and not x.isspace(), stringVals)
			L.append(stringVals[0])
			numVals = list(map(float, stringVals[1:]))
			Y.append(numVals[0])
			del numVals[0]
			X.append(np.array(numVals))
	return L, X, Y


def getLabeledX(fname):
	X = []
	labels = []
	header = False
	with open(fname) as f:
		for line in f:
			if not header:
				header = True
				continue
			stringVals = line.split('\t')
			stringVals = filter(lambda x: x and not x.isspace(), stringVals)
			label = stringVals[0]
			numVals = list(map(float, stringVals[1:]))
			X.append(np.array(numVals))
			labels.append(label)
	X = normalize(X)
	return labels, X

def confirmNormalized(X):
	if np.amax(X) > 1:
		print(np.amax(X))
	if np.amin(X) < 0:
		print(np.amin(X))
	assert(np.amin(X) >= 0)
	assert(np.amax(X) <= 1)

def getNormalizationFactors(X):
	b = np.min(X, axis=0)
	m = np.max(X - b, axis=0)
	return (m, b)

def normalizeBy(X, (m, b)):
	X -= b
	X /= m	
	for i in range(len(X)):
		for j in range(len(X[i])):
			if np.isnan(X[i][j]):
				X[i][j] = 0
	return X

def normalize(X):
	X -= np.min(X, axis=0)
	X /= np.max(X, axis=0)

	for i in range(len(X)):
		for j in range(len(X[i])):
			if np.isnan(X[i][j]):
				X[i][j] = 0
	confirmNormalized(X)
	return X

def addBias(X):
	for x in X:
		np.append(x, 1)
	return X

def getAllData(fnameTrain, fnameTest):
	L, X, Y = getLabeledXY(fnameTrain)
	l, testX = getLabeledX(fnameTest)
	fac = getNormalizationFactors(X)
	X = normalizeBy(X, fac)
	testX = normalizeBy(testX, fac)
	addBias(X)
	addBias(testX)
	tX, tY, tL, vX, vY, vL = getValidationSets(L, X, Y)
	return tL, tX, tY, vL, vX, vY, l, testX

def getAccuracy(confmat):
	tp, fp, tn, fn = confmat
	return 2 * float(tp) / (2 * tp + fn + fp)

def getRawAccuracy(confmat):
	tp, fp, tn, fn = confmat
	return float(tp + tn) / (tp + tn + fp + fn)

def printConfusionMatrix(confmat):
	tp, fp, tn, fn = confmat
	print("\t\tTrue\tFalse")
	print("Positive\t" + str(tp) + "\t" + str(fp))
	print("Negative\t" + str(tn) + "\t" + str(fn))

def getConfusionMatrix(model, X, Y):
	fp, fn, tp, tn = 0, 0, 0, 0
	for xi, yi in zip(X, Y):
		prediction = model(xi) > 0.5
		actual = yi > 0.5
		if prediction and actual:
			tp += 1
		elif prediction and not actual:
			fp += 1
		elif (not prediction) and (not actual):
			tn += 1
		elif (not prediction) and actual:
			fn += 1
	return (tp, fp, tn, fn)
	
def writePredictionFile(model, labels, X, fout, invert=False):
	with open(fout, "w") as f:
		for i in range(len(labels)):
			pred = model(X[i])
			if invert:
				pred = 1 - pred
			f.write(labels[i] + "," + str(pred) + "\n")

def getValidationSets(labels, X, Y, proportion=0.1):
	tX, vX = [], []
	tY, vY = [], []
	tL, vL = [], []
	
	thing1 = (int)(1 / proportion)
	countT = 0
	countF = 0
	for i in range(0, len(Y)):
		if Y[i] == 1:
			countT += 1
			using = countT
		else:
			countF += 1
			using = countF

		if using % thing1 == 0:
			vX.append(X[i])
			vY.append(Y[i])
			vL.append(labels[i])
		else:
			tX.append(X[i])
			tY.append(Y[i])
			tL.append(labels[i])
	print("Training set: " + str(len(Y)) + " examples, Validation set: " + str(len(vY)) + " examples")
	print("Training: " + str(sum(tY)) + " true examples, Validation: " + str(sum(vY)) + " true examples")
	return tX, tY, tL, vX, vY, vL

def getEvenSamplingSets(X, Y):
	tX, fX = [], []

	for i in range(0, len(Y)):
		idx = np.random.randint(len(X))
		if Y[i] == 1:
			tX.append(X[idx])
		else:
			fX.append(X[idx])

	while len(tX) != len(fX):
		if len(tX) > len(fX):
			idx = np.random.randint(len(fX))
			fX.append(fX[idx])
		else:
			idx = np.random.randint(len(tX))
			tX.append(tX[idx])

	return tX + fX, ([1] * len(tX)) + ([0] * len(fX))

def getEnsembleModelFunction(modelFunctions, weights):
	def outfn(x):
		votes = 0
		for i in range(len(modelFunctions)):
			votes += modelFunctions[i](x) * weights[i]
		return votes
	return outfn
