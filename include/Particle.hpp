#pragma once

#include "MolecularDynamics.hpp"
#include "Box.hpp"
#include "Force.hpp"
#include <vector>
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Particle : protected MolecularDynamics
{
public:
    void init(std::vector<vec2> &x0, std::vector<vec2> &x, std::vector<vec2> &v, std::vector<vec2> &f, double &zeta, Box &box);
    void update(std::vector<vec2> &x, std::vector<vec2> &v, const std::vector<vec2> &f, double &zeta, Force &force, Box &box, double &totalVelocitySquare);

    Particle(MolecularDynamics &md)
        : MolecularDynamics(md) {};

private:
    // 其他可能需要的私有成员
};
