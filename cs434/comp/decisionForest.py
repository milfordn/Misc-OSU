import numpy as np
import math
import common
import sys
import pca

from collections import Iterable

# decisionTree :: (float, int, float), decisionTree, decisionTree
# 		| bool
# note: left is true, right is false

# splits inputs and outputs by a decision function
def splitBy(inputs, outputs, fn):
	leftIns = [] # left = true
	leftOuts = []
	rightIns = [] # right = false
	rightOuts = []
	for i in range(0, len(outputs)):
		if fn(inputs[i]):
			leftIns.append(inputs[i])
			leftOuts.append(outputs[i])
		else:
			rightIns.append(inputs[i])
			rightOuts.append(outputs[i])
	return (leftIns, leftOuts, rightIns, rightOuts)

def getRandomFeatureSet(inputs):
	featureSet = []
	for i in range(0, len(inputs[0])):
		if np.random.rand() < 0.1:
			featureSet.append(i)
	return featureSet

# creates a function that maps an input to a boolean value
def makeDecisionFunction(theta, featureNumber):
	return (lambda x : x[featureNumber] < theta)

def unzip(arr):
	A = []
	B = []
	for a, b in arr:
		A.append(a)
		B.append(b)
	return A, B

def entropy(pT):
	#assert(pT >= 0 and pT <= 1)
	if pT <= 0 or pT >= 1:
		return 0

	pF = 1. - pT
	return -pT * math.log(pT, 2) - pF * math.log(pF, 2)

def infoGain(inputs, outputs, fn):
	countT = len([x for x in outputs if x == 1])
	baseEntropy = entropy(float(countT) / len(outputs))

	(_, leftOuts, _, rightOuts) = splitBy(inputs, outputs, fn)
	leftCountT = len([x for x in leftOuts if x == 1])
	rightCountT = len([x for x in rightOuts if x == 1])

	if len(leftOuts) == 0:
		pLeftT = 0
	else:
		pLeftT = float(leftCountT) / len(leftOuts)

	if len(rightOuts) == 0:
		pRightT = 0
	else:
		pRightT = float(rightCountT) / len(rightOuts)

	leftEntropy = entropy(pLeftT)
	rightEntropy = entropy(pRightT)
	return baseEntropy - pLeftT * leftEntropy - pRightT * rightEntropy

# gets a single decision 
def getStump(inputs, outputs, featureSet=None):
	if featureSet == None:
		featureSet = range(0, len(inputs[0]))

	bestFeature = -1
	bestTheta = 0
	bestGain = float("-inf")
	beftLeftIns = None
	bestLeftOuts = None
	bestRightIns = None
	bestRightOuts = None
	
	#for every feature:
	for i in featureSet:
		# sort the working set by that feature
		ios = zip(inputs, outputs)
		ios.sort(key=lambda(features, _):  features[i])

		leftCountT = 0
		rightCountT = sum(outputs)
		countT = rightCountT

		# for every possible decision boundary in the set
		for j in range(1, len(inputs)):
			(inPrev, outPrev) = ios[j-1]
			(inNext, outNext) = ios[j]
			leftCountT += outPrev
			rightCountT -= outPrev
			#assert(leftCountT + rightCountT == countT)
			# don't bother with this computation if the class doesn't change
			if outPrev == outNext or inPrev[i] == inNext[i]:
				continue

			pBaseT = float(countT) / len(inputs)
			pBaseF = float(len(inputs) - countT) / len(inputs)
			pLeft = float(j) / len(inputs)
			pLeftT = float(leftCountT) / j
			pLeftF = 1 - pLeftT
			pRight = 1 - pLeft
			pRightT = float(rightCountT) / (len(inputs) - j)
			pRightF = 1 - pRightT

			# gini index is HIGH when classes are ROUGHLY EQUAL in proportion
			baseGini = 1 - pBaseT * pBaseT - pBaseF * pBaseF
			leftGini = 1 - pLeftT * pLeftT - pLeftF * pLeftF
			rightGini = 1 - pRightT * pRightT - pRightF * pRightF

			infoGained = baseGini - leftGini * pLeft - rightGini * pRight

			# test it against the best decision boundary so far
			if infoGained >= bestGain:
				#print("New Decision Boundary!!! Gain = " + str(infoGained) + "(j=" + str(j) + "/" + str(len(inputs)) + ")")
				bestLeftIns, bestLeftOuts = unzip(ios[j:])
				bestRightIns, bestRightOuts = unzip(ios[:j])
				#assert(len(bestLeftOuts) + len(bestRightOuts) == len(ios))
				prevFeatureValue = inPrev[i]
				nextFeatureValue = inNext[i]
				bestTheta = prevFeatureValue / 2.0 + nextFeatureValue / 2.0
				bestGain = infoGained
				bestFeature = i
			
	# return the best decision 
	return (bestTheta, bestFeature, bestGain, bestLeftIns, bestLeftOuts, bestRightIns, bestRightOuts)

