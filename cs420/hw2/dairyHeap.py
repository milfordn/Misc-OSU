import sys

def newDairyHeap(d):
	# d = order of the heap
	# 1st list = heap data :: list of (key, value)
	# 2nd list = inverse heap data, such that:
	#	data[inverse[value]] = value = inverse[data[value]]
	return (d, [], {})

def getParent(heap, index):
	(d, _, _) = heap
	return int((index - 1) / d)

def getChildren(heap, index):
	(d, heapData, _) = heap
	children = []
	for i in range(0, d):
		idx = int(d * index + (i + 1))
		if idx < len(heapData):
			children.append(idx)
	return children

def swap(heap, i1, i2):
	(_, heapData, inverseHeapData) = heap
	temp = heapData[i1]
	heapData[i1] = heapData[i2]
	heapData[i2] = temp

	(_, val1) = temp
	(_, val2) = heapData[i1]

	inverseHeapData[val1] = i2
	inverseHeapData[val2] = i1

	# doing some weird shit, so making sure everything stays in order
	(kTest, vTest) = heapData[inverseHeapData[val1]]
	assert(vTest == val1)

def cascadeUp(heap, index):
	parentIndex = getParent(heap, index)
	(_, heapData, _) = heap
	# the parent heap is more than the child heap
	if index > 0 and heapData[index] < heapData[parentIndex]:
		swap(heap, index, parentIndex)
		cascadeUp(heap, parentIndex)
	# else, nothing left to do

def cascadeDown(heap, index):
	#print("cascading down from: " + str(index))	
	children = getChildren(heap, index)
	(_, heapData, _) = heap

	if heapData == []:
		return

	minIdx = -1
	minKey = sys.maxint
	for cIdx in children:
		(cKey, _) = heapData[cIdx]
		if cKey <= minKey:
			minKey = cKey
			minIdx = cIdx

	(currentKey, _) = heapData[index]

	# a child heap is less than the parent
	if minIdx != -1 and minKey < currentKey:
		swap(heap, index, minIdx)
		cascadeDown(heap, minIdx)
	# else, nothing to do

def insert(heap, newKey, newValue):
	(_, heapData, inverseHeapData) = heap
	heapData.append((newKey, newValue))
	inverseHeapData[newValue] = len(heapData) - 1
	cascadeUp(heap, len(heapData) - 1)

def deleteMin(heap):
	(_, heapData, _) = heap
	heapData[0] = heapData[-1] # python why
	heapData.pop(-1)
	#print(str(heapData))
	cascadeDown(heap, 0)

def decreaseKey(heap, value, newKey):
	(_, heapData, inverseHeapData) = heap
	heapIndex = inverseHeapData[value]
	#print("decreasing: " + str(value) + ", at: " + str(heapIndex) + ", len: " + str(len(heapData)))
	(oldKey, _) = heapData[heapIndex]

	# make sure the key is DECREASING
	if newKey > oldKey: 
		return

	heapData[heapIndex] = (newKey, value)
	cascadeUp(heap, heapIndex)

def getMin(heap):
	(_, heapData, _) = heap
	#print(str(heapData))
	return heapData[0]

def isEmpty(heap):
	(_, heapData, _) = heap
	return len(heapData) == 0
