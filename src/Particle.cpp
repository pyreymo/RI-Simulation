 #include "Particle.h"

 void Particle::rescale_2d(vector<vec2> &v)
 {
 	double totalVelocitySquare = 0;
 	vec2 totalVelocity(0, 0);
 	for (vec2 &vi : v)
 	{
 		totalVelocity += vi;
 		totalVelocitySquare += vi.squaredNorm();
 	}
 	// double tempScaleFactor = sqrt((2. * TEMP) / (totalVelocitySquare / N));
 	double tempScaleFactor = sqrt(1 + TIME_STEP / BT_TAU * ((2. * TEMP) / (totalVelocitySquare / N) - 1));
 	for (vec2 &vi : v)
 	{
 		vi = (vi - totalVelocity / ((double)N)) * tempScaleFactor;
 	}
 }

 void Particle::init_2d(vector<vec2> &x0, vector<vec2> &x, vector<vec2> &v, vector<vec2> &f, Box box)
 {
 	v.resize(N);
 	x.resize(N);
 	f.resize(N);

 	for (vec2 &vi : v)
 	{
 		vi = vec2(crand(), crand());
 	}
 	rescale_2d(v);

 	// initialize FCC-2D
 	int count = 0;
 	for (int j = 0; j < 2 * PLY + 1; j++)
 	{
 		for (int i = 0; i < LEN; i++)
 		{
 			x[count++] = vec2(
 				(double)(i + 0.5) * S + (j % 2) * 0.5 * S,
 				0.5 * sqrt(3) * (j - PLY) * S + BOX_HALF_Y);
 		}
 	}

 	x0 = x;
 }

 void Particle::update_2d(vector<vec2> &x, vector<vec2> &v, vector<vec2> &f, Force force, Box box, double &totalV2)
 {
 	totalV2 = 0;

 	for (size_t i = 0; i < N; i++)
 	{
 		x[i] += TIME_STEP * v[i] + TIME_STEP * TIME_STEP * f[i] * 0.5;
 		box.restrictPositionPBC(x[i]);
 		v[i] += HALF_DT * f[i];
 	}

 	force.update_2d(x, f, box);

 	for (size_t i = 0; i < N; i++)
 	{
 		v[i] += HALF_DT * f[i];
 		totalV2 += v[i].squaredNorm();
 	}
 }

 double Particle::crand()
 {
 	return (rand() / double(RAND_MAX)) - 0.5;
 }

Particle::Particle(int n_plies, int n_length, double temperature, double time_step, int n_iteration, int temperature_rescale_span, int logline_span, double cutoff_distance)
	: Simulation(n_plies, n_length, temperature, time_step, n_iteration, temperature_rescale_span, logline_span, cutoff_distance)
{
}
