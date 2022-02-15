#pragma once
#include <vector>
#include <random>
#include "Param.h"
#include "Box.h"
#include "Force.h"

class Particle
{
public:
	void init_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box);
	void init_3d(vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Box box);
	void rescale_2d(vector<vec2>& v);
	void rescale_3d(vector<vec3>& v);
	void update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2);
	void update_3d(vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Force force, Box box, double& totalV2);
private:
	double crand();
};

