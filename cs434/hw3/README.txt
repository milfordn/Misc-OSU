General:
Expected folder structure:
project
|-------src (Run python scripts from here)
|	|-------q1.py
|	|-------q2.py
|	|-------q3.py
|	|-------q4.py
|	|-------nn.py
|	|-------graphs
|		|-------(matplotlib graphs)
|
|-------cifar-10-batches.py
|	|-------(data batches)
|
|-------bin
|	|-------activate.csh
|
|-------include
|-------lib
|-------etc

Question 1:
To test many different learning rates: python q1.py
To test a single learning rate: python q1.py [lr]

Question 2:
To test many different learning rates: python q2.py
To test a single learning rate: python q2.py [lr]

Question 3:
To scan over all parameters and print results: python q3.py
To set all parameters and test those: pythno q3.py [dropout] [momentum] [weight decay]

Question 4:
To run both network structures with a given learning rate: python q4.py [lr]
