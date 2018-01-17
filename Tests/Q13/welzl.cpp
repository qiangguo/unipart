#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
using namespace std;

const int MAX_POINTS = 20;
int windowWidth=500;
int windowHeight=500;
float x[MAX_POINTS], y[MAX_POINTS];
int numPts = 0;

/**
 *
 */
struct Sphere {
	float xc, yc, radius;
};


/**
 *
 */
Sphere* sphere1pt(int pt1) {
	Sphere* spr = new Sphere;
	spr->xc = x[pt1];
	spr->yc = y[pt1];
	spr->radius = 0.0;
	return spr;
}

/**
 *
 */
Sphere* sphere2pts(int pt1, int pt2) {
	Sphere* spr = new Sphere;
	float xd, yd, dist;
	spr->xc = (x[pt1]+x[pt2])*0.5;
	spr->yc = (y[pt1]+y[pt2])*0.5;
	xd = x[pt1]-x[pt2];
	yd = y[pt1]-y[pt2];
	dist = sqrt(xd*xd + yd*yd);
	spr->radius = dist*0.5;
	return spr;
}

/**
 *
 */
Sphere* sphere3pts(int pt1, int pt2, int pt3) {
	Sphere* spr = new Sphere;
	float xd, yd, side_a, side_b, side_c, s;
	float term1, term2, term3, denom;
	xd = x[pt1]-x[pt2];
	yd = y[pt1]-y[pt2];
	side_a = sqrt(xd*xd + yd*yd);
	xd = x[pt2]-x[pt3];
	yd = y[pt2]-y[pt3];
	side_b = sqrt(xd*xd + yd*yd);
	xd = x[pt3]-x[pt1];
	yd = y[pt3]-y[pt1];
	side_c = sqrt(xd*xd + yd*yd);
	s = (side_a + side_b + side_c)*0.5;
	denom = sqrt(s*(s - side_a)*(s - side_b)*(s - side_c)); 
	spr->radius = side_a * side_b * side_c * 0.25 / denom;
	term1 = x[pt1]*x[pt1] + y[pt1]*y[pt1];
	term2 = x[pt2]*x[pt2] + y[pt2]*y[pt2];
	term3 = x[pt3]*x[pt3] + y[pt3]*y[pt3];
	denom = 2.0*(x[pt1]*(y[pt2]-y[pt3]) + 
		x[pt2]*(y[pt3]-y[pt1]) + x[pt3]*(y[pt1]-y[pt2])); 
	spr->xc = (term1*(y[pt2]-y[pt3]) + term2*(y[pt3]-y[pt1]) +
		term3*(y[pt1]-y[pt2]))/denom;
	spr->yc = (term1*(x[pt3]-x[pt2]) + term2*(x[pt1]-x[pt3]) +
		term3*(x[pt2]-x[pt1]))/denom;
	return spr;
}


/**
 *
 */
Sphere* minSphere(int pt[], int np, int bnd[], int nb) {
	Sphere* spr;
	float xd, yd, rad2, dist2;
	if(np == 1)	{
		if(nb == 0) return sphere1pt(pt[0]);
		if(nb == 1) return sphere2pts(pt[0], bnd[0]);
	}
	else if(np == 0) {
		if(nb == 1) return sphere1pt(bnd[0]);
		if(nb == 2) return sphere2pts(bnd[0], bnd[1]);
	}
	if (nb == 3)
		return sphere3pts(bnd[0], bnd[1], bnd[2]);
	spr = minSphere(pt, np-1, bnd, nb);
	xd = x[pt[np-1]]-(spr->xc);
	yd = y[pt[np-1]]-(spr->yc);
	dist2 = xd*xd + yd*yd;
	rad2 = (spr->radius)*(spr->radius);
	if(dist2 < rad2) return spr;
	bnd[nb] = pt[np-1];
	nb++;
	return minSphere(pt, np-1, bnd, nb);
}

/**
 *
 */
void display(void) {
	Sphere* sph;
	int pt[20], bnd[20];
	float xp, yp, angle;
	float toRad = M_PI/180.0;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	    for(int i = 0; i < numPts; i++) glVertex2f(x[i], y[i]);
	glEnd();

	if(numPts > 1) {
		for(int i = 0; i < 20; i++) {
			pt[i] = i;
			bnd[i] = 0;
		}
		sph = minSphere(pt, numPts, bnd, 0);
		if((sph->radius) > 0.1) {
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_LINE_STRIP);
			for(int i = 0; i <= 360; i++) {
				angle = i * toRad;
				xp = (sph->xc) + (sph->radius)*cos(angle);
				yp = (sph->yc) + (sph->radius)*sin(angle);
				glVertex2f(xp, yp);
			}
			glEnd();
		}
		delete sph;
	}
	glFlush(); 
} 


/**
 *
 */
void keyboard(unsigned char key, int x, int y) {
    if(key == 'c' || key == 'C') numPts = 0;
    glutPostRedisplay();
}


/**
 *
 */
void mouse(int button, int state, int xp, int yp) {
	if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN && numPts < 20) {
	    float xWorld = (float)(xp*10.0)/windowWidth;
	    float yWorld = (float)(windowHeight-yp)*10.0/windowHeight;
		x[numPts] = xWorld;
		y[numPts] = yWorld;
		numPts++;
		glutPostRedisplay();
	}
}


/**
 *
 */
void initialize(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 10.0, 0.0, 10.0);
}

/**
 *
 */
void reshape(int wid, int hgt) {
	windowWidth = wid;
	windowHeight = hgt;
	glViewport(0, 0, wid, hgt);
}

/**
 *
 */
int main(int argc, char **argv) {
	glutInit(&argc, argv);      
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Welzl's Algorithm");
	initialize();
	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
    return 0;
}
