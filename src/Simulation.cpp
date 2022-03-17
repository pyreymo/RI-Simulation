#include <iomanip>
#include <ctime>
#include "Simulation.h"
#include "Box.h"
#include "Force.h"
#include "Particle.h"
#include "Logline.h"
#include "Sample.h"

Simulation::Simulation(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5)
	: PLY(n_plies), LEN(n_length), TEMP(temperature), TIME_STEP(time_step), ITER_NUM(n_iteration), RESCALE(temperature_rescale_span), LOG_STEP(logline_span)
{
	CUTOFF     = cutoff_distance * S;
	CUTOFF_2   = CUTOFF * CUTOFF;
	BOX_X      = (LEN + 0.5) * S;
	BOX_Y      = sqrt(3) * (40. + PLY) * S;
	BOX_HALF_Y = BOX_Y / 2.0;
	BT_TAU     = 1.0;
	N          = (2 * PLY + 1) * LEN;
	HALF_DT    = TIME_STEP / 2.0;
};

void Simulation::start()
{
	clock_t start = clock(), tick;

	Particle particle(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF);
	Force    force(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF);
	Box      box(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF);
	Logline  logline(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF);
	Sample sample(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF);

	vector<vec2> x0, x, v, f;
	double totalVelocitySquare;
	map<string, double> params;
	const string LOG_ADDR = "Output/2D_" + to_string(PLY) + "x" + to_string(LEN) + "_temp_" + to_string(TEMP) + "_iter_" + to_string(ITER_NUM) + ".txt";

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
	    if (iter % RESCALE == 0)
	    {
	        particle.rescale_2d(v);
	    }

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