#include "Particle.h"

void Particle::rescale_2d(vector<vec2>& v)
{
    double totalVelocitySquare = 0;
    vec2 totalVelocity(0, 0);
    for (vec2& vi : v) {
        totalVelocity += vi;
        totalVelocitySquare += vi.squaredNorm();
    }
    // double tempScaleFactor = sqrt((2. * TEMP) / (totalVelocitySquare / N));
    double tempScaleFactor = sqrt(1 + TIME_STEP / BT_TAU * ((2. * TEMP) / (totalVelocitySquare / N) - 1));
    for (vec2& vi : v) {
        vi = (vi - totalVelocity / ((double)N)) * tempScaleFactor;
    }
}

void Particle::init_2d(vector<vec2>& x0, vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Box box)
{
    v.resize(N);
    x.resize(N);
    f.resize(N);
    zeta = 0;

    for (vec2& vi : v) {
        vi = vec2(crand(), crand());
    }
    rescale_2d(v);

    // initialize FCC-2D
    int count = 0;
    for (int j = 0; j < PLY; j++) {
        for (int i = 0; i < LEN; i++) {
            x[count++] = vec2(
                (double)(i + (j % 2) / 2. + 0.5) * GAP * S,
                (j - (PLY - 1) / 2.) * sqrt(3) / 2. * GAP * S + box.BOX_HALF_Y);
        }
    }

    cout << count << '\t' << N << endl;

    x0 = x;
}

// 解粒子运动方程
void Particle::update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, double& zeta, Force force, Box box, double& totalV2)
{
    /*
    * B 方法
    totalV2 = 0;

    for (size_t i = 0; i < N; i++)
    {
            x[i] += TIME_STEP * v[i] + TIME_STEP * TIME_STEP * f[i] * 0.5;
            box.restrictPositionPBC(x[i]);
            v[i] += HALF_DT * f[i];
    }

    force.update_2d(x, f, box);

    for (size_t i = 0; i < N; i++)
    {
            v[i] += HALF_DT * f[i];
            totalV2 += v[i].squaredNorm();
    }

    */

    vector<vec2> half_v;
    half_v.assign(v.begin(), v.end());

    for (size_t i = 0; i < N; i++) {
        auto temp1 = HALF_DT * (f[i] - zeta * v[i]);
        x[i] += TIME_STEP * (v[i] + temp1);
        box.restrictPositionPBC(x[i]);
        half_v[i] += temp1;
    }

    force.update_2d(x, f, box);

    totalV2 = 0;
    double totalHalfV2 = 0;

    for (size_t i = 0; i < N; i++) {
        totalV2 += v[i].squaredNorm();
        totalHalfV2 += half_v[i].squaredNorm();
    }

    zeta += HALF_DT / Q * ((totalV2 + totalHalfV2) / 2. - (2 * N + 1) * TEMP);

    totalV2 = 0;
    for (size_t i = 0; i < N; i++) {
        v[i] = (half_v[i] + HALF_DT * f[i]) / (1. + HALF_DT * zeta);
        totalV2 += v[i].squaredNorm();
    }
}

double Particle::crand()
{
    return (rand() / double(RAND_MAX)) - 0.5;
}

Particle::Particle(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap)
    : Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance, pairwise_gap)
{
}
