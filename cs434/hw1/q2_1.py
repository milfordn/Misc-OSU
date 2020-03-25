import LogisticRegression
import matplotlib as mpl
mpl.use("Agg")
import matplotlib.pyplot as plt
import sys

trainX, trainY = LogisticRegression.getXY(sys.argv[1])
testX, testY = LogisticRegression.getXY(sys.argv[2])
learningRate = float(sys.argv[3])

done = False
weights = LogisticRegression.randomWeights(trainX)

trainAccuracy = []
testAccuracy = []

for i in range(1, 1000):
	(weights, done) = LogisticRegression.gradDescent(trainX, trainY, weights, learningRate)
	trainAccuracy.append(LogisticRegression.getAccuracy(trainX, trainY, weights))
	testAccuracy.append(LogisticRegression.getAccuracy(testX, testY, weights))

plt.plot(trainAccuracy, color='r')
plt.plot(testAccuracy, color='b')
plt.xlabel("Gradient descent iterations")
plt.ylabel("Accuracy (red is training, blue is testing)")
plt.savefig("q2_1_graph.png")
