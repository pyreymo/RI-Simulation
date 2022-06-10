#include "Simulation.h"
#include <filesystem>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

    Simulation s(3, 3, 0.7, 1e-3, 1e4, 1, 1e2, 5, 1);
    s.start();

    cout << std::filesystem::current_path().generic_string() << endl;

    auto _ = getchar();
}