#include "Logline.h"
#include "Box.h"
#include "Force.h"
#include <iostream>
#include <fstream>

#ifdef TWO_DIMENSIONAL_SIMULATION
void Logline::print_log_2d(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::app);
	os << "Iter " << iter << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << endl;

	}
	for (auto m : params) {
		os << "@ \t" << m.first << "\t" << m.second << endl;
	}
	os.close();
}

void Logline::init_log_2d(string LOG_ADDR, vector<vec2> x, map<string, double> params) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::out);

	os << "# N\t" << N << endl;
	os << "# Radius\t" << sqrt(3) / 2.0 * PLY * S << endl;
	os << "# Length\t" << LEN * S << endl;

	os << "# TimeStep\t" << TIME_STEP << endl;
	os << "# IterNum\t" << ITER_NUM << endl;
	os << "# LogStep\t" << LOG_STEP << endl;

	os << "# Temp\t" << TEMP << endl;
	os << "# Cutoff\t" << CUTOFF << endl;

	os << "# BOX_X\t" << BOX_X << endl;
	os << "# BOX_Y\t" << BOX_Y << endl;

	os.close();

	print_log_2d(LOG_ADDR, 1, x, params);

}
#else
void Logline::print_log_3d(string LOG_ADDR, int iter, vector<vec3> x, map<string, double> params) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::app);
	os << "Iter " << iter << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << "," << x[i].z() << endl;
	}
	for (auto m : params) {
		os << "@ \t" << m.first << "\t" << m.second << endl;
	}
	os.close();
}

void Logline::init_log_3d(string LOG_ADDR, vector<vec3> x, map<string, double> params) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::out);

	os << "# N\t" << N << endl;
	os << "# Radius\t" << PLY * S << endl;
	os << "# Length\t" << sqrt(6) / 3.0 * LEN * S << endl;

	os << "# DeltaTime\t" << TIME_STEP << endl;
	os << "# IterSteps\t" << ITER_NUM << endl;
	os << "# LogSteps\t" << LOG_STEP << endl;

	os << "# Temperature\t" << TEMP << endl;
	os << "# Cutoff\t" << CUTOFF << endl;

	os << "# BOX_X\t" << BOX_X << endl;
	os << "# BOX_Y\t" << BOX_Y << endl;
	os << "# BOX_Z\t" << BOX_Z << endl;

	os.close();

	print_log_3d(LOG_ADDR, 1, x, params);
}
#endif
