#include "Sample.hpp"
#include "Box.hpp"
#include <cmath>

void Sample::density(const std::vector<vec2> &x, std::vector<double> &density)
{
    const int N_SPLIT = 10;
    double interval_y = BOX_Y / static_cast<double>(N_SPLIT);
    double interval_area = BOX_X * interval_y;

    density.assign(N_SPLIT, 0.0);
    for (size_t i = 0; i < N; i++)
    {
        int bin = static_cast<int>(x[i].y() / interval_y);
        if (bin < 0)
            bin = 0; // 防止负值
        else if (bin >= N_SPLIT)
            bin = N_SPLIT - 1; // 防止超出上限
        density[bin] += 1.0;
    }
    for (size_t i = 0; i < N_SPLIT; i++)
    {
        density[i] /= interval_area;
    }
}

void Sample::msd(const std::vector<vec2> &x0, const std::vector<vec2> &x, std::map<std::string, double> &params)
{
    // 计算均方位移（MSD）
    double msd = 0.0;
    for (int i = 0; i < N; ++i)
    {
        msd += (x0[i] - x[i]).squaredNorm();
    }
    msd /= static_cast<double>(N);
    params["msd"] = msd;
}
