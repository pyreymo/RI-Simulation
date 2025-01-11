#pragma once

#include "MolecularDynamics.hpp"
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Box : protected MolecularDynamics
{
public:
    void restrictPosition(vec2 &pos);
    void restrictForce(vec2 &force);
    Box(MolecularDynamics &md)
        : MolecularDynamics(md) {};
};
