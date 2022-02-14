#include "Box.h"

void Box::restrictPositionPBC(vec2& pos)
{
	pos.x() -= floor(pos.x() / x) * x;
	pos.y() -= floor(pos.y() / y) * y;
}

void Box::restrictPositionPBC(vec3& pos)
{
	pos.x() -= floor(pos.x() / x) * x;
	pos.y() -= floor(pos.y() / y) * y;
	pos.z() -= floor(pos.z() / z) * z;
}

void Box::restrictForcePBC(vec2& pos)
{
	pos.x() -= round(pos.x() / x) * x;
	pos.y() -= round(pos.y() / y) * y;
}

void Box::restrictForcePBC(vec3& pos)
{
	pos.x() -= round(pos.x() / x) * x;
	pos.y() -= round(pos.y() / y) * y;
	pos.z() -= round(pos.z() / z) * z;
}
