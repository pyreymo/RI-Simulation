#pragma once
#include "param.h"

class box
{
public:
	double x, y, z;
	box(double x, double y) :x(x), y(y), z(0) {};
	box(double x, double y, double z) :x(x), y(y), z(z) {};
	void pbc_restrict(vec2&);
	void pbc_restrict(vec3&);
	void pbc_mic(vec2&);
	void pbc_mic(vec3&);
};

