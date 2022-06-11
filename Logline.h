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

class Logline : protected MolecularDynamics {
public:
    void init(string LOG_ADDR, vector<vec2> x, map<string, double> params);
    void print_params(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params);
    void print_density(string LOG_ADDR, int iter, vector<double> density);
    Logline(MolecularDynamics& md)
        : MolecularDynamics(md) {};
};
