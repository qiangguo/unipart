#include <iostream>
#include <random>
#include "nn.h"
#include "define.h"

/**

 **/
void NN::print_info(void) const {
	std::cout << "\n\n--------------------------------------------" << std::endl;
	std::cout << "*  Neural Network Structure:  "
			  << m_input_nums << " x "
			  << m_hidden_nums << " x "
			  << m_output_nums << "    *" << std::endl;
	std::cout << "--------------------------------------------\n\n" << std::endl;
}

/**

 **/
void NN::initialise(void) {
	std::random_device rd;
	std::default_random_engine gen_value(rd());
	std::uniform_real_distribution<double> DIST {0.0, 1.0};


	// Create Input Layer
	for (size_t i = 0; i < m_input_nums; i++) {
		m_input_neurons.emplace_back(
			std::shared_ptr<Neuron> {new Neuron(NEURON_ID_BASE+i,
												NeuronType::Input)});
	}
	// Include a bias input
	m_input_neurons.emplace_back(
		std::shared_ptr<Neuron> {new Neuron(9999900,
											NeuronType::Bias)});

	// Create Hidden Layer
	for (size_t i = 0; i < m_hidden_nums; i++) {
		m_hidden_neurons.emplace_back(
			std::shared_ptr<Neuron> {new Neuron(NEURON_ID_BASE*2+i,
												NeuronType::Hidden)});
	}
	// Include a bias input
	m_hidden_neurons.emplace_back(
		std::shared_ptr<Neuron> {new Neuron(9999901,
											NeuronType::Bias)});
		
	// Create Output Layer
	for (size_t i = 0; i < m_output_nums; i++) {
		m_output_neurons.emplace_back(
			std::shared_ptr<Neuron> {new Neuron(NEURON_ID_BASE*3+i,
												NeuronType::Output)});
	}
	
	// Create weights between input and hidden neurons
	for (size_t i = 0; i < m_input_nums+1; i++) {		
		for (size_t j = 0; j < m_hidden_nums+1; j++){
			// If the hidden layer neuron is a bias, skip
			if (m_hidden_neurons[j]->getType() == NeuronType::Bias)
				continue;
			auto wt_ptr = std::shared_ptr<Weight> {
				new Weight(DIST(gen_value),
						   m_input_neurons[i],
						   m_hidden_neurons[j])};
			
			m_i2h_weights.push_back(wt_ptr);
			m_input_neurons[i]->m_output_weights.push_back(wt_ptr);
			m_hidden_neurons[j]->m_input_weights.push_back(wt_ptr);
		}
    }
 
	// Create weights between hidden and output neurons
	for (size_t i = 0; i < m_hidden_nums+1; i++) {		
		for (size_t j = 0; j < m_output_nums; j++){
			auto wt_ptr = 
				std::shared_ptr<Weight> {new Weight(DIST(gen_value),
													m_hidden_neurons[i],
													m_output_neurons[j])};
			m_h2o_weights.push_back(wt_ptr);
			m_hidden_neurons[i]->m_output_weights.push_back(wt_ptr);
			m_output_neurons[j]->m_input_weights.push_back(wt_ptr);
		}
    }
}

/**

 **/
double NN::getLearningRate(void) const {
	return m_eta;
}

/**

 **/
double NN::getMomentumRate(void) const {
	return m_delta;
}

/**

 **/
size_t NN::getTrainingEpoch(void) const {
	return m_training_epoch;
}


/**

 **/
void NN::setLearningRate(double eta) {
	m_eta = eta;
}

/**

 **/
void NN::setMomentumRate(double delta) {
	m_delta = delta;
}


/**

 **/
void NN::setTrainingEpoch(size_t val) {
	m_training_epoch = val;
}


/**

 **/
void NN::feedForward_neurons(void) {
	for (auto &n_ptr : m_hidden_neurons) {
		if (n_ptr->getType() == NeuronType::Bias)
			continue;
		n_ptr->feedForward();
	}

	for (auto &n_ptr : m_output_neurons) {
		n_ptr->feedForward();
	}
}

/**

 **/
void NN::setInputs(std::vector<double> Inputs) {
	assert(Inputs.size() == m_input_nums);
	for (size_t i = 0; i < m_input_nums; i++) {
		m_input_neurons[i]->setValue(Inputs[i]);
	}

}

/**

 **/
void NN::setExpectedOutputs(std::vector<double> Outputs) {
	assert(Outputs.size() == m_output_nums);
	for (size_t i = 0; i < m_output_nums; i++) {
		m_output_neurons[i]->setExpectedValue(Outputs[i]);
	}
}


/**

 **/
void NN::updateWeights(void) {
	//double outputDeltaSum = getOutputDeltaSum();
	
	for (auto &p : m_h2o_weights) {
		p->updateWeight(m_eta, m_delta);
	}
	
	for (auto &p : m_i2h_weights) {
		p->updateWeight(m_eta, m_delta);
	}
	
	// After all weights have completed their gradients'
	// calculations, update the weights' values.
	for (auto &p : m_h2o_weights) {
		p->updateValue();
	}
	
	for (auto &p : m_i2h_weights) {
		p->updateValue();
	}
}

/**

 **/
void NN::startTraining(std::vector<double>Inputs, std::vector<double>Outputs) {
	assert(m_input_nums > 0);
	assert(m_hidden_nums > 0);
	assert(m_output_nums > 0);
	assert(Inputs.size() >= m_input_nums);
	assert(Inputs.size() % m_input_nums == 0);
	assert(Outputs.size() % m_output_nums == 0);
	assert((int)(Inputs.size()/m_input_nums) == (int)(Outputs.size()/m_output_nums));

	std::vector<double> bi;
	std::vector<double> bo;
	
	for (size_t epoch = 0; epoch < m_training_epoch; epoch++) {
		auto pt_i = Inputs.begin();
		auto pt_o = Outputs.begin();

		while (pt_i != Inputs.end()) {
			std::copy(pt_i, pt_i+m_input_nums, std::back_inserter(bi));
			std::copy(pt_o, pt_o+m_output_nums, std::back_inserter(bo));
		
			setInputs(bi);
			setExpectedOutputs(bo);
			feedForward_neurons();
			updateWeights();

			pt_i += m_input_nums;
			pt_o += m_output_nums;
			
			bi.clear();
			bo.clear();
		}
		std::cout << "Epoch: " << epoch << "   Total Error: " << getTotalErrors() << std::endl;

	}
}


/**

 **/
double NN::getTotalErrors(void) {
	double sumTotal = 0.0;
	for (auto &p : m_output_neurons) {
		sumTotal += p->getError();
	}
	return sumTotal;
}
