#pragma once
#include <Eigen/Dense>

class Simulation {
public:
    int PLY;
    int LEN;
    int N;
    int ITER_NUM;
    int RESCALE;
    int LOG_STEP;
    double TEMP;
    double TIME_STEP;
    double HALF_DT;
    double CUTOFF;
    double CUTOFF_2;
    double BOX_X;
    double BOX_Y;
    double BOX_HALF_Y;
    double BT_TAU;
    double S;
    double GAP;
    Simulation(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap);
    void start();
};
