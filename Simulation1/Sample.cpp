#include "Sample.h"
#include "Param.h"
#include "Box.h"
#include "Force.h"

#ifdef TWO_DIMENSIONAL_SIMULATION
double Sample::msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params) {
	// Calculate for mean square displacement (MSD)
	double msd = 0.0;
	int N = x0.size();
	for (int i = 0; i < N; ++i) {
		msd += (x0[i] - x[i]).squaredNorm();
	}
	msd /= (double)N;
	params["msd"] = msd;
}
#else
double Sample::msd_3d(vector<vec3> x0, vector<vec3> x, map<string, double>& params) {
	// Calculate for mean square displacement (MSD)
	double msd = 0.0;
	int N = x0.size();
	for (int i = 0; i < N; ++i) {
		msd += (x0[i] - x[i]).squaredNorm();
	}
	msd /= (double)N;
	params["msd"] = msd;
}
#endif