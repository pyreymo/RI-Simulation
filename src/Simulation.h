#include <Eigen/Dense>

class Simulation
{
public:
	int PLY = 0;
	int LEN = 0;
	int N = 0;
	int ITER_NUM = 0;
	int RESCALE = 0;
	int LOG_STEP = 0;
	double TEMP = 0.0;
	double TIME_STEP = 0.0;
	double HALF_DT = 0.0;
	double CUTOFF = 0.0;
	double CUTOFF_2 = 0.0;
	double BOX_X = 0.0;
	double BOX_Y = 0.0;
	double BOX_HALF_Y = 0.0;
	double BT_TAU = 0.0;
	const double S = pow(2, 1 / 6.);
	Simulation(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance);
	void start();
};
