#include "MolecularDynamics.hpp"
#include "Particle.hpp"
#include "Force.hpp"
#include "Box.hpp"
#include "Logline.hpp"
#include "Sample.hpp"
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <stdexcept>

// 构造函数实现
MolecularDynamics::MolecularDynamics(int n_plies, int n_length, double temperature, double dt, int n_iteration, int log_every, double cutoff_distance, double density_param)
    : PLY(n_plies), LEN(n_length), TEMP(temperature), TIME_STEP(dt), HALF_DT(dt / 2.0), ITER_NUM(n_iteration), LOG_STEP(log_every), S(pow(2.0, 1.0 / 6.0)), GAP(density_param)
{
    CUTOFF = cutoff_distance * S;
    CUTOFF_2 = CUTOFF * CUTOFF;
    BOX_X = LEN * GAP * S;
    BOX_Y = sqrt(3.0) / 2.0 * 3.0 * PLY * GAP * S;
    BOX_HALF_Y = BOX_Y / 2.0;
    N = PLY * LEN;
}

void MolecularDynamics::simulation()
{
    clock_t now = clock(), tick;

    Particle particle(*this);
    Force force(*this);
    Box box(*this);
    Logline logline(*this);
    Sample sample(*this);

    std::vector<vec2> x0, x, v, f;
    std::map<std::string, double> params;
    std::vector<double> density;
    double zeta;
    double totalVelocitySquare;

    const std::string curr_path = std::filesystem::current_path().generic_string();
    const std::string LOG_ADDR = curr_path + "/data/2D_" + std::to_string(PLY) + "x" + std::to_string(LEN) + "_temp_" + std::to_string(TEMP) + "_iter_" + std::to_string(ITER_NUM) + ".txt";

    // 初始化粒子
    particle.init(x0, x, v, f, zeta, box);
    // 初始化日志
    logline.init(LOG_ADDR, x, params);

    std::cout << "Calc.\tProg.\tTemp." << std::setprecision(4) << std::endl;

    int iter = 0;
    while (++iter <= ITER_NUM)
    {
        // 使用GPU更新力
        force.update_2d_gpu(x, f, box);
        // 更新粒子位置和速度
        particle.update(x, v, f, zeta, force, box, totalVelocitySquare);

        // 每LOG_STEP步记录一次
        if (iter % LOG_STEP == 0)
        {
            // 输出进度
            tick = clock();
            std::cout << static_cast<double>(tick - now) / CLOCKS_PER_SEC << "s\t"
                      << ((static_cast<double>(iter) / ITER_NUM) * 100) << "%\t"
                      << totalVelocitySquare / (2.0 * (N - 1)) << std::endl;
            now = tick;

            // 采样参数
            sample.msd(x0, x, params);
            sample.density(x, density);

            // 记录日志
            logline.print_params(LOG_ADDR, iter, x, params);
            logline.print_density(LOG_ADDR, iter, density);
        }
    }
}
