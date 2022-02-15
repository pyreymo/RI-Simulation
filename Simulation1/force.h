#pragma once
#include "Param.h"
#include <vector>
#include "Box.h"

class Force
{
public:
	void update_2d(vector<vec2> x, vector<vec2>& f, Box box);
	void update_3d(vector<vec3> x, vector<vec3>& f, Box box);
protected:

private:
	vector<vec2> CellCoord_2d;
	vector<vec3> CellCoord_3d;
	vector<int> ParticleCell;
	vector<int> HeadList;
	vector<int> LinkedList;
};

