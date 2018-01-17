#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <memory>
#include "neuron.h"

class Neuron;

class Weight {
public:
Weight(double val,
	   std::shared_ptr<Neuron> i_ptr,
	   std::shared_ptr<Neuron> o_ptr) :
	              m_val {val},
			      m_input_neuron {i_ptr},
				  m_output_neuron {o_ptr} {};
	~Weight() {};
	
	double getValue(void) const;
	void setValue(double val);

	double getUpdateValue() { return m_update_val; };
	
	std::shared_ptr<Neuron> getInputNeuron(void) const;
	std::shared_ptr<Neuron> getOutputNeuron(void) const;

	void updateWeight(double eta, double delta);
	void updateValue(void);
	
private:
	// Disable default constructor
	Weight() {};
	double m_val;
	double m_update_val = 0.0;
	double m_delta_val = 0.0;

	std::shared_ptr<Neuron> m_input_neuron;
	std::shared_ptr<Neuron> m_output_neuron;
};

#endif
