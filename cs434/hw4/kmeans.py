import numpy as np
import math
import sys
import matplotlib
matplotlib.use("agg")
import matplotlib.pyplot as plt

def readData(fname):
	data = []
	with open(fname) as f:
		for line in f:
			vals = line.split(",")
			data.append(np.array(list(map(int, vals))))
	return data

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
		center = np.zeros(len(data[i]), dtype=int)
		for c in clusters[i]:
			center += data[c]

		# divide by number of points in cluster
		if len(clusters[i]) > 0:
			center /= len(clusters[i])

		#make that the new mean
		means[i] = center

def initMeans(k):
	means = []
	for i in range(k):
		means.append(np.random.randint(0, 255, (784)))

	return means

def kMeansCluster(k, data, prn=False):
	means = initMeans(k)
	clusters = []
	totalSSEs = []

	print(str(k) + " Clusters")
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

########## q2.1 ##########

fname = "p4-data.txt"
data = readData(fname)

if len(sys.argv) <= 1:
	print("Graph of SSE over iterations...")
	clusters, means, totalSSEs = kMeansCluster(2, data)
	
	plt.plot(totalSSEs)
	plt.xlabel("Iterations")
	plt.ylabel("Sum of Squared Error")
	plt.savefig("graphs/q2-1-graph.png")

########## q2.2 ##########

if len(sys.argv) <= 1:
	print("Graph of SSE over number of clusters...")
	ks = range(2, 11)

	SSEs = []
	for k in ks:
		print("k = " + str(k))
		bestSSE = float("inf")
		for _ in range(0, 10):
			clusters, means, totalSSEs = kMeansCluster(k, data)
			
			if totalSSEs[-1] < bestSSE:
				bestSSE = totalSSEs[-1]

		SSEs.append(bestSSE)

	plt.close()
	plt.plot(ks, SSEs)
	plt.xlabel("K")
	plt.ylabel("Sum of Squared Error")
	plt.savefig("graphs/q2-2-graph.png")

########## Intended Implementation ##########

if len(sys.argv) > 1:
	clusters, means, totalSSEs = kMeansCluster(int(sys.argv[1]), data, prn=True)
