#ifndef __ACT_FUNC_H__
#define __ACT_FUNC_H__

#include <cmath>

class ActFunc {
public:
    ActFunc() {};
	~ActFunc() {};
	static double sigma(double x) ;
	static double sigma_deriv(double x);

	
private:
	const double EXP = std::exp(1.0);
};

#endif
