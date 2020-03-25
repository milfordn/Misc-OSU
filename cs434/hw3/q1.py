import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import nn

if len(sys.argv) < 2:
	learnRates = [1., 0.1, 0.01, 0.001, 0.0001]
else:
	learnRates = [float(sys.argv[1])]

for learnRate in learnRates:
	print("######## LEARNING RATE = " + str(learnRate) + " ########\n")
	(model, optimizer, criterion) = nn.init(learnRate)

	(accv, errv, losst) = nn.fullTrain(model, optimizer, criterion)
	testAccuracy = nn.test(model)
	print('Test Accuracy:\t' + str(testAccuracy.item() * 100.) + '%\n')

	fig, ax1 = plt.subplots()

	ax1.set_xlabel('Epochs')
	ax1.set_ylabel('Validation Error', color='tab:red')
	ax1.plot(errv, color='tab:red')
	ax1.tick_params(axis='y', labelcolor='tab:red')

	ax2 = ax1.twinx()

	ax2.set_ylabel('Training Loss', color='tab:blue')
	ax2.plot(losst, color='tab:blue')
	ax2.tick_params(axis='y', labelcolor='tab:blue')

	fig.tight_layout()

	plt.title("Q1 Graph With Learning Rate = " + str(learnRate))
	plt.savefig("graphs/q1_graph_loss_lr=" + str(learnRate) + ".png")
	plt.close()

print("\n######## DONE ########\n")
