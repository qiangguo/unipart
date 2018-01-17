#include "act_func.h"
#include <iostream>
/**

 **/
double ActFunc::sigma(double x) {
	return 1 / (1 + std::exp((-1.0)*x));
}


/**

 **/
double ActFunc::sigma_deriv(double x) {
	return sigma(x) * (1 - sigma(x));
}
