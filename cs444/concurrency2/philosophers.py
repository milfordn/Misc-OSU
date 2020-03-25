import time
import random
from multiprocessing import Process, Lock

AMT_PHILOSOPHERS = 5
PHIL_NAMES = ["Diogenes", "Pythagoras", "Socrates", "Plato", "Aristotle"]

statuses = []
fork_statuses = []
forks = []

for x in range(0, AMT_PHILOSOPHERS):
	statuses.append("thinking")
	fork_statuses.append("nobody")
	forks.append(Lock()) #array of mutexes

def print_statuses():
	return;
	for x in range(0, AMT_PHILOSOPHERS):
		print PHIL_NAMES[x] + " is " + statuses[x]
	for x in range(0, AMT_PHILOSOPHERS):
		print "Fork " + str(x) + " is held by " + fork_statuses[x]	

def left_fork_index(i):
	return i
def right_fork_index(i):
	if(i - 1 < 0):
		return AMT_PHILOSOPHERS - 1
	return i-1

def get_forks(i):
	left_fork = left_fork_index(i)
	right_fork = right_fork_index(i)
	
	has_left = False
	has_right = False
	while True:
		if(has_left or forks[left_fork].acquire(False)): #non-blocking
			fork_statuses[left_fork] = PHIL_NAMES[i]
			has_left = True
		elif(has_right): #does not have or could not get left fork and has right fork
			forks[right_fork].release() #release other fork if we can't have both
			fork_statuses[right_fork] = "nobody"
			print_statuses()
			has_right = False
		
		#repeat for other side
		if(has_right or forks[right_fork].acquire(False)):
			fork_statuses[right_fork] = PHIL_NAMES[i]
			has_right = True
		elif(has_left):
			forks[left_fork].release()
			fork_statuses[left_fork] = "nobody"
			print_statuses()
			has_left = False

		if(has_left and has_right):
			break

def put_forks(i):
	forks[left_fork_index(i)].release()
	forks[right_fork_index(i)].release()
	fork_statuses[left_fork_index(i)] = "nobody"
	fork_statuses[right_fork_index(i)] = "nobody"

def philosophize(i, unused):
	while True:
		statuses[i] = "thinking"
		print_statuses()
		time.sleep(random.randint(1, 20)) #think
		statuses[i] = "waiting"
		print_statuses()
		get_forks(i)
		statuses[i] = "eating"
		print_statuses()
		time.sleep(random.randint(20, 20)) #eat
		put_forks(i)


philosophers = []
for x in range(0, AMT_PHILOSOPHERS):
	philosophers.append(Process(target=philosophize, args=(x, False)))
	philosophers[x].start()

