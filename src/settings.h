/*
/ Program: ann
/ File: settings.h
/ Author: Andrew Holman
/ Assignment: 2
/ Class/Instructor: CS 402/ Jianna Zhang
/ Last Date Modified: November 9, 2017
/
/ Description: Header file for settings namespace
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
namespace settings {
	extern int layer_sizes[];
	extern int layer_count;
	extern int data_m_number;
	extern int label_m_number;
	extern double learning_rate;
	extern int min_epochs;
	extern double mean_squared_error_threshold;

	extern std::string train_img_file;
	extern std::string train_lbl_file;
	extern std::string test_img_file;
	extern std::string test_lbl_file;
	extern std::string weight_bias_out_file;
}

#endif
