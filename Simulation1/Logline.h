#pragma once
#include <vector>
#include <random>
#include <map>
#include "Param.h"
#include "Box.h"
#include "Force.h"

class Logline
{
public:
#ifdef TWO_DIMENSIONAL_SIMULATION
	void init_log_2d(string LOG_ADDR, vector<vec2> x, map<string, double> params);
	void print_log_2d(string LOG_ADDR, int iter, vector<vec2> x, map<string, double> params);
#else
	void init_log_3d(string LOG_ADDR, vector<vec3> x, map<string, double> params);
	void print_log_3d(string LOG_ADDR, int iter, vector<vec3> x, map<string, double> params);
#endif
};

