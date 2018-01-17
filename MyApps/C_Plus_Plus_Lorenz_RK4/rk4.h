/** This is a demonstrative program written to illustrate how Lorenz Chao
    Ordinal Differential Equation is solved using 4th order Runga Kuta method.
    The result is drawn in an OpenGL panel. The program	is NOT developed for
    any commercial purposes.
        Author: Dr. Qiang Guo
	Email:  Qiang.Guo@cl.cam.ac.uk
 **/

#ifndef __RK4_H__
#define __RK4_H__

#include <vector>
#include <iostream>

const int DIM = 3;

class RK4 {
public:
    RK4(double h, double x0, double y0,	double z0):
	m_h {h}, m_x {x0}, m_y {y0}, m_z {z0} {};
	virtual ~RK4() {};
	std::vector<double> getNextValues(
		std::vector<double> (*pt2Func)(double, double, double));

private:
	RK4() {};
	
	double m_h;
	double m_x;
	double m_y;
	double m_z;

	std::vector<double> m_K1 = std::vector<double>(DIM, 0.0);
	std::vector<double> m_K2 = m_K1;
	std::vector<double> m_K3 = m_K1;
	std::vector<double> m_K4 = m_K1;
	
	void calcK1(std::vector<double> (*pt2Func)(double, double, double));
	void calcK2(std::vector<double> (*pt2Func)(double, double, double));
	void calcK3(std::vector<double> (*pt2Func)(double, double, double));
	void calcK4(std::vector<double> (*pt2Func)(double, double, double));

};

#endif
