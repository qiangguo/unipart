#include <iostream>
#include <cmath>
#include <mpi.h>
#include <cassert>

double f(double x) {
	return x * x;
}

double integral(double a, double b, double h) {
	double sumVal = 0.0;
	while (true) {
		if ((b-a) > h) {
			sumVal += 0.5 * (f(a) + f(a+h)) * h;
			a += h;
		} else {
			sumVal += 0.5 * (f(a) + f(b)) * (b - a);
			break;
		}
	}
	return sumVal;
	
};

int main(int argc, char **argv) {
	int nproc;
	int my_rank;

	double a = -10.0;   // Left boundary
	double b = 10.0;    // Right boundary
	double h = 0.001;   // Step
	double interval;
	double my_result;
	double result = 0.0;
   
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	interval = (b - a) / ((double) nproc);
	double x = a + my_rank * interval;
	double y = x + interval;

	my_result = integral(x, y, h);

	if (my_rank == 0) {
		result = my_result;
		for (int i = 1; i < nproc; i++) {
			MPI_Recv(&my_result, 1, MPI_DOUBLE, i, 123, MPI_COMM_WORLD, &status);
			result += my_result;
		}
	} else {
		MPI_Send(&my_result, 1, MPI_DOUBLE, 0, 123, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();

	if (my_rank == 0) {
		// assert error tolerance
		assert(std::abs(result - 2000.0/3.0) < 0.01);
		std::cout << "\n------------------------------------------------------------" << std::endl;
		std::cout << " * Calculating integral from function f = x*x" << std::endl;
		std::cout << " * Integration range [-10, 10], step 0.01" << std::endl;
		std::cout << " * Running in " << nproc << " processes." << std::endl;
		std::cout << " * Result = " << result  << std::endl;
		std::cout << "------------------------------------------------------------\n" << std::endl;
	}
	return 0;
}
