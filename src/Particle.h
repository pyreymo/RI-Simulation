#include <iostream>
#include <vector>
#include <random>
#include <Eigen/Dense>
#include "Simulation.h"
#include "Box.h"
#include "Force.h"

using namespace std;
using vec2 = Eigen::Vector2d;

class Particle : protected Simulation
{
private:
	double crand();

public:
	void rescale_2d(vector<vec2>& v);
	void init_2d(vector<vec2>& x0, vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box);
	void update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2);
	Particle(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5);
};
