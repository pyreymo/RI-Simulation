#pragma once

#include "MolecularDynamics.hpp"
#include "Box.hpp"
#include <vector>
#include <map>
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Sample : protected MolecularDynamics
{
public:
    void density(const std::vector<vec2> &x, std::vector<double> &density);
    void msd(const std::vector<vec2> &x0, const std::vector<vec2> &x, std::map<std::string, double> &params);
    Sample(MolecularDynamics &md)
        : MolecularDynamics(md) {};
};
