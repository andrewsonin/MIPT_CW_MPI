#include <iostream>
#include <cmath>
#include <mpi.h>
#include <unistd.h>

double sin_by_log(double);

double integrate(double (*)(double), double, double, double);

double ksi_init(double);

int main(int argc, char* argv[]) {
	int myid, process_number;
	unsigned depth = atoi(argv[1]);

	int err = MPI_Init(&argc, &argv);
	if (err != 0) {
		std::cout << "Error occurred when initializing the MPI environment. Error code: " << err << std::endl;
		return err;
	}
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &process_number);

	unsigned sum_of_pids, pid = getpid();
	MPI_Reduce(&pid, &sum_of_pids, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);

	double step_and_diff[2];
	if (myid == 0) {
		step_and_diff[0] = (ksi_init(sum_of_pids / process_number) - 2) / process_number;
		step_and_diff[1] = step_and_diff[0] / depth;
	}
	MPI_Bcast(&step_and_diff, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double leftest_bound = 2 + step_and_diff[0] * myid;
	double result, addend = integrate(sin_by_log, leftest_bound, leftest_bound + step_and_diff[0], step_and_diff[1]);
	MPI_Reduce(&addend, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (myid == 0) std::cout << "Integral equals " << result << std::endl;
	MPI_Finalize();
	return 0;
}

double sin_by_log(double x) { return sin(x) / log(x); }

double integrate(double (*function)(double), double left_bound, double right_bound, double d) {
	double current_point = left_bound + d / 2;
	double result = 0;
	while (current_point < right_bound) {
		result += function(current_point);
		current_point += d;
	}
	return result * d;
}

double ksi_init(double q) {
	constexpr double denom = log(M_PI);
	return q / denom;
}
