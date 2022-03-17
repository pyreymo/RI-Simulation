#include <vector>
#include <Eigen/Dense>
#include "Box.h"
#include "Simulation.h"

using namespace std;
using vec2 = Eigen::Vector2d;
using array2 = Eigen::Array2d;

class Force : protected Simulation
{
public:
	vector<vec2> CellCoord_2d;
	vector<int> ParticleCell;
	vector<int> HeadList;
	vector<int> LinkedList;
	void update_2d(vector<vec2> x, vector<vec2> &f, Box box);
	Force(int n_plies, int n_length, double temperature, double time_step = 1e-3, int n_iteration = 4e5, int temperature_rescale_span = 10, int logline_span = 100, double cutoff_distance = 5);
};
