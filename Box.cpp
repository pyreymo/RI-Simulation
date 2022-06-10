#include "Box.h"

void Box::restrictPositionPBC(vec2& pos)
{
    pos.x() -= floor(pos.x() / BOX_X) * BOX_X;
    pos.y() -= floor(pos.y() / BOX_Y) * BOX_Y;
}

void Box::restrictForcePBC(vec2& pos)
{
    pos.x() -= round(pos.x() / BOX_X) * BOX_X;
    pos.y() -= round(pos.y() / BOX_Y) * BOX_Y;
}

Box::Box(double xx, double yy, int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance, double pairwise_gap)
    : Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance, pairwise_gap)
{
    this->BOX_X = xx;
    this->BOX_Y = yy;
    this->BOX_HALF_Y = yy / 2.;
}