#pragma once
#include "Simulation.h"
#include <Eigen/Dense>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;

class Sample : protected Simulation {
public:
    void density_2d(vector<vec2> x, vector<double>& desity);
    void msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params);
    Sample(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
};
