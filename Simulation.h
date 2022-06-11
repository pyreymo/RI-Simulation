#pragma once
#include <Eigen/Dense>

class MolecularDynamics {
public:
    void simulation();
    MolecularDynamics(int n_plies, int n_length, double temperature, double dt, int n_iteration, int log_every, double cutoff_distance, double density_param);

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
    double S = pow(2, 1 / 6.);
    double GAP;
};
