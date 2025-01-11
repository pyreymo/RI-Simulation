#include "Box.hpp"
#include <cmath>

void Box::restrictPosition(vec2 &pos)
{
    pos.x() -= floor(pos.x() / BOX_X) * BOX_X;
    pos.y() -= floor(pos.y() / BOX_Y) * BOX_Y;
}

void Box::restrictForce(vec2 &force)
{
    force.x() -= round(force.x() / BOX_X) * BOX_X;
    force.y() -= round(force.y() / BOX_Y) * BOX_Y;
}
