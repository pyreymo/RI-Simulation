#include "Simulation.h"
#include "Box.h"
#include "Force.h"
#include "Logline.h"
#include "Particle.h"
#include "Sample.h"
#include <ctime>
#include <filesystem>
#include <iomanip>

MolecularDynamics::MolecularDynamics(int n_plies, int n_length, double temperature, double dt, int n_iteration, int log_every, double cutoff_distance, double density_param)
    : PLY(n_plies)
    , LEN(n_length)
    , TEMP(temperature)
    , TIME_STEP(dt)
    , HALF_DT(dt / 2.0)
    , ITER_NUM(n_iteration)
    , LOG_STEP(log_every)
    , GAP(density_param)
{
    CUTOFF = cutoff_distance * S;
    CUTOFF_2 = CUTOFF * CUTOFF;
    BOX_X = LEN * GAP * S;
    BOX_Y = sqrt(3) / 2. * 3. * PLY * GAP * S;
    BOX_HALF_Y = BOX_Y / 2.0;
    N = PLY * LEN;
};

void MolecularDynamics::simulation()
{
    clock_t now = clock(), tick;

    Particle particle(*this);
    Force force(*this);
    Box box(*this);
    Logline logline(*this);
    Sample sample(*this);

    vector<vec2> x0, x, v, f;
    map<string, double> params;
    vector<double> density;
    double zeta;
    double totalVelocitySquare;

    const string curr_path = std::filesystem::current_path().generic_string();
    const string LOG_ADDR = curr_path + "/.data/2D_" + to_string(PLY) + "x" + to_string(LEN) + "_temp_" + to_string(TEMP) + "_iter_" + to_string(ITER_NUM) + ".txt";

    particle.init(x0, x, v, f, zeta, box);
    logline.init(LOG_ADDR, x, params);

    cout << "Calc.\tProg.\tTemp." << setprecision(4) << endl;

    int iter = 0;
    while (++iter <= ITER_NUM) {
        // Update x, v, f every time step
        force.update_2d(x, f, box);
        particle.update(x, v, f, zeta, force, box, totalVelocitySquare);

        // Output and sample parameters every LOG_STEP time steps
        if (iter % LOG_STEP == 0) {
            // Output the current calculation progress and status to the console
            tick = clock();
            cout << (double)(tick - now) / CLOCKS_PER_SEC << "s\t" << ((double)iter / ITER_NUM) * 100 << "%\t"
                 << totalVelocitySquare / (2. * (N - 1.)) << endl;
            now = tick;
        }

        if (iter % LOG_STEP == 0) {
            // Sample some parameters
            sample.msd(x0, x, params);
            sample.density(x, density);

            // Output the sampled parameters to a log file
            logline.print_params(LOG_ADDR, iter, x, params);
            logline.print_density(LOG_ADDR, iter, density);
        }
    }
};