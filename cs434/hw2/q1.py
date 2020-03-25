import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import sys

def loadData(fname):
	outputs = []
	inputs = []
	with open(fname) as f:
		for line in f:
			stringVals = line.split(",")
			numVals = map(float, stringVals)
			outputs.append(numVals[0])
			del numVals[0]
			inputs.append(numVals)

	return (inputs, outputs)

def getNormalizationFactor(inputs):
	normalizationFactors = []
	normalizationConstants = []
	for i in range(0, len(inputs)):
		featureMax = float("-inf")
		featureMin = float("inf")
		for j in range(0, len(inputs[i])):
			featureMax = max(inputs[i][j], featureMax)
			featureMin = min(inputs[i][j], featureMin)
		normalizationConstants.append(featureMin)
		normalizationFactors.append(featureMax - featureMin)
	return (normalizationConstants, normalizationFactors)

def normalizeBy(inputs, normalizationConstants, normalizationFactors):
	for i in range(0, len(inputs)):
		for j in range(0, len(inputs[i])):
			inputs[i][j] = (inputs[i][j] - normalizationConstants[j]) / normalizationFactors[j]

def getKnn(point, inputs, outputs, K, leaveOut=-1):
	assert(len(outputs) == len(inputs))
	nearest = [0] * K
	distances = [float('inf')] * K

	# loop through all training points
	for i in range(0, len(inputs)):
		# leave this point out of consideration (use for leave-one-out validation)
		if i == leaveOut:
			continue

		newDistance = np.linalg.norm(np.array(point) - np.array(inputs[i]))
		# print("| " + str(point) + " - " + str(inputs[i]) + " | = " + str(newDistance))
		maxDistNeighbor = -1

		# loop through all current nearest neighbors
		for j in range(0, K):
			if newDistance < distances[j] and distances[j] >= distances[maxDistNeighbor]:
				maxDistNeighbor = j

		# replace farthest nearest neighbor with current point if necessary
		if maxDistNeighbor >= 0:
			nearest[maxDistNeighbor] = outputs[i]
			distances[maxDistNeighbor] = newDistance

	return nearest

def vote(knn):
	return np.sign(sum(knn))

def knnOne(trainIns, trainOuts, testIn, testOut, k):
	assert(len(trainIns) == len(trainOuts))
	knns = getKnn(testIn, trainIns, trainOuts, k)
	return vote(knns) == testOut

def leaveOneOut(trainIns, trainOuts, k):
	errors = 0
	for i in range(0, len(trainOuts)):
		knns = getKnn(trainIns[i], trainIns, trainOuts, k, leaveOut = i)
		if vote(knns) != trainOuts[i]:
			errors += 1
	return errors
	
def knnFor(trainIns, trainOuts, testIns, testOuts, k):
	assert(len(trainIns) == len(trainOuts))
	assert(len(testIns) == len(testOuts))
	errors = 0
	for i in range(0, len(testOuts)):
		if not knnOne(trainIns, trainOuts, testIns[i], testOuts[i], k):
			errors += 1
	return errors

def splitForFiveFold(inputs, outputs, index):
	assert(len(outputs) == len(inputs))
	trainIns = []
	trainOuts = []
	validationIns = []
	validationOuts = []
	for i in range(0, len(outputs)):
		if i % 5 == index:
			validationIns.append(inputs[i])
			validationOuts.append(outputs[i])
		else:
			trainIns.append(inputs[i])
			trainOuts.append(outputs[i])
	return (trainIns, trainOuts, validationIns, validationOuts)
	
def fiveFoldValidation(trainIns, trainOuts, k):
	errors = 0
	for i in range(0, 5):
		vtrainIns, vtrainOuts, validationIns, validationOuts = splitForFiveFold(trainIns, trainOuts, i)
		assert(len(vtrainIns) == len(vtrainOuts))
		assert(len(validationIns) == len(validationOuts))
		for i in range(0, len(validationOuts)):
			point = validationIns[i]
			if not knnOne(vtrainIns, vtrainOuts, point, validationOuts[i], k):
				errors += 1
	return errors

trainIns, trainOuts = loadData(sys.argv[1])
testIns, testOuts = loadData(sys.argv[2])
assert(len(trainIns) == len(trainOuts))
assert(len(testIns) == len(testOuts))
normalizationConstants, normalizationFactors = getNormalizationFactor(trainIns)

normalizeBy(trainIns, normalizationConstants, normalizationFactors)
normalizeBy(testIns, normalizationConstants, normalizationFactors)

total = len(testOuts)

print("Train Set Size: " + str(len(trainOuts)))
print("Test Set Size: " + str(total))

xs = []
trainErrs = []
testErrs = []
validErrs = []

if len(sys.argv) >= 4:
	iterations = [int(sys.argv[3])]
else:
	iterations = range(1, 53, 2)

for i in iterations:
	print("K = " + str(i))
	trainError = knnFor(trainIns, trainOuts, trainIns, trainOuts, i)
	print("\tTraining Set: " + str(100. * trainError / total) + "% errors")
	validError = leaveOneOut(trainIns, trainOuts, i)
	print("\tCross-Validation: " + str(100. * validError / total) + "% errors")
	testError = knnFor(trainIns, trainOuts, testIns, testOuts, i)
	print("\tTesting Set: " + str(100. * testError / total) + "% errors")

	xs.append(i)
	trainErrs.append(trainError)
	testErrs.append(testError)
	validErrs.append(validError)

if len(sys.argv) < 4:
	plt.plot(xs, trainErrs)
	plt.plot(xs, testErrs)
	plt.plot(xs, validErrs)
	plt.legend(["Training Errors", "Testing Errors", "Validation Errors"], loc="lower right")
	plt.savefig("q1_graph.png")

