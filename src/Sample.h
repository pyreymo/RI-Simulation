#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <Eigen/Dense>
#include "Simulation.h"

using namespace std;
using vec2 = Eigen::Vector2d;

class Sample : protected Simulation
{
public:
	double msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params);
	Sample(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5);
};
