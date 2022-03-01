#pragma once
#include <vector>
#include <random>
#include <map>
#include "Param.h"
#include "Box.h"
#include "Force.h"

class Sample
{
public:
#ifdef TWO_DIMENSIONAL_SIMULATION
	double msd_2d(vector<vec2> x0, vector<vec2> x, map<string, double>& params);
#else
	double msd_3d(vector<vec3> x0, vector<vec3> x, map<string, double>& params);
#endif
};

