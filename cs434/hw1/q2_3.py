import LogisticRegression
import matplotlib as mpl
mpl.use("Agg")
import matplotlib.pyplot as plt
import sys
import numpy as np

trainX, trainY = LogisticRegression.getXY(sys.argv[1])
testX, testY = LogisticRegression.getXY(sys.argv[2])
learningRate = 0.00001

weightsInitial = LogisticRegression.randomWeights(trainX)

trainAccuracy = []
testAccuracy = []
regs = []

with open(sys.argv[3]) as f:
	for line in f:
		regs.append(float(line))

regs.sort()

for regularization in regs:
	weights = np.copy(weightsInitial)
	for _ in range(0, 1000):
		(weights, done) = LogisticRegression.regularizedGradDescent(trainX, trainY, weights, learningRate, regularization)
	trainAccuracy.append(LogisticRegression.getAccuracy(trainX, trainY, weights))
	testAccuracy.append(LogisticRegression.getAccuracy(testX, testY, weights))
	
plt.plot(regs, trainAccuracy, color='r')
plt.plot(regs, testAccuracy, color='b')
plt.xlabel("Regularization Coefficient")
plt.ylabel("Error (red is training, blue is testing)")
plt.xscale("log")
plt.savefig("q2_3_graph.png")
