#include "mpi.h"
#include "Simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	Simulation s(2, 8, 0.7);

    MPI_Finalize();
}