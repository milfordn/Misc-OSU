import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import nn

learnRate = 0.1

if len(sys.argv) > 1: #use given settings
	dropout = float(sys.argv[1])
	momentum = float(sys.argv[2])
	decay = float(sys.argv[3])

	(model, optimizer, criterion) = nn.init(learnRate, momentum=momentum, dropout=dropout, wd=decay)
	(accv, errv, losst) = nn.fullTrain(model, optimizer, criterion)
	testAccuracy = nn.test(model)

	print('Test Accuracy:\t' + str(testAccuracy.item() * 100.) + "%\n")

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

	plt.title("Q3 Final Graph (d=" + str(dropout) + ", m=" + str(momentum) + ", wd=" + str(decay) + ")")
	plt.savefig("graphs/q3_graph.png")
	plt.close()

else: #go through a bunch of tests to find optimal settings
	decays = [0.1, 0.01, 0.001, 0.0001, 0.00001]
	momentums = [1, 0.1, 0.01, 0.001, 0.0001]
	dropouts = [0.2, 0.02, 0.002, 0.0002, 0.00002]

	print("######## MOMENTUM ########")
	accuracies = []
	for momentum in momentums:	
		(model, optimizer, criterion) = nn.init(learnRate, momentum=momentum)

		(accv, errv, losst) = nn.fullTrain(model, optimizer, criterion, prn=False)
		testAccuracy = nn.test(model)
		print('Test Accuracy:\t' + str(testAccuracy.item() * 100.) + '%\n')
		accuracies.append(testAccuracy)

	plt.title("Q3 Momentum Graph")
	plt.plot(momentums, accuracies)
	plt.xscale('log')
	plt.xlabel("Momentum")
	plt.ylabel("Accuracy (%)")
	plt.savefig("graphs/q3_graph_accuracy_momentum")
	plt.close()

	print("######## WEIGHT DECAY ########")
	accuracies = []
	for decay in decays:
		(model, optimizer, criterion) = nn.init(learnRate, wd=decay)
	
		(accv, errv, losst) = nn.fullTrain(model, optimizer, criterion, prn=False)
		testAccuracy = nn.test(model)
		accuracies.append(testAccuracy)
		print('Test Accuracy:\t' + str(testAccuracy.item() * 100.) + '%\n')

	plt.title("Q3 Weight Decay Graph")
	plt.plot(decays, accuracies)
	plt.xscale('log')
	plt.xlabel("Weight Decay")
	plt.ylabel("Accuracy (%)")
	plt.savefig("graphs/q3_graph_accuracy_decay")
	plt.close()

	print("######## DROPOUT ########")
	accuracies = []
	for dropout in dropouts:
		(model, optimizer, criterion) = nn.init(learnRate, dropout=dropout)

		(accv, errv, losst) = nn.fullTrain(model, optimizer, criterion, prn=False)
		testAccuracy = nn.test(model)
		accuracies.append(testAccuracy)
		print('Test Accuracy:\t' + str(testAccuracy.item() * 100.) + '%\n')
	
	plt.title("Q3 Dropout Rate Graph")
	plt.plot(dropouts, accuracies)
	plt.xscale('log')
	plt.xlabel("Dropout Rate")
	plt.ylabel("Accuracy (%)")
	plt.savefig("graphs/q3_graph_accuracy_dropout")
	plt.close()


