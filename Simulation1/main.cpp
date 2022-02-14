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

void print_log(string LOG_ADDR, int iter, vector<vec2> x) {
	ofstream os;
	os.open(LOG_ADDR, std::ios_base::app);
	os << "Iter " << iter << endl;
	for (size_t i = 0; i < N; i++) {
		os << i << "," << x[i].x() << "," << x[i].y() << endl;
	}
	os.close();
}

void init_log(string LOG_ADDR, vector<vec2> x) {
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

	particle.init(x, v, f, box);
	string LOG_ADDR = "尺寸" + to_string(PLY) + "x" + to_string(LEN) + "温度" + to_string(TEMP)
		+ "迭代" + to_string(N_STEP) + "DT" + to_string(DT) + "截断" + to_string(TRUNC_DIST) + ".txt";
	init_log(LOG_ADDR, x);
	cout << "用时\t进度\t温度" << setprecision(4) << endl;
	while (++n <= N_STEP)
	{
		force.update(x, f, box);
		particle.update(x, v, f, force, box, totalV2);

		if (n % LOG_STEP == 0) {
			tick = clock();
			cout << (double)(tick - start) / CLOCKS_PER_SEC << "\t"
				<< ((double)n / N_STEP) * 100 << "%\t"
				<< totalV2 / (2. * (N - 1.)) << endl;
			start = tick;

			print_log(LOG_ADDR, n, x);
		}
	}
};

void debug() {

}

int main() {
	simulation_2d();
	//debug();
	return 0;
}