/*
/ Program: ann
/ File: data_set.h
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 7, 2017
/
/ Description: Header file for dataset class
*/

#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
#include <fstream>

class Data_Set {
	public:
		Data_Set(std::string data_fname, std::string label_fname);
		int **get_data();
		int *get_labels();

	private:
		void parse_m_numbers();
		int parse_set_size();
		int parse_input_size();
		int endian_swap(int i);

		std::string data_filename, label_filename;
		std::ifstream data_stream, label_stream;
		int **data;
		int *labels;
};

#endif
