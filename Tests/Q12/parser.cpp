#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <regex>


std::string ascii_to_digit_str(std::string str);
long eval_expr(std::string expr);

int main() {
	std::vector<std::string> data;
	std::string expr = "";
	std::ifstream myfile("content.txt");

	if (myfile.is_open()) {
		std::string reading;
		while (getline(myfile, reading)) {
			std::istringstream iss(reading);
			std::copy(std::istream_iterator<std::string>(iss),
					  std::istream_iterator<std::string>(),
					  std::back_inserter(data));
                      // std::ostream_iterator<std::string>(std::cout, "\n"));
		}
	} else {
		std::cout << "Cannot open the file!" << std::endl;
	}

   	for (auto& v : data) {
		v = ascii_to_digit_str(v);
	}

	for (const auto& v : data) {
		auto x = v.find('*');
		if (v.find('*') != std::string::npos) {
			//std::cout << x << std::endl;
			expr += v;
		} else if (v.find('-') != std::string::npos){
			expr += v;
		} else {
			expr += v + " + ";
		}
	}

	// If the last character in the original file is '.', the transformed
	// string will be suffixed with "* ". To make the arithmetic evaluation
	// pass, we need to include "1" to the end to perform * 1.
	if (expr.at(expr.size()-2) == '*') {
		expr += "1";
	}

	std::cout << "Parsed expression is:\n" << expr << "\n" << std::endl;
	
	// Now expr contains a string of converted ascii values with + - *.
	// to evaluate the arithmetic express, one can make use of some open
	// source. A recommended app can be downloaded from
	// http://www.partow.net/programming/exprtk/index.html
	long result;
	result = eval_expr(expr);

	std::cout << result << std::endl;
	
	return EXIT_SUCCESS;
}


long eval_expr(std::string expr) {
	long expected_val = 0;
	// call open source APIs.
	return expected_val;
}

/**
 * Convert a string into a ascii value string. Given 'a' to 'z', it is converted to
 * 0-25 and 'A' to 'Z', 1 - 26. ',' is converted to '-' while '.' to '*'
 */
std::string ascii_to_digit_str(std::string str) {
	std::string tmp = "";
	//std::cout << (int)'a' << " " << (int)'z' << " " << (int)'A' << " " << (int)'Z' << std::endl;
	for (size_t i=0; i<str.size(); i++) {
		int ascii_val = static_cast<int> (str.at(i));
		if (ascii_val>=65 && ascii_val<=90) {
			ascii_val = ascii_val - 65 + 1;
			tmp += std::to_string(ascii_val);
		} else if (ascii_val>=97 && ascii_val<=122) {
			ascii_val -= 97;
			tmp += std::to_string(ascii_val);
		} else if (str.at(i) == ','){
			tmp += " - ";
			break;
		} else {
			tmp += " * ";
			break;
		}
	}
	return tmp;
}
