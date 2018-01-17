#include "weight.h"
#include <iostream>

/**
    
 **/
double Weight::getValue(void) const {
	return m_val;
}

/**
    
 **/
void Weight::setValue(double val) {
	m_val = val;
}


/**

 **/
std::shared_ptr<Neuron> Weight::getInputNeuron(void) const {
	return m_input_neuron;
}


/**

 **/
std::shared_ptr<Neuron> Weight::getOutputNeuron(void) const {
	return m_output_neuron;
}


/**
   Eta: Learning rate. Delta: Momentum

 **/
void Weight::updateWeight(double eta, double delta) {
	if (m_input_neuron->getType() == NeuronType::Bias) {
		m_update_val = m_val;
		return;
	}
	
	double gradient;
	
	if (m_output_neuron->getType() == NeuronType::Output) {
		// To calculate weight updates between hidden layer and output layer:
		// gradient = -1 * (target_output - output) *  -> Partial differential against Error
		//             output * (1 - output) *         -> Partial differential against activate function
		//                                                Sigma function => f(x)(1-f(x))
		//             m_input_neuron_output           -> Partial differential against weight w_i
		//                                                output_neuron_input = sum(w_i * i_input_neuron_output)
		gradient = -1.0 * (m_output_neuron->getExpectedValue() - m_output_neuron->getValue()) *
			m_output_neuron->getDerivateValue() * m_input_neuron->getValue();
		m_update_val = m_val - eta*gradient;
	} else {
		// To calculate weight updates between input layer and hidden layer
		double sumVal = 0.0;
		for (auto &p : m_output_neuron->m_output_weights) {
			if (p->getInputNeuron()->getType() == NeuronType::Bias)
				continue;
			sumVal += -1.0 * (p->getOutputNeuron()->getExpectedValue() - p->getOutputNeuron()->getValue()) *
			       	   p->getOutputNeuron()->getDerivateValue() *
				       p->getValue();
		}
		
		gradient = sumVal * m_output_neuron->getDerivateValue() * m_input_neuron->getValue();

		m_update_val = m_val - eta * gradient;
	}
}


/**

 **/
void Weight::updateValue(void) {
	m_val = m_update_val;
}
