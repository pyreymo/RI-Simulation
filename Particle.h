#pragma once
#include "Box.h"
#include "Force.h"
#include "Simulation.h"
#include <Eigen/Dense>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;

class Particle : protected Simulation {
private:
    double crand();
    double Q = 1.;

public:
    void rescale_2d(vector<vec2>& v);
    void init_2d(vector<vec2>& x0, vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Box box);
    void update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Force force, Box box, double& totalV2);
    Particle(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
};
