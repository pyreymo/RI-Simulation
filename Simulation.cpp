#include "Simulation.h"
#include "Box.h"
#include "Force.h"
#include "Logline.h"
#include "Particle.h"
#include "Sample.h"
#include <ctime>
#include <filesystem>
#include <iomanip>

Simulation::Simulation(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_gap, int logline_span, double cutoff_distance, double pairwise_gap)
{
    PLY = n_plies;
    LEN = n_length;
    TEMP = temperature;
    TIME_STEP = time_step;
    ITER_NUM = n_iteration;
    RESCALE = temperature_rescale_gap;
    LOG_STEP = logline_span;
    GAP = pairwise_gap;
    S = pow(2, 1 / 6.);
    CUTOFF = cutoff_distance * S;
    CUTOFF_2 = CUTOFF * CUTOFF;
    BOX_X = LEN * GAP * S;
    // BOX_Y = sqrt(3) / 2. * (20. + PLY * GAP) * S;
    BOX_Y = sqrt(3) / 2. * 3. * PLY * GAP * S;
    BOX_HALF_Y = BOX_Y / 2.0;
    BT_TAU = 1.0;
    N = PLY * LEN;
    HALF_DT = TIME_STEP / 2.0;
};

void Simulation::start()
{
    clock_t start = clock(), tick;

    Particle particle(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF, this->GAP);
    Force force(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF, this->GAP);
    Box box(this->BOX_X, this->BOX_Y, this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF, this->GAP);
    Logline logline(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF, this->GAP);
    Sample sample(this->PLY, this->LEN, this->TEMP, this->TIME_STEP, this->ITER_NUM, this->RESCALE, this->LOG_STEP, this->CUTOFF, this->GAP);

    vector<vec2> x0, x, v, f;
    vector<double> density;
    double zeta;
    double totalVelocitySquare;
    map<string, double> params;
    const string LOG_ADDR = std::filesystem::current_path().generic_string() + "/.data/2D_" + to_string(PLY) + "x" + to_string(LEN) + "_temp_" + to_string(TEMP) + "_iter_" + to_string(ITER_NUM) + ".txt";

    particle.init_2d(x0, x, v, f, zeta, box);
    logline.init_log_2d(LOG_ADDR, x, params);

    cout << "Calc.\tProg.\tTemp." << setprecision(4) << endl;

    int iter = 0;
    while (++iter <= ITER_NUM) {
        // Update x, v, f every time step
        force.update_2d(x, f, box);
        particle.update_2d(x, v, f, zeta, force, box, totalVelocitySquare);

        //// Rescale every RESCALE time steps
        // if (iter % RESCALE == 0)
        //{
        //	particle.rescale_2d(v);
        // }

        // Output and sample parameters every LOG_STEP time steps
        if (iter % LOG_STEP == 0) {
            // Output the current calculation progress and status to the console
            tick = clock();
            cout << (double)(tick - start) / CLOCKS_PER_SEC << "s\t" << ((double)iter / ITER_NUM) * 100 << "%\t"
                 << totalVelocitySquare / (2. * (N - 1.)) << endl;
            start = tick;
        }

        if (iter % LOG_STEP == 0) {
            // Sample some parameters
            sample.msd_2d(x0, x, params);
            sample.density_2d(x, density);

            // Output the sampled parameters to a log file
            logline.print_double_params(LOG_ADDR, iter, x, params);
            logline.print_density(LOG_ADDR, iter, density);
        }
    }
};