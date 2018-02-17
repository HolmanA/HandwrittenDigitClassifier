/*
/ Program: ann
/ File: network.h
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 10, 2017
/
/ Description: Header file for network class
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>

class Network {
	public:
		Network(int sizes[], int n);
		void print(std::string filename);
		std::vector<double> feed_forward(int *input, int input_size);
		void train(int **data, int *expected, int set_size);
		void test(int **data, int *expected, int set_size);

	private:
		double sigmoid(double z);
		double sigmoid_prime(double z);
		void initialize_network();
		int prediction(std::vector<double> v);
		void back_propagation(int expected);

		int layer_count;
		int *layer_sizes;
		double total_squared_error;
		int total_attempts;
		std::vector< std::vector< std::vector<double> > > weights;
		std::vector< std::vector<double> > biases;
		std::vector< std::vector<double> > activations;
		std::vector< std::vector<double> > inputs;
};

#endif
