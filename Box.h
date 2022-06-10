#pragma once
#include "Simulation.h"
#include <Eigen/Dense>

using namespace std;
using vec2 = Eigen::Vector2d;

class Box : public Simulation {
public:
    void restrictPositionPBC(vec2&);
    void restrictForcePBC(vec2&);
    Box(double xx, double yy, int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
};