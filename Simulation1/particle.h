#pragma once
#include <vector>
#include <random>
#include "Param.h"
#include "Box.h"
#include "Force.h"

class Particle
{
public:
	void init(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box);
	void update(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2);
private:
	double crand();
};

