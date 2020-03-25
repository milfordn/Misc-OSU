import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision import datasets, transforms

import sys
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

if torch.cuda.is_available():
    device = torch.device('cuda')
else:
    device = torch.device('cpu')
    
print('Using PyTorch version:', torch.__version__, ' Device:', device)
#torch.set_default_tensor_type('torch.DoubleTensor')

##### Load Data #####

def cifarToTensor(cifar):
	X = torch.Tensor(cifar[b'data'].astype('float') / 255.)
	y = cifar[b'labels']
	y = torch.tensor(y, dtype=torch.long)
	return X, y

def unpickle(fname):
	import pickle
	with open(fname, "rb") as f:
		data = pickle.load(f, encoding="bytes")
	return data

batch_size = 32

trainSets = []
for i in range(1, 5):
	train_raw = unpickle("../cifar-10-batches-py/data_batch_" + str(i))
	(i, o) = cifarToTensor(train_raw)
	trainSets.append(torch.utils.data.TensorDataset(i, o))
train_dataset = torch.utils.data.ConcatDataset(trainSets)

validation_raw = unpickle("../cifar-10-batches-py/data_batch_5")
(i, o) = cifarToTensor(validation_raw)
validation_dataset = torch.utils.data.TensorDataset(i, o)

test_raw = unpickle("../cifar-10-batches-py/test_batch")
(i, o) = cifarToTensor(test_raw)
test_dataset = torch.utils.data.TensorDataset(i, o)

train_loader = torch.utils.data.DataLoader(dataset=train_dataset, 
                                           batch_size=batch_size, 
                                           shuffle=True)

validation_loader = torch.utils.data.DataLoader(dataset=validation_dataset, 
                                                batch_size=batch_size, 
                                                shuffle=False)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=False)
print("Datasets Loaded")

##### Network Definition #####

class Net(nn.Module):
    def __init__(self, dropout, structure):
        super(Net, self).__init__()
        self.structure = structure
        if(structure == "default"):
            self.fc1 = nn.Linear(32*32*3, 100)
            self.fc1_drop = nn.Dropout(dropout)
            self.fc2 = nn.Linear(100, 10)
        elif structure == "q4":
            self.fc1 = nn.Linear(32*32*3, 50)
            self.fc1_drop = nn.Dropout(dropout)
            self.fc2 = nn.Linear(50, 50)
            self.fc2_drop = nn.Dropout(dropout)
            self.fc3 = nn.Linear(50, 10)
       	self.activation = torch.sigmoid

    def forward(self, x):
        x = x.view(-1, 32*32*3)
        x = self.activation(self.fc1(x))
        x = self.fc1_drop(x)
        if self.structure == "q4":
            x = self.activation(self.fc2(x))
            x = self.fc2_drop(x)
        return F.log_softmax(self.fc2(x), dim=1)

    def switchActivation(self, st):
        if st == "sigmoid":
            self.activation = torch.sigmoid
        elif st == "relu":
            self.activation = F.relu

def init(learnRate, dropout=0.2, momentum=0.5, wd=0, structure="default"):
	model = Net(dropout, structure).to(device)
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

	# more than 10 epochs and accuracy has decreased
        if(epoch > 10 and accv[-1] <= accv[-2]):
            break
    return accv, errv, losst

