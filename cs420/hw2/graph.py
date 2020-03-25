def newGraph(n):
	graph = []
	for i in range(0, n):
		graph.append([-1] * n)
	return graph

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
		if(g[vert][i] >= 0):
			neighbors.append(i)
	return neighbors

def getPredecessors(g, vert):
	pred = []
	for i in range(0, len(g)):
		if(g[i][vert] >= 0):
			pred.append(i)
	return pred

def addEdge(g, v1, v2, w):
	g[v1][v2] = w
	g[v2][v1] = w #undirected graph
