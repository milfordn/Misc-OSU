import numpy as np
import math
import common
import sys

def clusterSSE(cluster, mean, data):
	error = 0
	for d in cluster:
		dist = np.linalg.norm(mean - data[d])
		error += dist * dist
	return error

#sum of squared euclidean distances
def sse(clusters, means, data):
	error = 0
	
	#loop over clusters
	for i in range(len(means)):
		# aggregate cluster errors
		error += clusterSSE(clusters[i], means[i], data)
	return error

def getClusterInfo(clusters, means, sses):
	info = ""
	for i in range(0, len(means)):
		info += "Cluster " + str(i+1) + "\n"
		info += "\tSize: " + str(len(clusters[i])) + " Datapoints\n"
		info += "\tSSE: " + str(sses[i]) + "\n"
	
	return info

def assign(means, data):
	clusters = []

	# initialize clusters array
	for i in range(len(means)):
		clusters.append([])

	# loop over all data points	
	for i in range(len(data)):
		minCluster = -1
		minLen = float("inf")
		
		# find the closest mean point
		for m in range(len(means)):
			dist = np.linalg.norm(means[m] - data[i])
			if dist <= minLen:
				minLen = dist
				minCluster = m

		# assign current data point to the closest mean's cluster
		clusters[minCluster].append(i)
		#print("Assigned " + str(i) + " to cluster " + str(minCluster))

	return clusters

def recenter(clusters, means, data):
	# loop over means and clusters
	for i in range(len(clusters)):

		# aggregate points in cluster
		center = np.zeros(len(data[i]))
		for c in clusters[i]:
			center += data[c]

		# divide by number of points in cluster
		if len(clusters[i]) > 0:
			center /= len(clusters[i])

		#make that the new mean
		means[i] = center

def initMeans(k, X):
	means = []
	for i in range(k):
		means.append(np.random.rand(len(X[0])))

	return means

def kMeansCluster(k, data, prn=False):
	means = initMeans(k, data)
	clusters = []
	totalSSEs = []

	#print(str(k) + " Clusters")
	while True:
		clusters = assign(means, data)
		recenter(clusters, means, data)
	
		SSEs = []
		totalSSE = 0
		for i in range(0, k):
			SSEs.append(clusterSSE(clusters[i], means[i], data))
			totalSSE += SSEs[-1]

		if prn:
			#print(getClusterInfo(clusters, means, SSEs))
			print("SSE: " + str(totalSSE))
		curSSE = totalSSE
		if len(totalSSEs) > 0 and curSSE >= totalSSEs[-1]:
			break
		totalSSEs.append(totalSSE)

	return (clusters, means, totalSSEs)

def cluster(k, data, attempts=5):
	bestSSE = float("inf")
	bestClusters = []
	bestMeans = []
	for _ in range(attempts):
		clusters, means, totalSSEs = kMeansCluster(k, data)
		if totalSSEs[-1] < bestSSE:
			bestSSE = totalSSEs[-1]
			bestClusters = clusters
			bestMeans = means
	return (bestSSE, bestClusters, bestMeans)

def printCountOfCluster(clusters, X, Y):
	countT = []
	countF = []
	for c in clusters:
		cT = 0
		cF = 0
		for i in c:
			if Y[i] == 1:
				cT += 1
			else:
				cF += 1
		countT.append(cT)
		countF.append(cF)
	
	print(countT)
	print(countF)

def tryClusters(ks, data, labels):
	for k in ks:
		sse, clusters, _ = cluster(k, data)
		print("k=" + str(k) + ": " + str(sse))
		printCountOfCluster(clusters, data, labels)

if __name__ == "__main__":
	X, Y = common.getXY(sys.argv[1])
	X = common.normalize(X)
	ks = [2, 3, 4, 5, 6, 7, 8, 9]
	tryClusters(ks, X, Y)
