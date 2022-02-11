#pragma once
#include <vector>
#include <random>
#include "param.h"

class particle
{
public:
	void init(vector<vec2>& x, vector<vec2>& xm, vector<vec2>& v);
	double velocity_verlet(vector<vec2>& x, vector<vec2>& xm, vector<vec2>& v, vector<vec2>& f);
private:
	double crand();
};

