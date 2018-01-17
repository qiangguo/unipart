/** This is a demonstrative program written to illustrate how Lorenz Chao
    Ordinal Differential Equation is solved using 4th order Runga Kuta method.
    The result is drawn in an OpenGL panel. The program	is NOT developed for
    any commercial purposes.
        Author: Dr. Qiang Guo
	Email:  Qiang.Guo@cl.cam.ac.uk
 **/

#include "rk4.h"

/**

 **/
std::vector<double> RK4::getNextValues(
	std::vector<double> (*pt2Func)(double, double, double)) {

	calcK1(pt2Func);
	calcK2(pt2Func);
	calcK3(pt2Func);
	calcK4(pt2Func);

	m_x = m_x + m_K1[0]/6.0 + m_K2[0]/3.0 + m_K3[0]/3.0 + m_K4[0]/6.0;
	m_y = m_y + m_K1[1]/6.0 + m_K2[1]/3.0 + m_K3[1]/3.0 + m_K4[1]/6.0;
	m_z = m_z + m_K1[2]/6.0 + m_K2[2]/3.0 + m_K3[2]/3.0 + m_K4[2]/6.0;
	
	return std::vector<double> {m_x, m_y, m_z};
}


/**

 **/
void RK4::calcK1(std::vector<double> (*pt2Func)(double, double, double)) {

	std::vector<double> xyz = (*pt2Func)(m_x, m_y, m_z);
	for (int index = 0; index < DIM; index ++) {
	    m_K1[index] = m_h * xyz[index];
	}
}

/**

 **/
void RK4::calcK2(std::vector<double> (*pt2Func)(double, double, double)) {
	
	std::vector<double> xyz = (*pt2Func)(m_x+0.5*m_K1[0], m_y+0.5*m_K1[1], m_z+0.5*m_K1[2]);
	for (size_t index = 0; index < DIM; index ++) {
	    m_K2[index] = m_h * xyz[index];
	}
}

/**

 **/
void RK4::calcK3(std::vector<double> (*pt2Func)(double, double, double)) {

	std::vector<double> xyz = (*pt2Func)(m_x+0.5*m_K2[0], m_y+0.5*m_K2[1], m_z+0.5*m_K2[2]);
	for (size_t index = 0; index < DIM; index ++) {
	    m_K3[index] = m_h * xyz[index];
	}
}

/**

 **/
void RK4::calcK4(std::vector<double> (*pt2Func)(double, double, double)) {

	std::vector<double> xyz = (*pt2Func)(m_x+m_K3[0], m_y+m_K3[1], m_z+m_K3[2]);
	for (size_t index = 0; index < DIM; index ++) {
	    m_K4[index] = m_h * xyz[index];
	}
}
