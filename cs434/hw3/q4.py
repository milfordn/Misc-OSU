import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import nn

learnRate = float(sys.argv[1])
structures = ["default", "q4"]

for structure in structures:

	print("######## Testing " + structure + " Structure ########\n")

	(model, optimizer, criterion) = nn.init(learnRate, structure=structure)

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

	if structure == "q4":
		plt.title("Q4 Graph 50/50 Structure")
		plt.savefig("graphs/q4_graph_loss_5050.png")
	else:
		plt.title("Q4 Graph Normal Structure")
		plt.savefig("graphs/q4_graph_loss_normal.png")
	plt.close()

