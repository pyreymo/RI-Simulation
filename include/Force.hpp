#pragma once

#include "MolecularDynamics.hpp"
#include "Box.hpp"
#include <vector>
#include <cuda_runtime.h>
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Force : protected MolecularDynamics
{
public:
    void update_2d_gpu(const std::vector<vec2> &x, std::vector<vec2> &f, Box &box);
    Force(MolecularDynamics &md)
        : MolecularDynamics(md) {};

private:
    // 设备指针在方法内部管理
};
