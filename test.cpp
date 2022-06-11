#include "Simulation.h"

int main()
{
    MolecularDynamics(3, 3, 0.7, 1e-3, 1e4, 1e2, 5, 1).simulation();

    system("pause");
}