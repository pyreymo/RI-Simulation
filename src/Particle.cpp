#include "Particle.hpp"
#include "Box.hpp"
#include "Force.hpp"
#include <random>
#include <stdexcept>

void Particle::init(std::vector<vec2> &x0, std::vector<vec2> &x, std::vector<vec2> &v, std::vector<vec2> &f, double &zeta, Box &box)
{
    // 初始化粒子位置（x0 和 x）
    x0.resize(N);
    x.resize(N);
    v.resize(N, vec2(0.0, 0.0));
    f.resize(N, vec2(0.0, 0.0));

    // 使用均匀分布初始化位置，避免重叠
    double spacing = GAP * S;
    int particles_per_row = LEN;
    int particles_per_column = PLY;
    for (int i = 0; i < N; ++i)
    {
        int row = i % particles_per_row;
        int col = i / particles_per_row;
        x0[i] = vec2(row * spacing, col * spacing * sqrt(3.0) / 2.0);
        x[i] = x0[i];
    }

    // 初始化速度，根据温度分配
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<double> dist(0.0, sqrt(TEMP));

    double vx_sum = 0.0;
    double vy_sum = 0.0;
    for (int i = 0; i < N; ++i)
    {
        v[i].x() = dist(gen);
        v[i].y() = dist(gen);
        vx_sum += v[i].x();
        vy_sum += v[i].y();
    }

    // 取消整体动量
    double vx_avg = vx_sum / N;
    double vy_avg = vy_sum / N;
    for (int i = 0; i < N; ++i)
    {
        v[i].x() -= vx_avg;
        v[i].y() -= vy_avg;
    }

    // 初始化zeta
    zeta = 0.1; // 设定一个阻尼系数，根据需要调整
}

void Particle::update(std::vector<vec2> &x, std::vector<vec2> &v, const std::vector<vec2> &f, double &zeta, Force &force, Box &box, double &totalVelocitySquare)
{
    // 使用Verlet积分或其他积分方法更新位置和速度
    // 这里使用简单的显式Euler方法示例

    totalVelocitySquare = 0.0;
    for (int i = 0; i < N; ++i)
    {
        // 更新速度
        v[i] += (f[i] - zeta * v[i]) * TIME_STEP;

        // 更新位置
        x[i] += v[i] * TIME_STEP;

        // 应用周期性边界条件
        box.restrictPosition(x[i]);

        // 累加速度平方
        totalVelocitySquare += v[i].squaredNorm();
    }
}
