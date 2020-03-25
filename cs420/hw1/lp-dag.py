
UNVISITED = 0
VISITED = 1

f = open("graph.txt")

nVerts = int(f.readline())
nEdges = int(f.readline())

graph = []

for i in range(0, nVerts):
	graph.append([0] * nVerts)

for i in range(0, nEdges):
	verts = f.readline().split(" ")
	vertFrom = int(verts[0])
	vertTo = int(verts[1])
	graph[vertFrom - 1][vertTo - 1] = 1

def printGraph(g):
	s = "#"
	for i in range(0, len(g)):
		s += " " + str(i + 1)
	print s
	for i in range(0, len(g)):
		s = str(i + 1)
		for j in range(0, len(g[i])):
			s += " " + str(g[i][j])
		print s

def getNeighbors(g, vert):
	neighbors = []
	for i in range(0, len(g[vert])):
		if(g[vert][i] == 1):
			neighbors.append(i)
	return neighbors

def getPredecessors(g, vert):
	pred = []
	for i in range(0, len(g)):
		if(g[i][vert] == 1):
			pred.append(i)
	return pred

def topologicalSortOnce(g, vert, vertStatuses, topSorted):
	neighbors = getNeighbors(g, vert)
	#print str(vert + 1) + str(vertStatuses) + str(neighbors)
	for i in range(0, len(neighbors)):
		if(vertStatuses[neighbors[i]] == UNVISITED): #only recurse for unvisited vertices
			topologicalSortOnce(g, neighbors[i], vertStatuses, topSorted)
	vertStatuses[vert] = VISITED
	topSorted.append(vert)

def topologicalSort(g):
	topSorted = []
	vertStatuses = [UNVISITED] * len(g)
	for i in range(len(g)):
		if(vertStatuses[i] == UNVISITED):
			topologicalSortOnce(g, i, vertStatuses, topSorted)
	topSorted.reverse()
	return topSorted

# O(V^2) with adjacency matrix
# O(V+E) with adjacency list if predecessors are generated during the DFS
def longestPath(g, topSorted):
	lengthList = [-1] * len(g)
	longestPathPred = [-1] * len(g)
	longestPathTotal = -1
	longestPathEnd = -1

	for i in range(0, len(topSorted)):
		prev = getPredecessors(g, topSorted[i])
		maxLen = 0
		maxLenPred = -1

		#find longest path predecessor to this vertex
		for vert in prev: 
			if lengthList[vert] >= maxLen:
				maxLen = lengthList[vert] + 1
				maxLenPred = vert
		lengthList[topSorted[i]] = maxLen
		longestPathPred[topSorted[i]] = maxLenPred
		
		#if this vertex is the new longest path, remember it
		if maxLen > longestPathTotal:
			#print "found new path end: " + str(topSorted[i] + 1)
			longestPathTotal = maxLen
			longestPathEnd = topSorted[i]

	longestPath = []

	#backtrack from the end along the predecessors to make the path
	while longestPathEnd != -1:
		longestPath.append(longestPathEnd)
		longestPathEnd = longestPathPred[longestPathEnd]

	longestPath.reverse()
	return longestPath

def printPath(path):
	print "Length of longest path: " + str(len(path) - 1)
	s = "Path: " + str(path[0] + 1)
	for v in path[1:]:
		s += " - " + str(v + 1)
	print s

#printGraph(graph)
topSorted = topologicalSort(graph)
path = longestPath(graph, topSorted)
printPath(path)
