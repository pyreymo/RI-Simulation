#pragma once
#include "Param.h"
#include <vector>
#include "Box.h"

class Force
{
public:
#ifdef TWO_DIMENSIONAL_SIMULATION
	void update_2d(vector<vec2> x, vector<vec2>& f, Box box);
#else
	void update_3d(vector<vec3> x, vector<vec3>& f, Box box);
#endif
protected:

private:
#ifdef TWO_DIMENSIONAL_SIMULATION
	vector<vec2> CellCoord_2d;
#else
	vector<vec3> CellCoord_3d;
#endif
	vector<int> ParticleCell;
	vector<int> HeadList;
	vector<int> LinkedList;
};

