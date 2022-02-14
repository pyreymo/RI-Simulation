#pragma once
#include "Param.h"
#include <vector>
#include "Box.h"

class Force
{
public:
	void update(vector<vec2> x, vector<vec2>& f, Box box);
protected:

private:
	vector<vec2> forceVector;
	vec2 forceCoord;
	vector<int> ParticleCell;
	vector<int> HeadList;
	vector<int> LinkedList;
	vector<vec2> CellCoord;
};

