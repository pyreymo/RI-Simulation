#pragma once
#include "Simulation.h"
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;

class Logline : protected Simulation {
public:
    void init_log_2d(string LOG_ADDR, vector<vec2> x, map<string, double> params);
    void print_double_params(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params);
    void print_density(string LOG_ADDR, int iter, vector<double> density);
    Logline(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
};
