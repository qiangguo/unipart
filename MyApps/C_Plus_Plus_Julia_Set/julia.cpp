/** This is a demonstrative program written to illustrate how Julia Set
	is generated. The result is printed using character "*". The program
	is NOT developed for any commercial purposes.
            Author: Dr. Qiang Guo
	    Email:  Qiang.Guo@cl.cam.ac.uk
 **/

#include <iostream>
#include <iomanip>
#include <complex>

using namespace std;

int main() {
	const int width {100}, height {100};
	size_t count {100};
	char image[width][height];
	complex<double> c {-0.7, 0.27015};

	for(int i {}; i < width; ++i) {
		for(int j {}; j < height; ++j) {
			auto re = 1.5*(i - width/2) / (0.5*width);
			auto im = (j - height/2) / (0.5*height);
			complex<double> z {re, im};
			image[i][j] = ' ';
			for(size_t k {}; k < count; ++k) {
				z = z*z + c;
            }
			if (std::abs(z) < 2.0)
				image[i][j] = '*';
        }
    }
	cout << "The Julia set looks like this: " << endl;
	for(size_t i {}; i< width; ++i) {
		for(size_t j {}; j < height; ++j)
			cout << image[i][j];
		cout << endl;
    }

	return 0;
}
