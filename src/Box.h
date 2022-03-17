#include <Eigen/Dense>
#include "Simulation.h"

using namespace std;
using vec2 = Eigen::Vector2d;

class Box : protected Simulation
{
protected:
	double x, y, z;

public:
	void restrictPositionPBC(vec2&);
	void restrictForcePBC(vec2&);
	Box(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5);
};