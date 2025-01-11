#include "MolecularDynamics.hpp"

int main(int argc, char *argv[])
{
    // 根据需要解析命令行参数或使用默认值
    // 这里使用默认参数示例
    int n_plies = 10;
    int n_length = 10;
    double temperature = 1.0;
    double dt = 0.001;
    int n_iteration = 1000;
    int log_every = 1;
    double cutoff_distance = 2.5;
    double density_param = 1.0;

    MolecularDynamics md(n_plies, n_length, temperature, dt, n_iteration, log_every, cutoff_distance, density_param);
    md.simulation();

    return 0;
}
