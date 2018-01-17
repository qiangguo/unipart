#ifndef __NEURON_H__
#define __NEURON_H__

#include <cstddef>
#include <vector>
#include <memory>
#ifndef __DEFINE_H__
#include "define.h"
#endif
#include "weight.h"
#include "act_func.h"


class Weight;

class Neuron {
public:
    Neuron(size_t id, NeuronType nt) : m_id {id},
			                           m_type {nt},
				                       m_val{nt==NeuronType::Bias ? 1.0 : 0.0} {};
    ~Neuron() {};

	// A neuron is defined with two containers used to accommodate
	// input weights and output weights.
	std::vector<std::shared_ptr<Weight>> m_input_weights;
	std::vector<std::shared_ptr<Weight>> m_output_weights;

	size_t getID(void) const;
	NeuronType getType(void) const { return m_type; };
	
	double getValue(void) const;
	double getDerivateValue(void) const;
	double getExpectedValue(void) const;
	double getError(void);
	
	void setValue(double value);
	void setExpectedValue(double value);
	
   	void feedForward(void);

private:
	// Disable default constructor!
	Neuron() {};
    size_t  m_id;
	NeuronType m_type;
	double m_val = 0.0;
	double m_derivate_val = 0.0;
	double m_expected_val = 0.0;
	
	
    //friend std::ostream & operator <<(const std::ostream &out, const Neuron &Neuron) {};
	//friend std::istream & operator >>(const std::istream &in) {};
};




#endif
