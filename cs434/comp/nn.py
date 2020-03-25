import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms

import sys
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import common

if torch.cuda.is_available():
	device = torch.device('cuda')
else:
	device = torch.device('cpu')
	
print('Using PyTorch version:', torch.__version__, ' Device:', device)
#torch.set_default_tensor_type('torch.LongTensor')

##### Load Data #####

def dataToTensor(dX, dY):
	X = torch.Tensor(dX)
	y = torch.tensor(dY, dtype=torch.long)
	return X, y

batch_size = 32

tL, X, Y, vL, vX, vY, testL, testX = common.getAllData(sys.argv[1], sys.argv[2])
inSize = len(X[0])

(i, o) = dataToTensor(X, Y)
train_dataset = torch.utils.data.TensorDataset(i, o)

(i, o) = dataToTensor(vX, vY)
validation_dataset = torch.utils.data.TensorDataset(i, o)

train_loader = torch.utils.data.DataLoader(dataset=train_dataset, 
					   batch_size=batch_size, 
					   shuffle=True)

validation_loader = torch.utils.data.DataLoader(dataset=validation_dataset,
						batch_size=batch_size,
						shuffle=False)

print("Datasets Loaded")

##### Network Definition #####

class Net(nn.Module):
	def __init__(self, dropout):
		super(Net, self).__init__()
		self.inLen = inSize
		self.fc1 = nn.Linear(self.inLen, 100)
		self.fc1_drop = nn.Dropout(dropout)
		self.fc2 = nn.Linear(100, 2)
		self.activation = F.relu

	def forward(self, x):
		x = x.view(-1, self.inLen)
		x = self.activation(self.fc1(x))
		x = self.fc1_drop(x)
		return F.log_softmax(self.fc2(x), dim=1)

def init(learnRate, dropout=0.2, momentum=0.5, wd=0, structure="default"):
	model = Net(dropout).to(device)
	optimizer = torch.optim.SGD(model.parameters(), lr=learnRate, momentum=momentum, weight_decay=wd)
	criterion = nn.NLLLoss()
	return (model, optimizer, criterion)

##### Learning #####

def train(model, optimizer, criterion, trainingLoss):
	# Set model to training mode
	model.train()
	
	avgLoss = 0
	# Loop over each batch from the training set
	for batch_idx, (data, target) in enumerate(train_loader):
		#data = data.double()
	
	# Zero gradient buffers
		optimizer.zero_grad() 
		
		# Pass data through the network
		output = model(data)
		#output = output.double()

		#print(target.type(), data.type(), output.type())
		#print(data, target, len(target))

		# Calculate loss
		loss = criterion(output, target)
		avgLoss += loss

		# Backpropagate
		loss.backward()
		
		# Update weights
		optimizer.step()
	trainingLoss.append(avgLoss / len(train_loader))

def validate(model, criterion, error_vector, accuracy_vector):
	model.eval()
	correct = 0
	for data, target in validation_loader:
		output = model(data)
		pred = output.data.max(1)[1] # get the index of the max log-probability
		correct += pred.eq(target.data).cpu().sum()

	error = len(validation_loader.dataset) - correct
	accuracy = correct.to(torch.float32) / len(validation_loader.dataset)
	error = error.to(torch.float32) / len(validation_loader.dataset)
	accuracy_vector.append(accuracy)
	error_vector.append(error)

def test(model):
	model.eval()
	correct = 0
	for data, target in test_loader:
		output = model(data)
		pred = output.data.max(1)[1]
		correct += pred.eq(target.data).cpu().sum()

	accuracy = correct.to(torch.float32) / len(test_loader.dataset)
	return accuracy

def getModelFunction(model):
	def outfn(x):
		model.eval()
		output = model(torch.Tensor(x))
		p0 = output.data[0][0].item()
		p1 = output.data[0][1].item()
		#print(p0, p1, p0 / (p0 + p1))
		return p0 / (p0 + p1)
	return outfn

##### Script #####

def fullTrain(model, optimizer, criterion, prn=True):
	accv, errv, losst = [], [], []
	epoch = 0
	while True:
		train(model, optimizer, criterion, losst)
		validate(model, criterion, errv, accv)
		epoch += 1
		if prn:
			print('Epoch ' + str(epoch))
			print('Training Loss: \t' + str(losst[-1].item()))
			print('Verification Accuracy: \t' + str(accv[-1].item() * 100.) + '%\n')

		if (epoch > 5 and accv[-1] <= accv[-2] and accv[-2] < accv[-3]):
			break
	return accv, errv, losst

model, optimizer, criterion = init(0.1)
fullTrain(model, optimizer, criterion)
fn = getModelFunction(model)
X = (X + vX)
L = (tL + vL)
confmat = common.getConfusionMatrix(fn, X, Y)
common.printConfusionMatrix(confmat)
print(common.getAccuracy(confmat))
common.writePredictionFile(fn, L, X, "pred_nn_"+sys.argv[1], invert=False)
common.writePredictionFile(fn, testL, testX, "pred_nn_" + sys.argv[2], invert=False)
