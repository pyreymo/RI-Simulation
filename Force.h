#pragma once
#include "Box.h"
#include "Simulation.h"
#include <Eigen/Dense>
#include <vector>

using namespace std;
using vec2 = Eigen::Vector2d;
using array2 = Eigen::Array2d;

class Force : protected MolecularDynamics {
public:
    void update_2d(vector<vec2> x, vector<vec2>& f, Box &box);
    Force(MolecularDynamics& md)
        : MolecularDynamics(md) {};

private:
    vector<vec2> CellCoord_2d;
    vector<int> ParticleCell;
    vector<int> HeadList;
    vector<int> LinkedList;
};
