#include "Sample.h"

void Sample::density_2d(vector<vec2> x, vector<double>& density)
{
    const int N_SPLIT = 10;
    double interval_y = BOX_Y / (double)N_SPLIT;
    double interval_area = BOX_X * interval_y;

    density = vector<double>(N_SPLIT);
    for (size_t i = 0; i < N; i++) {
        density[x[i].y() / interval_y] += 1;
    }
    for (size_t i = 0; i < N_SPLIT; i++) {
        density[i] /= interval_area;
    }
}

void Sample::msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params)
{
    // Calculate for mean square displacement (MSD)
    double msd = 0.0;
    int N = x0.size();
    for (int i = 0; i < N; ++i) {
        msd += (x0[i] - x[i]).squaredNorm();
    }
    msd /= (double)N;
    params["msd"] = msd;
}

Sample::Sample(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap)
    : Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance, pairwise_gap)
{
}