# uses getStump to recursively build a decision tree
def buildTree(inputs, outputs, depthLimit, featureSet=None):
	#assert(len(inputs) == len(outputs) and len(inputs) != 0)
	
	# get count of each category in working set
	categories = {}
	categories[0] = 0
	categories[1] = 0
	for i in range(0, len(outputs)):
		if outputs[i] in categories:
			categories[outputs[i]] += 1
		else:
			categories[outputs[i]] = 1
	#print((" " * depthLimit) + str(categories))
	
	# if the depth limit is reached, or the working set is entirely one category, then return that category
	if depthLimit == 0 or categories[0] == 0 or categories[1] == 0:
		prob = float(categories[1]) / len(outputs)
		#print("Depth Limit Reached! Probability of knot: " + str(prob))
		return prob

	# get the stump for the working set
	(theta, feature, gain, leftIns, leftOuts, rightIns, rightOuts) = getStump(inputs, outputs, featureSet)
	#assert(len(leftIns) + len(rightIns) == len(inputs))
	#assert(len(leftIns) != 0 and len(rightIns) != 0)

	# get the next left(true) branch with the left (true) working set
	leftTree = buildTree(leftIns, leftOuts, depthLimit - 1)
	# get the next right(false) branch with the right (false) working set
	rightTree = buildTree(rightIns, rightOuts, depthLimit - 1)
	# return the whole tree
	return (theta, feature, gain, leftTree, rightTree)

def runOneTree(decisionTree, x):
	if not isinstance(decisionTree, Iterable):
		return decisionTree

	else:
		(threshold, feature, _, leftTree, rightTree) = decisionTree
		if x[feature] < threshold:
			return runOneTree(leftTree, x)
		else:
			return runOneTree(rightTree, x)

def getModelFunction(tree):
	return (lambda x: 1 - runOneTree(tree, x))

if __name__ == "__main__":
	tL, tX, tY, vL, vX, vY, testL, testX = common.getAllData(sys.argv[1], sys.argv[2])

	sizeForest = 11
	depth = 1
	trees = []
	weights = []
	for i in range(sizeForest):
		tree = buildTree(tX, tY, depth, getRandomFeatureSet(tX))
		fn = getModelFunction(tree)
		trainAccuracy = common.getRawAccuracy(common.getConfusionMatrix(fn, tX, tY))
		vConfmat = common.getConfusionMatrix(fn, vX, vY)
		vAcc = common.getAccuracy(vConfmat)
		common.printConfusionMatrix(vConfmat)
		trees.append(tree)
		weights.append(vAcc)

	weights = map(lambda x: x / sum(weights), weights)

	fn = common.getEnsembleModelFunction(map(getModelFunction, trees), weights)

	cmat = common.getConfusionMatrix(fn, vX, vY)
	acc = common.getRawAccuracy(cmat)
	print(acc)
	common.printConfusionMatrix(cmat)

	X = np.concatenate((tX, vX), axis=0)
	l = np.concatenate((tL, vL), axis=0)

	common.writePredictionFile(fn, l, X, "predictions/pred_dforest_"+sys.argv[1], invert=False)
	common.writePredictionFile(fn, testL, testX, "predictions/pred_dforest_"+sys.argv[2], invert=False)

