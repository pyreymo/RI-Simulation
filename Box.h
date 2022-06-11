#pragma once
#include "Simulation.h"
#include <Eigen/Dense>

using namespace std;
using vec2 = Eigen::Vector2d;

class Box : protected MolecularDynamics {
public:
    void restrictPosition(vec2&);
    void restrictForce(vec2&);
    Box(MolecularDynamics& md)
        : MolecularDynamics(md) {};
};