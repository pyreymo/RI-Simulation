#include "Logline.hpp"
#include <fstream>
#include <iostream>

void Logline::init(const std::string &LOG_ADDR, const std::vector<vec2> &x, const std::map<std::string, double> &params)
{
    std::ofstream os;
    os.open(LOG_ADDR, std::ios_base::out);

    os << "# N\t" << N << std::endl;

    os << "# Radius\t" << sqrt(3.0) / 4.0 * PLY * GAP * S << std::endl;
    os << "# Length\t" << LEN * GAP * S << std::endl;

    os << "# Gap\t" << GAP << std::endl;
    os << "# PLY\t" << PLY << std::endl;
    os << "# LEN\t" << LEN << std::endl;
    os << "# BOX_X\t" << BOX_X << std::endl;
    os << "# BOX_Y\t" << BOX_Y << std::endl;

    os << "# Temp\t" << TEMP << std::endl;
    os << "# TimeStep\t" << TIME_STEP << std::endl;
    os << "# IterNum\t" << ITER_NUM << std::endl;
    os << "# Cutoff\t" << CUTOFF << std::endl;
    os << "# LogStep\t" << LOG_STEP << std::endl;

    os.close();

    print_params(LOG_ADDR, 1, x, params);
}

void Logline::print_params(const std::string &LOG_ADDR, int iter, const std::vector<vec2> &x, const std::map<std::string, double> &params)
{
    std::ofstream os;
    os.open(LOG_ADDR, std::ios_base::app);
    os << "Iter " << iter << std::endl;
    for (size_t i = 0; i < N; i++)
    {
        os << i << "," << x[i].x() << "," << x[i].y() << std::endl;
    }
    for (const auto &m : params)
    {
        os << "@ \t" << m.first << "\t" << m.second << std::endl;
    }
    os.close();
}

void Logline::print_density(const std::string &LOG_ADDR, int iter, const std::vector<double> &density)
{
    std::ofstream os;
    os.open(LOG_ADDR, std::ios_base::app);
    os << "Iter " << iter << std::endl;
    os << "@DEN";
    for (const double &d : density)
    {
        os << "\t" << d;
    }
    os << std::endl;
    os.close();
}
