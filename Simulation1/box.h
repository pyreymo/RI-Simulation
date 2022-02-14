#pragma once
#include "Param.h"

class Box
{
public:
	double x, y, z;
	Box(double x, double y) :x(x), y(y), z(0) {};
	Box(double x, double y, double z) :x(x), y(y), z(z) {};
	void restrictPositionPBC(vec2&);
	void restrictPositionPBC(vec3&);
	void restrictForcePBC(vec2&);
	void restrictForcePBC(vec3&);
};

