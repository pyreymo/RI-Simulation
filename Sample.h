#pragma once
#include "Simulation.h"
#include <Eigen/Dense>
#include <iostream>
#include <map>
#include <random>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;

class Sample : protected MolecularDynamics {
public:
    void density(vector<vec2> x, vector<double>& desity);
    void msd(vector<vec2> x0, vector<vec2> x, map<string, double>& params);
    Sample(MolecularDynamics& md)
        : MolecularDynamics(md) {};
};
