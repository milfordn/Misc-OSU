import dairyHeap
import graph
import math
import sys

def parseGraphList(fname):
	f = open(fname)
	nTests = int(f.readline())
	graphList = []

	for i in range(0, nTests):
		nVerts = int(f.readline())
		graphList.append(graph.newGraph(nVerts))
		vertsList = []

		for j in range(0, nVerts):
			line = f.readline()
			coordString = line.split()
			coords = (int(coordString[0]), int(coordString[1]))
			vertsList.append(coords)
			
			for k in range(0, j):
				# integer-rounded distance
				(otherVx, otherVy) = vertsList[k]
				(vx, vy) = coords
				(dx, dy) = (vx - otherVx, vy - otherVy)
				distance = math.sqrt(dx * dx + dy * dy)
				graph.addEdge(graphList[i], j, k, int(round(distance)))
	
	return graphList

def mstWeight(g):
	pQueue = dairyHeap.newDairyHeap((len(g) - 1) / 2)
	totalWeight = 0
	vertexIsUsed = [0] * len(g)

	dairyHeap.insert(pQueue, 0, 0)
	for i in range(1, len(g)):
		dairyHeap.insert(pQueue, sys.maxint, i)
		
	while not dairyHeap.isEmpty(pQueue):
		(kMin, vMin) = dairyHeap.getMin(pQueue)
		vertexIsUsed[vMin] = 1

		for vAdj in graph.getNeighbors(g, vMin):
			if vertexIsUsed[vAdj] == 0:
				dairyHeap.decreaseKey(pQueue, vAdj, g[vMin][vAdj])

		dairyHeap.deleteMin(pQueue)
		totalWeight += kMin

	return totalWeight

graphList = parseGraphList("graph.txt")

for i in range(0, len(graphList)):
	print("Test Case " + str(i+1) + ": MST weight is " + str(mstWeight(graphList[i])))

