#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>
#include "Particle.h"
#include "Box.h"
#include "Force.h"
#include "Param.h"

using namespace std;

void print_log_2d(string LOG_ADDR, int iter, vector<vec2> x) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::app);
	os << "Iter " << iter << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << endl;
	}
	os.close();
}

void init_log_2d(string LOG_ADDR, vector<vec2> x) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::out);
	os << "# 层数\t" << PLY << endl;
	os << "# 长度\t" << LEN << endl;
	os << "# dt\t" << DT << endl;
	os << "# 迭代次数\t" << N_STEP << endl;
	os << "# 记录步长\t" << LOG_STEP << endl;
	os << "# 温度\t" << TEMP << endl;
	os << "# 截断距离\t" << TRUNC_DIST << endl;
	os << "# BOX_X\t" << BOX_X << endl;
	os << "# BOX_Y\t" << BOX_Y << endl;
	os << "Iter 1" << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << endl;
	}
	os.close();
}

void simulation_2d() {
	clock_t start = clock(), tick;

	int n = 0;
	double totalV2;
	vector<vec2> x, v, f;

	Particle particle;
	Box box(BOX_X, BOX_Y);
	Force force;

	particle.init_2d(x, v, f, box);
	string LOG_ADDR = "2D_" + to_string(PLY) + "x" + to_string(LEN) + "_temp_" + to_string(TEMP)
		+ "_iter_" + to_string(N_STEP) + ".txt";
	init_log_2d(LOG_ADDR, x);
	cout << "用时\t进度\t温度" << setprecision(4) << endl;
	while (++n <= N_STEP)
	{
		force.update_2d(x, f, box);
		particle.update_2d(x, v, f, force, box, totalV2);

		if (n % 10 == 0) {
			particle.rescale_2d(v);
		}

		if (n % LOG_STEP == 0) {
			tick = clock();
			cout << (double)(tick - start) / CLOCKS_PER_SEC << "\t"
				<< ((double)n / N_STEP) * 100 << "%\t"
				<< totalV2 / (2. * (N - 1.)) << endl;
			start = tick;

			print_log_2d(LOG_ADDR, n, x);
		}
	}
};


void print_log_3d(string LOG_ADDR, int iter, vector<vec3> x) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::app);
	os << "Iter " << iter << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << "," << x[i].z() << endl;
	}
	os.close();
}

void init_log_3d(string LOG_ADDR, vector<vec3> x) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::out);
	os << "# 层数\t" << PLY << endl;
	os << "# 长度\t" << LEN << endl;
	os << "# dt\t" << DT << endl;
	os << "# 迭代次数\t" << N_STEP << endl;
	os << "# 记录步长\t" << LOG_STEP << endl;
	os << "# 温度\t" << TEMP << endl;
	os << "# 截断距离\t" << TRUNC_DIST << endl;
	os << "# BOX_X\t" << BOX_X << endl;
	os << "# BOX_Y\t" << BOX_Y << endl;
	os << "# BOX_Z\t" << BOX_Z << endl;
	os << "Iter 1" << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << "," << x[i].z() << endl;
	}
	os.close();
}

void simulation_3d() {
	clock_t start = clock(), tick;

	int n = 0;
	double totalV2;
	vector<vec3> x, v, f;

	Particle particle;
	Box box(BOX_X, BOX_Y, BOX_Z);
	Force force;

	particle.init_3d(x, v, f, box);
	string LOG_ADDR = "3D_" + to_string(PLY) + "x" + to_string(LEN) + "x" + to_string(LEN)
		+ "_temp_" + to_string(TEMP)
		+ "_iter_" + to_string(N_STEP) + ".txt";
	init_log_3d(LOG_ADDR, x);
	cout << "用时\t进度\t温度" << setprecision(4) << endl;
	while (++n <= N_STEP)
	{
		force.update_3d(x, f, box);
		particle.update_3d(x, v, f, force, box, totalV2);

		if (n % 10 == 0) {
			particle.rescale_3d(v);
		}

		if (n % LOG_STEP == 0) {
			tick = clock();
			cout << (double)(tick - start) / CLOCKS_PER_SEC << "\t"
				<< ((double)n / N_STEP) * 100 << "%\t"
				<< totalV2 / (3. * (N - 1.)) << endl;
			start = tick;

			print_log_3d(LOG_ADDR, n, x);
		}
	}
};

void debug() {

}

int main() {
	simulation_2d();
	//simulation_3d();
	//debug();
	return 0;
}