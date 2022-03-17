#include "Sample.h"

double Sample::msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params)
{
	// Calculate for mean square displacement (MSD)
	double msd = 0.0;
	int N = x0.size();
	for (int i = 0; i < N; ++i)
	{
		msd += (x0[i] - x[i]).squaredNorm();
	}
	msd /= (double)N;
	params["msd"] = msd;
}


Sample::Sample(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance)
	: Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance)
{
}