/*
/ Program: ann
/ File: main.cpp
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 10, 2017
/
/ Description: Main file for ann program. This file is the entry point for the program.
*/

#include <iostream>

#include "settings.h"
#include "network.h"
#include "data_set.h"

int main(int argc, char **argv) {
	Network n(settings::layer_sizes, settings::layer_count);

	Data_Set training(settings::train_img_file, settings::train_lbl_file);
	Data_Set test(settings::test_img_file, settings::test_lbl_file);

	int **data = training.get_data();
	int *labels = training.get_labels();
	n.train(data, labels, 60000);

	int **test_data = test.get_data();
	int *test_labels = test.get_labels();
	n.test(test_data, test_labels, 10000);

	return 0;
}
