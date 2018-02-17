/*
/ Program: ann
/ File: settings.cpp
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 12, 2017
/
/ Description: cpp file for settings namespace. Used to specify various network parameters and settings.
*/

#include "settings.h"

namespace settings {
	int layer_sizes[] = {784, 100, 10};
	int layer_count = sizeof(layer_sizes)/sizeof(*layer_sizes);
	int data_m_number = 0x00000803;
	int label_m_number = 0x00000801;
	double learning_rate = 0.01;
	int min_epochs = 60;
	double mean_squared_error_threshold = 0.015;

	std::string train_img_file = "../data/train/train-images-idx3-ubyte";
	std::string train_lbl_file = "../data/train/train-labels-idx1-ubyte";
	std::string test_img_file = "../data/test/t10k-images-idx3-ubyte";
	std::string test_lbl_file = "../data/test/t10k-labels-idx1-ubyte";
	std::string weight_bias_out_file = "../out/weights-biases-epoch";
}
