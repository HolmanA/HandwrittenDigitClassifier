/*
/ Program: ann
/ File: data_set.cpp
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 7, 2017
/
/ Description: cpp file for dataset class. This class is responsible for
/	parsing and preprocessing image pixel data and expected values from the
/	specified files.
*/

#include <iostream>
#include <cstdlib>

#include "data_set.h"
#include "settings.h"

// Opens data and label files, validates and parses their data
Data_Set::Data_Set(std::string data_fname, std::string label_fname) {
	data_filename = data_fname;
	label_filename = label_fname;

	std::cout << "=============================================\n\n";
	std::cout << "Loading data from " << data_filename << "\n";
	data_stream.open(data_filename.c_str(), std::ios::in | std::ios::binary);
	if (!data_stream.is_open()) {
		std::cerr << "Error: Unable to open " << data_filename << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}

	std::cout << "Loading labels from " << label_filename << "\n";
	label_stream.open(label_filename.c_str(), std::ios::in | std::ios::binary);
	if (!label_stream.is_open()) {
		std::cerr << "Error: Unable to open " << label_filename << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}

	parse_m_numbers();
	int set_size = parse_set_size();
	int input_size = parse_input_size();

	int d = 0;
	int l = 0;
	data = new int*[set_size];
	labels = new int[set_size];

	// Read data and label values from files
	for (int i = 0; i < set_size; i++) {
		data[i] = new int[input_size];
		// Data and label values are stored as big-endian characters
		label_stream.read((char*)&l, sizeof(char));
		labels[i] = l;

		for (int j = 0; j < input_size; j++) {
			data_stream.read((char*)&d, sizeof(char));
			data[i][j] = d;
		}
	}

	data_stream.close();
	label_stream.close();
	std::cout << "\n=============================================\n";
}

// parses data and label files for their magic numbers
// magic numbers must match those specified in settings.cpp or program will exit
void Data_Set::parse_m_numbers() {
	int d = 0;
	int l = 0;
	data_stream.read((char*)&d, sizeof(d));
	label_stream.read((char*)&l, sizeof(l));

	if (endian_swap(d) != settings::data_m_number) {
		std::cerr << "Error: This program is not configured for the format indicated by the magic number found in:\n";
		std::cerr << data_filename << "\n";
		std::cerr << "magic number(found) : " << endian_swap(d) << "\n";
		std::cerr << "magic number(expected) : " << settings::data_m_number << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}
	if (endian_swap(l) != settings::label_m_number) {
		std::cerr << "Error: This program is not configured for the format indicated by the magic number found in:\n";
		std::cerr << label_filename << "\n";
		std::cerr << "magic number(found) : " << endian_swap(l) << "\n";
		std::cerr << "magic number(expected) : " << settings::label_m_number << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}
}

// parses data and label files to obtain data set size
// data and label set sizes must match or program will exit
int Data_Set::parse_set_size() {
	int d = 0;
	int l = 0;
	data_stream.read((char*)&d, sizeof(d));
	label_stream.read((char*)&l, sizeof(l));
	if (d != l) {
		std::cerr << "Error: data and label set sizes dont match\n";
		std::cerr << "data set size : " << endian_swap(d) << "\n";
		std::cerr << "label set size : " << endian_swap(l) << "\n";
		std::cerr << "System exiting...\n";
		exit(1);
	}
	return endian_swap(d);
}

// parses data file to obtain size of input data sets byte
int Data_Set::parse_input_size() {
	int dims[2];
	data_stream.read((char*)&dims[0], sizeof(dims[0]));
	data_stream.read((char*)&dims[1], sizeof(dims[1]));
	return endian_swap(dims[0]) * endian_swap(dims[1]);
}

// swaps little/big endian encoding
int Data_Set::endian_swap(int i) {
	int byte1 = (i & 0x000000ff) << 24;
	int byte2 = (i & 0x0000ff00) << 8;
	int byte3 = (i & 0x00ff0000) >> 8;
	int byte4 = (i & 0xff000000) >> 24;

	return (byte1 + byte2 + byte3 + byte4);
}

// returns 2d array of data inputs
int **Data_Set::get_data() {
	return data;
}

// returns 1d array of expected outputs
int *Data_Set::get_labels() {
	return labels;
}
