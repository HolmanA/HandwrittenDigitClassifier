## Approach
My approach to this program was to create a neural network able to identify handwritten digits. To accomplish this task, I focused on a model that uses backpropagation with a sigmoid activation function in order to train the network's weights and balances, and to better approximate digit identification. The network topology consists of 3 layers; 784 neurons in the first layer, 100 in the second, and 10 in the output layer. Input images are 28x28 pixels, so each pixel value corresponds to one of the 784 input neurons. At the output layer, each of the 10 output neurons represents the likelihood that the image represents the corresponding digit. In order to obtain a numeric prediction from this output vector, the network uses the neuron with the highest value as the predicted image value.

## Reasoning
I settled with the above topology after trying a range of hidden layer counts and sizes. I found that one hidden layer containing 100 neurons offered the best compromise between speed, accuracy, and complexity. Similarly, a learning rate of 0.01 compliments this topology by allowing the network to make consistent steps towards its goal without reaching local minima. I set the mean squared error threshold at 0.015 because it is usually around this point that the network begins to plateau around 90% accuracy. By capping the network training algorithm here we can avoid long waits with no real payoff.

## References
Russell, Stuart J. (Stuart Jonathan), and Peter Norvig. Artificial intelligence a modern approach/ Stuart Russell ; Peter Norvig. Prentice Hall, 2003.

“THE MNIST DATABASE.” MNIST handwritten digit database, Yann LeCun, Corinna Cortes and Chris Burges, yann.lecun.com/exdb/mnist/

Nielsen, Michael A. “Neural Networks and Deep Learning.” Neural networks and deep learning, Determination Press, neuralnetworksanddeeplearning.com/chap1.html.

Cireşan, Dan Claudiu, et al. “Deep, Big, Simple Neural Nets for Handwritten Digit Recognition.” Neural Computation, vol. 22, no. 12, 2010, pp. 3207–3220., doi:10.1162/neco_a_00052.
