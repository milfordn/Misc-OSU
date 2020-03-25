import numpy as np

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
		vals[i], vecs[:,i] = maxEval, vecs[:, maxIndex]
		vals[j], vecs[:,j] = tempVal, tempVec

	return vals, vecs

def readData(fname):
        data = []
        with open(fname) as f:
                for line in f:
                        vals = line.split(",")
                        data.append(np.array(list(map(float, vals))))
        return data

#np.set_printoptions(10)
data = readData("p4-data.txt")
cov = getCov(data)
evals, evecs = getSortedEvecs(cov)

for i in range(1, 11):
	print("Eigenvalue " + str(i) + ": " + str(evals[i]))
	pass
