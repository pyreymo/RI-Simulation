#include "Logline.h"

void Logline::print_params(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params)
{
    ofstream os;
    os.open(LOG_ADDR, std::ios_base::app);
    os << "Iter " << iter << endl;
    for (size_t i = 0; i < N; i++) {
        os << i << "," << x[i].x() << "," << x[i].y() << endl;
    }
    for (auto& m : params) {
        os << "@ \t" << m.first << "\t" << m.second << endl;
    }
    os.close();
}

void Logline::print_density(string LOG_ADDR, int iter, vector<double> density)
{
    ofstream os;
    os.open(LOG_ADDR, std::ios_base::app);
    os << "Iter " << iter << endl;
    os << "@DEN";
    for (double& d : density) {
        os << "\t" << d;
    }
    os << endl;
    os.close();
}

void Logline::init(string LOG_ADDR, vector<vec2> x, map<string, double> params)
{
    ofstream os;
    os.open(LOG_ADDR, std::ios_base::out);

    os << "# N\t" << N << endl;

    os << "# Radius\t" << sqrt(3) / 4. * PLY * GAP * S << endl;
    os << "# Length\t" << LEN * GAP * S << endl;

    os << "# Gap\t" << GAP << endl;
    os << "# PLY\t" << PLY << endl;
    os << "# LEN\t" << LEN << endl;
    os << "# BOX_X\t" << BOX_X << endl;
    os << "# BOX_Y\t" << BOX_Y << endl;

    os << "# Temp\t" << TEMP << endl;
    os << "# TimeStep\t" << TIME_STEP << endl;
    os << "# IterNum\t" << ITER_NUM << endl;
    os << "# Cutoff\t" << CUTOFF << endl;
    os << "# LogStep\t" << LOG_STEP << endl;

    os.close();

    print_params(LOG_ADDR, 1, x, params);
}
