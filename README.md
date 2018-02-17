# Program Description
This program represents a neural network specialized in identifying hand written numerical digits. The program opens and parses a data file and accompanying expected value file, generates an initial random network, trains the network on the training data, then tests itself on a set of test data. This is a simple neural network that uses backpropagation learning with a sigmoid activation function.
This program is setup to specifically run with the included training and test data, other data may not be compatible even if it is of a similar format. Various network parameters can be changed in the settings.cpp file. Any changes to this file require that the program be recompiled for changes to take effect. This network is set up to specifically run with 784 input neurons and 10 output neurons in order to work with the provided data set. The network should have at least one hidden layer.
A more in-depth report on this program including references can be found in the file:
	report.txt

## How to compile
You must first change directories to 'src' in order to compile the program.
To compile the program, simply use the included makefile and execute the command:

	make

## Program execution
You must first change directories to 'src' in order to execute the program.
To run the program, execute the command:

	./ann
The program will train until the mean squared error drops below the threshold specified in settings.cpp then will test itself on the test data.

## Program output
The program will display network initialization information to standard output upon startup.
Upon the completion of each training epoch, training accuracy, mean squared error, and CPU runtime are displayed.
When the network has completed training, it prints the total number of epochs as well as the total CPU training time.
The network then tests itself using the test data and prints its accuracy. A sample of this output sequence can be found under:

	out/OUTPUT_FILE
Every 20 epochs, the program will create a new file under the 'out' directory labeled with that epoch number, containing a snapshot of the network's weights and biases at that moment in time. Each time the network is trained, these files are overwritten. Check the 'out' directory to see some example output.
