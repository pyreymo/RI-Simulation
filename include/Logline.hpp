#pragma once

#include "MolecularDynamics.hpp"
#include "Box.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Logline : protected MolecularDynamics
{
public:
    void init(const std::string &LOG_ADDR, const std::vector<vec2> &x, const std::map<std::string, double> &params);
    void print_params(const std::string &LOG_ADDR, int iter, const std::vector<vec2> &x, const std::map<std::string, double> &params);
    void print_density(const std::string &LOG_ADDR, int iter, const std::vector<double> &density);
    Logline(MolecularDynamics &md)
        : MolecularDynamics(md) {};
};
