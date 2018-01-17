#include <iostream>
#include <cstddef>
#include <string>
#include "define.h"
#include "nn.h"


std::string NeuronType2Str(NeuronType nt) {
	std::string mapping = "Unknown";
	switch(nt) {
	case NeuronType::Input:
		mapping = "Input";
		break;
	case NeuronType::Hidden:
		mapping = "Hidden";
		break;
	case NeuronType::Output:
		mapping = "Output";
		break;
	default:
		break;
	}

	return mapping;
};


/**

 **/
int main(int argc, char** argv) {
	NN nn = NN(2, 5, 1);

	std::vector<double> Is {0.0, 0.0,
			                0.0, 1.0,
			                1.0, 0.0,
			                1.0, 1.0};
	std::vector<double> Os {0.0, 0.0, 0.0, 1.0};
	
	nn.initialise();
	nn.startTraining(Is, Os);

	std::vector<double> test {0.0, 1.0};
	nn.setInputs(test);
	nn.feedForward_neurons();

	std::cout << "\nTesting ..." << std::endl;
	for (const auto &p : nn.m_output_neurons) {
		std::cout << "0.0 AND 1.0 = " << p->getValue() << std::endl;
	}
	
	
	return 0;
}
