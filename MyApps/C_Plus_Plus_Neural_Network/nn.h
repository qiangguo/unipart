/** This is a demonstrative program written to illustrate how multi-layer
    Neural Network is created and trained. A logic AND function is used to
    train a NN with a structure of 2*5*1. The program is NOT developed for
    any commercial purposes.
            Author: Dr. Qiang Guo
	    Email:  Qiang.Guo@cl.cam.ac.uk
 **/

#ifndef __NN_H__
#define __NN_H__

#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>
#include <cassert>
#include "weight.h"
#include "neuron.h"


/**

 **/
class NN {
public:
    NN(size_t Is, size_t Hs, size_t Os) : m_input_nums{Is},
                                          m_hidden_nums {Hs},
                                          m_output_nums {Os} {};
	virtual ~NN() {};
	
	std::vector<std::shared_ptr<Neuron>> m_input_neurons;
	std::vector<std::shared_ptr<Neuron>> m_hidden_neurons;
	std::vector<std::shared_ptr<Neuron>> m_output_neurons;

	size_t getNumOfInputs(void) const { return m_input_nums; };
	size_t getNumOfHiddens(void) const { return m_hidden_nums; };
	size_t getNumOfOutputs(void) const { return m_output_nums; };

	// Input to Hidden layer and Hidden layer to ouptput 
	std::vector<std::shared_ptr<Weight>> m_i2h_weights;
	std::vector<std::shared_ptr<Weight>> m_h2o_weights;
	
	void initialise(void);

	double getLearningRate(void) const;
	void setLearningRate(double eta);
	double getMomentumRate(void) const;
	void setMomentumRate(double delta);
	size_t getTrainingEpoch(void) const;
	void setTrainingEpoch(size_t val);

	void setInputs(std::vector<double> Inputs);
	void setExpectedOutputs(std::vector<double> Outputs);
	void feedForward_neurons(void);	
	void updateWeights(void);
	void startTraining(std::vector<double>Inputs, std::vector<double>Outputs);
	double getTotalErrors(void);

private:
	NN() {};
	const size_t NEURON_ID_BASE = 1000000;
	size_t m_input_nums = 0;
	size_t m_hidden_nums = 0;
	size_t m_output_nums = 0;

	double m_eta = 0.5;     // learning rate
	double m_delta = 0.9;   // momentum rate
	size_t m_training_epoch = 1000;

	void print_info(void) const;
};

#endif
