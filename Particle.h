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

class Particle : protected MolecularDynamics {
private:
    double crand();
    double Q = 1.;

public:
    void rescale(vector<vec2>& v);
    void init(vector<vec2>& x0, vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Box& box);
    void update(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Force& force, Box& box, double& totalV2);
    Particle(MolecularDynamics& md)
        : MolecularDynamics(md) {};
};
