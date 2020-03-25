import matplotlib
matplotlib.use("agg")
import matplotlib.pyplot as plt
import numpy as np

def getMean(data):
	mean = np.copy(data[0])	
	for i in range(1, len(data)):
		mean += data[i]	

	return mean / len(data)		

def getCov(data):
	return np.cov(np.array(data).T)

def getSortedEvecs(cov):
	vals, vecs = np.linalg.eig(cov)
	
	for i in range(len(vals)):
		maxIndex = i
		maxEval = vals[i]
		for j in range(i, len(vals)):
			if vals[j] > maxEval:
				maxIndex = j
				maxEval = vals[j]
		tempVal, tempVec = vals[i], np.copy(vecs[:,i])
		vals[i], vecs[:,i] = maxEval, vecs[:,maxIndex]
		vals[j], vecs[:,j] = tempVal, tempVec

	return vals, vecs

def readData(fname):
        data = []
        with open(fname) as f:
                for line in f:
                        vals = line.split(",")
                        data.append(np.array(list(map(int, vals))))
        return data

def vectorToImage(vec):
	img = []

	for i in range(0, 28):
		img.append([])
		for j in range(0, 28):
			img[i].append(vec[i * 28 + j].real)

	return img

data = readData("p4-data.txt")
cov = getCov(data)
evals, evecs = getSortedEvecs(cov)
mean = getMean(data)

for i in range(1, 11):
	plt.imshow(vectorToImage(evecs[:,i]), interpolation="none")
	plt.title("Eigenvector " + str(i) + "(Eigenvalue " + str(evals[i]) + ")")
	plt.savefig("graphs/pca_2_graph_vec" + str(i) + ".png")
	plt.close()

plt.imshow(vectorToImage(mean), interpolation="none")
plt.savefig("graphs/pca_2_graph_mean.png")
