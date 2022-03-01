#include <iostream>
#include <iomanip>
#include <ctime>
#include <map>
#include "Particle.h"
#include "Logline.h"
#include "Sample.h"
#include "Box.h"
#include "Force.h"
#include "Param.h"

using namespace std;

#ifdef TWO_DIMENSIONAL_SIMULATION
void simulation_2d() {
	clock_t start = clock(), tick;

	// Define simulation environment
	Particle particle;
	Force force;
	Box box(BOX_X, BOX_Y);
	Logline logline;
	Sample sample;

	vector<vec2> x0, x, v, f;
	double totalVelocitySquare;
	map<string, double> params;
	const string LOG_ADDR = "Output/2D_" + to_string(PLY) + "x" + to_string(LEN) + "_temp_" + to_string(TEMP)
		+ "_iter_" + to_string(ITER_NUM) + ".txt";

	particle.init_2d(x0, x, v, f, box);
	logline.init_log_2d(LOG_ADDR, x, params);

	cout << "Calc.\tProg.\tTemp." << setprecision(4) << endl;

	int iter = 0;
	while (++iter <= ITER_NUM)
	{
		// Update x, v, f every time step
		force.update_2d(x, f, box);
		particle.update_2d(x, v, f, force, box, totalVelocitySquare);

		// Rescale every RESCALE time steps
		if (iter % RESCALE == 0) { particle.rescale_2d(v); }

		// Output and sample parameters every LOG_STEP time steps
		if (iter % LOG_STEP == 0)
		{
			// Output the current calculation progress and status to the console
			tick = clock();
			cout << (double)(tick - start) / CLOCKS_PER_SEC << "s\t" << ((double)iter / ITER_NUM) * 100 << "%\t"
				<< totalVelocitySquare / (2. * (N - 1.)) << endl;
			start = tick;

			// Sample some parameters
			sample.msd_2d(x0, x, params);

			// Output the sampled parameters to a log file
			logline.print_log_2d(LOG_ADDR, iter, x, params);
		}
	}
};
#else
void simulation_3d() {
	clock_t start = clock(), tick;

	// Define simulation environment
	Particle particle;
	Force force;
	Box box(BOX_X, BOX_Y, BOX_Z);
	Logline logline;
	Sample sample;

	vector<vec3> x0, x, v, f;
	double totalVelocitySquare;
	map<string, double> params;
	const string LOG_ADDR = "Output/3D_" + to_string(PLY) + "x" + to_string(LEN) + "x" + to_string(LEN)
		+ "_temp_" + to_string(TEMP) + "_iter_" + to_string(ITER_NUM) + ".txt";

	particle.init_3d(x0, x, v, f, box);
	logline.init_log_3d(LOG_ADDR, x, params);

	cout << "Calc.\tProg.\tTemp." << setprecision(4) << endl;

	int iter = 0;
	while (++iter <= ITER_NUM)
	{
		// Update x, v, f every time step
		force.update_3d(x, f, box);
		particle.update_3d(x, v, f, force, box, totalVelocitySquare);

		// Rescale every 10 time steps
		if (iter % RESCALE == 0) { particle.rescale_3d(v); }

		// Output and sample parameters every LOG_STEP time steps
		if (iter % LOG_STEP == 0)
		{
			// Output the current calculation progress and status to the console
			tick = clock();
			cout << (double)(tick - start) / CLOCKS_PER_SEC << "s\t" << ((double)iter / ITER_NUM) * 100 << "%\t"
				<< totalVelocitySquare / (3. * (N - 1.)) << endl;
			start = tick;

			// Sample some parameters
			sample.msd_3d(x0, x, params);

			// Output the sampled parameters to a log file
			logline.print_log_3d(LOG_ADDR, iter, x, params);
		}
	}
};
#endif


int main() {
#ifdef TWO_DIMENSIONAL_SIMULATION
	simulation_2d();
#else
	simulation_3d();
#endif
	return 0;
}