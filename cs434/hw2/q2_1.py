import decisionTree
import sys

trainIns, trainOuts = decisionTree.loadData(sys.argv[1])
testIns, testOuts = decisionTree.loadData(sys.argv[2])

tree = decisionTree.buildTree(trainIns, trainOuts, 1)
(theta, feature, gain, leftCategory, rightCategory) = tree
print("Learned Tree: ")
print("\tFeature " + str(feature) + ": (Information gain: " + str(gain) + ")")
print("\t| > " + str(theta) + " -> " + str(leftCategory))
print("\t| < " + str(theta) + " -> " + str(rightCategory))

trainErrs = decisionTree.runTree(tree, trainIns, trainOuts)
testErrs = decisionTree.runTree(tree, testIns, testOuts)

print("\nTraining Error:\t" + str(trainErrs * 100. / len(trainOuts)) + "%")
print("Testing Error:\t" + str(testErrs * 100. / len(testOuts)) + "%")
