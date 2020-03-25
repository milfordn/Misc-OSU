import decisionTree
import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

trainIns, trainOuts = decisionTree.loadData(sys.argv[1])
testIns, testOuts = decisionTree.loadData(sys.argv[2])

if len(sys.argv) > 3:
	d = [int(sys.argv[3])]
else:
	d = range(1, 7)

trainErrs = []
testErrs = []
ds = []

for i in d:
	tree = decisionTree.buildTree(trainIns, trainOuts, i)

	trainErr = 100. * decisionTree.runTree(tree, trainIns, trainOuts) / len(trainOuts)
	testErr = 100. * decisionTree.runTree(tree, testIns, testOuts) / len(trainOuts)

	trainErrs.append(trainErr)
	testErrs.append(testErr)
	ds.append(i)

	print("\nd = " + str(i) + " :")
	print("\n\tTraining Error:\t" + str(trainErr) + "%")
	print("\tTesting Error:\t" + str(testErr) + "%")

if len(sys.argv) <= 3:
	plt.plot(ds, trainErrs)
	plt.plot(ds, testErrs)
	plt.legend(["Training Error", "Testing Error"], "center right")
	plt.savefig("q2_2_graph.png")
