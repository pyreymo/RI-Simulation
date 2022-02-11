#pragma once
#include <vector>
#include "particle.h"

void simulation_2d() {
	vector<vec2> x(N), xm(N), v(N), f(N);
	particle particle_generator = particle();
	particle_generator.init(x, xm, v);
	particle_generator.velocity_verlet(x, xm, v, f);
};

int main() {
	simulation_2d();
	return 0;
}