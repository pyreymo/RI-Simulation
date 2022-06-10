#pragma once
#include "Box.h"
#include "Simulation.h"
#include <Eigen/Dense>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;
using array2 = Eigen::Array2d;

class Force : public Simulation {
public:
    vector<vec2> CellCoord_2d;
    vector<int> ParticleCell;
    vector<int> HeadList;
    vector<int> LinkedList;
    void update_2d(vector<vec2> x, vector<vec2>& f, Box box);
    Force(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
};
