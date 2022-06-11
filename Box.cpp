#include "Box.h"

void Box::restrictPosition(vec2& pos)
{
    pos.x() -= floor(pos.x() / BOX_X) * BOX_X;
    pos.y() -= floor(pos.y() / BOX_Y) * BOX_Y;
}

void Box::restrictForce(vec2& pos)
{
    pos.x() -= round(pos.x() / BOX_X) * BOX_X;
    pos.y() -= round(pos.y() / BOX_Y) * BOX_Y;
}