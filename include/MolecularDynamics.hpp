#pragma once

#include <vector>
#include <map>
#include <Eigen/Dense>

using vec2 = Eigen::Vector2d;

class Particle;
class Force;
class Box;
class Logline;
class Sample;

class MolecularDynamics
{
public:
    MolecularDynamics(int n_plies, int n_length, double temperature, double dt, int n_iteration, int log_every, double cutoff_distance, double density_param);
    void simulation();

protected:
    int PLY;
    int LEN;
    int N;
    int ITER_NUM;
    int LOG_STEP;
    double TEMP;
    double TIME_STEP;
    double HALF_DT;
    double CUTOFF;
    double CUTOFF_2;
    double BOX_X;
    double BOX_Y;
    double BOX_HALF_Y;
    double S;
    double GAP;

    // 其他可能需要的成员变量
};
