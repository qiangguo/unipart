#include "neuron.h"
#include <iostream>

/**

 **/
size_t Neuron::getID(void) const {
	return m_id;
}


/**

 **/
double Neuron::getValue(void) const {
	return m_val;
}

/**

 **/
double Neuron::getDerivateValue(void) const {
	return m_derivate_val;
}


/**

 **/
double Neuron::getExpectedValue(void) const {
	return m_expected_val;
}


/**

 **/
double Neuron::getError(void) {
	double delta = m_expected_val - m_val;
	return (delta * delta) / 2.0;
}

/**

 **/
void Neuron::setValue(double value) {
	m_val = value;
}


void Neuron::setExpectedValue(double value) {
	m_expected_val = value;
}

/**

 **/
void Neuron::feedForward(void) {
	double sumVal = 0.0;
	for (const auto &wt_ptr : m_input_weights) {
		double inputVal = wt_ptr->getInputNeuron()->getValue();
		double weightVal =  wt_ptr->getValue();
		sumVal += inputVal * weightVal;
	}
	m_val =  ActFunc::sigma(sumVal);
	m_derivate_val = ActFunc::sigma_deriv(sumVal);
}
