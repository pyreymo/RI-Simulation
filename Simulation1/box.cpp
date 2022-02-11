#include "box.h"

void box::pbc_restrict(vec2& pos)
{
	pos.x() -= floor(pos.x() / x) * x;
	pos.y() -= floor(pos.y() / y) * y;
}

void box::pbc_restrict(vec3& pos)
{
	pos.x() -= floor(pos.x() / x) * x;
	pos.y() -= floor(pos.y() / y) * y;
	pos.z() -= floor(pos.z() / z) * z;
}

void box::pbc_mic(vec2& pos)
{
	pos.x() -= round(pos.x() / x) * x;
	pos.y() -= round(pos.y() / y) * y;
}

void box::pbc_mic(vec3& pos)
{
	pos.x() -= round(pos.x() / x) * x;
	pos.y() -= round(pos.y() / y) * y;
	pos.z() -= round(pos.z() / z) * z;
}
