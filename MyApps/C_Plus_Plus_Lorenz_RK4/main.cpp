#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <algorithm>
#include <cstddef>
#include "rk4.h"

std::vector<double> lorenz(double, double, double);

std::vector<double> X {0.0};
std::vector<double> Y {1.0};
std::vector<double> Z {0.0};

const long MAX_EPOCH = 100000;

void display()  
{  
    glClearColor(0.0, 0.0, 0.0, 0.0);  
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(1.0, 1.0, 1.0);
	glOrtho(-5, 5, -5, 9, -1, 1);

	size_t Max = X.size() - 1;
	
	for (size_t index = 0; index < Max; index++) {
		glBegin(GL_LINES);
		{
			glVertex2d(X[index], Z[index]);
			glVertex2d(X[index+1], Z[index+1]);
		}
		glEnd();
	}

	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(-10, -20);
	
	char str[] = "Theta = 10, B = 3/8, R = 28";
	char *c;
	for (c=str; *c!=0; c++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
	}

	glFlush();
	
}

int main(int argc, char **argv) {
	// h = 0.001, x0 = 0.0, y0 = 1.0, z0 = 0.0
	RK4 rk4 = RK4 {0.001, 0.0, 1.0, 0.0};
	std::vector<double> xyz;

	for (int i = 0; i < MAX_EPOCH; i++) {
		xyz = rk4.getNextValues(&lorenz);
		X.push_back(xyz[0]);
		Y.push_back(xyz[1]);
		Z.push_back(xyz[2]);
	}

	
	// Start to produce OpenGL display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lorenz Chaos");
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}


/**

 **/
std::vector<double> lorenz(double x, double y, double z) {
	const double theta = 10.0;
	const double b = 8.0/3.0;
	const double r = 28.0;
	
	double dx, dy, dz;
	dx = -1.0 * theta * x + theta * y;
	dy = -1.0 * x * z + r * x - y;
	dz = x * y - b * z;
	std::vector<double> xyz {dx, dy, dz};
	return xyz;
}
