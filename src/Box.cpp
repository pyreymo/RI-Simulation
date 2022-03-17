#include "Box.h"

void Box::restrictPositionPBC(vec2& pos)
{
	pos.x() -= floor(pos.x() / x) * x;
	pos.y() -= floor(pos.y() / y) * y;
}

void Box::restrictForcePBC(vec2& pos)
{
	pos.x() -= round(pos.x() / x) * x;
	pos.y() -= round(pos.y() / y) * y;
}

Box::Box(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance)
	: Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance)
{
}