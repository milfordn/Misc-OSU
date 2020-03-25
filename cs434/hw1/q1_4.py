import LinearRegression
import sys
import matplotlib as mpl;
mpl.use("Agg")
import matplotlib.pyplot as plt

trainErrs = []
testErrs = []
extraFeatures = []
for i in range(0, 12, 1):
	_, trainErr, testErr = LinearRegression.wholeEnchilada(sys.argv[1], sys.argv[2], numExtraFeatures = i)
	trainErrs.append(trainErr)
	testErrs.append(testErr)
	extraFeatures.append(i)

minErr = min(trainErrs + testErrs)
maxErr = max(trainErrs + testErrs)

for (trainErr, extraFeature) in zip(trainErrs, extraFeatures):
	#print("training error, d=" + str(extraFeature) + "\t|\t" + ("*" * int((trainErr - minErr) / (maxErr - minErr) * 25)) + "\t(" + str(trainErr) + ")")
	pass

#print("\n\n")

for (testErr, extraFeature) in zip(testErrs, extraFeatures):
	#print("testing error, d=" + str(extraFeature) + "\t|\t" + ("*" * int((testErr - minErr) / (maxErr - minErr) * 25)) + "\t(" + str(testErr) + ")")
	pass

plt.bar(map(lambda x: x - 0.2, extraFeatures), trainErrs, width=0.4, color='r', align='center')
plt.bar(map(lambda x: x + 0.2, extraFeatures), testErrs, width=0.4, color='b', align='center')
plt.ylabel("Error (red is training, blue is testing)")
plt.xlabel("Count of Extra Random Features")
plt.savefig("q1_4_graph.png")
