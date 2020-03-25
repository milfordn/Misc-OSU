import numpy as np
import sys

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
		vals[i], vecs[:,i] = maxEval, np.copy(vecs[:, maxIndex])
		vals[maxIndex], vecs[:,maxIndex] = tempVal, tempVec

	return vals, vecs

def readData(fname):
        data = []
	header = True
        with open(fname) as f:
                for line in f:
			if header:
				header = False
				continue
                        vals = line.split("\t")
			#without first 2 because of gene label and output label
                        data.append(np.array(list(map(float, vals[2:]))))
        return data

def getEvecsFor(evals, evecs, requireVariance=0.9999):
	totalEvals = sum(evals)
	sumEvals = 0
	numEvals = 0

	for ev in evals:
		if sumEvals > totalEvals * requireVariance:
			break;
		sumEvals += ev
		numEvals += 1

	print("Reduced from " + str(len(evals)) + " features to " + str(numEvals) + " features")
	
	newEvecs = []
	for i in range(numEvals):
		newEvecs.append(evecs[i].real)
	
	return newEvecs

def evecsToMatrix(evecs):
	return np.matrix(evecs)

def transformedData(data, matrix):
	outData = []
	for d in data:
		outData.append(np.squeeze(np.asarray(np.matmul(d, matrix.T))))
	return outData

def getReducedData(data):
	cov = getCov(data)
	evals, evecs = getSortedEvecs(cov)
	topEvecs = getEvecsFor(evals, evecs)
	matrix = evecsToMatrix(topEvecs)
	return transformedData(data, matrix)

