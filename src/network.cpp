/*
/ Program: ann
/ File: network.cpp
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 11, 2017
/
/ Description: cpp file for network class. This class represents the neural network
/	using several multi-dimensional vectors to hold weights, biases, activations, and inputs.
/	The network uses backpropagation to learn to identify handwritten numeric digits.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <fstream>

#include "network.h"
#include "settings.h"

// Constructor
// sizes is an integer array, where each value corresponds to the number of neurons
// in that layer. n is the number of layers in the network, therefore n is the size of sizes.
Network::Network(int sizes[], int n) {
	layer_sizes = sizes;
	layer_count = n;
	initialize_network();
}

// Initializes network weights and biases
void Network::initialize_network() {
	// Display intial network information
	std::cout << "=============================================\n\n";
	std::cout << "Initializing Network...\n";
	std::cout << "	Layers: " << layer_count << "\n";
	std::cout << "	Layer Sizes:";
	for (int i = 0; i < layer_count; i++) {
		std::cout << " " << layer_sizes[i];
	}
	std::cout << "\n	Generating random weights in range [-1.00, 1.00]\n";
	std::cout << "	Setting biases to 0\n";
	std::cout << "	Learning rate: " << settings::learning_rate << "\n";

	srand(time(NULL));
	activations.resize(layer_count);
	activations[0].resize(layer_sizes[0]);
	weights.resize(layer_count - 1);
	biases.resize(layer_count - 1);
	inputs.resize(layer_count - 1);

	// Initialize network weights and biases
	for (int i = 0; i < weights.size(); i++) {
		weights[i].resize(layer_sizes[i]);
		biases[i].resize(layer_sizes[i + 1], 0); // initialize biases to 0
		inputs[i].resize(layer_sizes[i + 1], 0);
		for (int j = 0; j < weights[i].size(); j++) {
			weights[i][j].resize(layer_sizes[i + 1]);
			for (int k = 0; k < weights[i][j].size(); k++) {
				double w = (((double)(rand() % 201) - 100.0) / 100.0); // w between -1.00 and 1.00
				weights[i][j][k] = w;
			}
		}
	}
	std::cout << "\n=============================================\n";
}

// Feeds an input data set through the network and returns an output vector
std::vector<double> Network::feed_forward(int *input, int input_size) {
	if (input_size != layer_sizes[0]) {
		std::cerr << "Error: data input size does not match network input size\n";
		std::cerr << "Data input size: " << input_size << "\n";
		std::cerr << "Network input size: " << layer_sizes[0] << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}

	std::vector<double> in(input, input +  input_size);
	std::vector<double> out;

	for (int i = 1; i < layer_count; i++) {
		activations[i].resize(layer_sizes[i]);
		out.resize(layer_sizes[i]);
		for (int j = 0; j < layer_sizes[i]; j++) {
			out[j] = 0.0;
			for (int k = 0; k < layer_sizes[i - 1]; k++) {
				out[j] += in[k] * weights[i - 1][k][j];
			}
			inputs[i - 1][j] = out[j] - biases[i - 1][j];
			out[j] = sigmoid(inputs[i - 1][j]);
			activations[i][j] = out[j];
		}
		in = out;
	}
	return out;
}

// Calculates an integer value from a provided output vector
// The index of the highest value in the output vector is the value returned
int Network::prediction(std::vector<double> v) {
	int max_index = 0;
	double max_size = 0.0;

	for (int i = 0; i < v.size(); i++) {
		if (v[i] > max_size) {
			max_size = v[i];
			max_index = i;
		}
	}
	return max_index;
}

// Back propagation algorithm used to update network weights
void Network::back_propagation(int expected) {
	std::vector< std::vector<double> > deltas;
	deltas.resize(layer_count - 1);
	for (int i = 0; i < layer_count - 1; i++) {
		deltas[i].resize(layer_sizes[i + 1]);
	}
	// Compute deltas for output layer
	for (int i = 0; i < layer_sizes[layer_count - 1]; i++) {
		double result = activations[layer_count - 1][i];
		double err = 0 - result;
		if (i == expected) {
			err = 1 - result;
		}
		total_squared_error += (err * err);
		deltas[layer_count - 2][i] = sigmoid_prime(inputs[layer_count - 2][i]) * err;
	}
	// Compute deltas for hidden layers
	for (int i = layer_count - 2; i > 0; i--) {
		for (int j = 0; j < layer_sizes[i]; j++) {
			for (int k = 0; k < layer_sizes[i + 1]; k++) {
				deltas[i - 1][j] += sigmoid_prime(inputs[i - 1][j]) * deltas[i][k] * weights[i][j][k];
			}
		}
	}
	// Update weights
	for (int i = 0; i < weights.size(); i++) {
		for (int j = 0; j < weights[i].size(); j++) {
			for (int k = 0; k < weights[i][j].size(); k++) {
				weights[i][j][k] += settings::learning_rate * deltas[i][k] * activations[i][j];
			}
		}
		// Update biases
		for (int j = 0; j < biases[i].size(); j++) {
			biases[i][j] += settings::learning_rate * deltas[i][j];
		}
	}
}

// trains the network using the provided data and expected values with a backpropagation strategy
void Network::train(int **data, int *expected, int set_size) {
	int epochs_complete = 0;
	total_attempts = 0;
	total_squared_error = 0.0;
	std::cout << "=============================================\n";
	std::cout << "Training Network...\n";
	std::cout << "Weights and biases saved to " << settings::weight_bias_out_file << " every 20 epochs\n";
	std::clock_t train_cpu_start_time = std::clock();

	while (epochs_complete < settings::min_epochs || (total_squared_error / total_attempts) > settings::mean_squared_error_threshold) {
		std::clock_t epoch_cpu_start_time = std::clock();
		int correct = 0;
		int attempt = 0;

		// print weights and biases to file every 20 epochs
		if (epochs_complete % 20 == 0) {
			print(settings::weight_bias_out_file + std::to_string(epochs_complete) + ".out");
		}

		for (int h = 0; h < set_size; h++) {
			attempt++;

			// print dashes as network is trained
			if ((h % (int)(set_size / 45)) == 0) {
				std::cout << "-" << std::flush;
			}

			// total squared error is summed over each output node
			total_attempts += layer_sizes[layer_count - 1];

			// Initialize activations for input neurons
			for (int i = 0; i < layer_sizes[0]; i++) {
				activations[0][i] = data[h][i];
			}

			// Feed forward and get result vector; fills in activation values for all
			// other neurons
			std::vector<double> o = feed_forward(data[h], layer_sizes[0]);

			// Get numeric prediction from output vector
			int p = prediction(o);
			if (p == expected[h]) {
				correct++;
			} else {
				back_propagation(expected[h]);
			}
		}
		epochs_complete++;
		std::cout << "\nEnd of epoch " << epochs_complete << "\n";
		std::cout << "Accuracy: " << correct << "/" << attempt << "(" << ((double)correct / attempt) * 100 << "%)\n";
		std::cout << "Mean squared error: " << total_squared_error / total_attempts << "\n";
		std::cout << "CPU Time: " << (std::clock() - epoch_cpu_start_time) / (double)CLOCKS_PER_SEC << " seconds\n";
	}
	std::cout << "---------------------------------------------\n";
	std::cout << "\nTraining Complete...";
	std::cout << "Epochs: " << epochs_complete << "\n";
	std::cout << "Total CPU Time: " << (std::clock() - train_cpu_start_time) / (double)CLOCKS_PER_SEC << " seconds\n";
	std::cout << "=============================================\n";
}

// Tests the network's ability to accurately predict output
void Network::test(int **data, int *expected, int set_size) {
	std::cout << "=============================================\n";
	std::cout << "Testing Network...\n";
	int correct = 0;
	int attempt = 0;
	for (int i = 0; i < set_size; i++) {
		attempt++;
		if (prediction(feed_forward(data[i], layer_sizes[0])) == expected[i]) {
			correct++;
		}
	}
	std::cout << "Finished Testing\n";
	std::cout << "Accuracy: " << correct << "/" << attempt << "(" << ((double)correct / attempt) * 100 << "%)\n";
}

// Prints the network's current weights and biases to the specified file
void Network::print(std::string filename) {
	std::ofstream stream(filename, std::ios::trunc);
	if (stream.is_open()) {
		stream << "Network Weights:\n\n";
		for (int i = 0; i < weights.size(); i++) {
			stream << "Layer " << i << " to layer " << i + 1 << ":\n";
			for (int j = 0; j < weights[i].size(); j++) {
				stream << "Node " << j << ":\n";
				for (int k = 0; k < weights[i][j].size(); k++) {
					stream << weights[i][j][k] << " ";
				}
				stream << "\n\n";
			}
			stream << "\n\n";
		}

		stream << "\nNetwork Biases:\n\n";
		for (int i = 0; i < biases.size(); i++) {
			stream << "Layer " << i + 1 << ":\n";
			for (int j = 0; j < biases[i].size(); j++) {
				stream << "Node " << j << ": " << biases[i][j] <<  "\n";
			}
			stream << "\n\n";
		}
		stream.close();
	} else {
		std::cerr << "Error: Unable to open " << filename << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}
}

// Activation function for neurons
double Network::sigmoid(double z) {
	return (1.0 / (1.0 + exp(-z)));
}

// Derivative of sigmoid function
double Network::sigmoid_prime(double z) {
	return sigmoid(z) * (1 - sigmoid(z));
}
