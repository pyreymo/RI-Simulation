#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <map>
#include <Eigen/Dense>
#include "Simulation.h"

using namespace std;
using vec2 = Eigen::Vector2d;

class Logline : protected Simulation
{
public:
	void init_log_2d(string LOG_ADDR, vector<vec2> x, map<string, double> params);
	void print_log_2d(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params);
	Logline(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5);
};
