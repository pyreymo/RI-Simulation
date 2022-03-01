#include "Particle.h"
#include "Box.h"
#include "Force.h"
#include <iostream>

#ifdef TWO_DIMENSIONAL_SIMULATION
void Particle::rescale_2d(vector<vec2>& v)
{
	double totalVelocitySquare = 0;
	vec2 totalVelocity(0, 0);
	for (vec2& vi : v)
	{
		totalVelocity += vi;
		totalVelocitySquare += vi.squaredNorm();
	}
	//double tempScaleFactor = sqrt((2. * TEMP) / (totalVelocitySquare / N));
	double tempScaleFactor = sqrt(1 + TIME_STEP / BT_TAU * ((2. * TEMP) / (totalVelocitySquare / N) - 1));
	for (vec2& vi : v) { vi = (vi - totalVelocity / ((double)N)) * tempScaleFactor; }
}

void Particle::init_2d(vector<vec2>& x0, vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box)
{
	v.resize(N);
	x.resize(N);
	f.resize(N);

	for (vec2& vi : v) { vi = vec2(crand(), crand()); }
	rescale_2d(v);

	// initialize FCC-2D
	int count = 0;
	for (int j = 0; j < 2 * PLY + 1; j++)
	{
		for (int i = 0; i < LEN; i++)
		{
			x[count++] = vec2(
				(double)(i + 0.5) * S + (j % 2) * 0.5 * S,
				0.5 * sqrt(3) * (j - PLY) * S + BOX_HALF_Y
			);
		}
	}

	x0 = x;
}

void Particle::update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2)
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
#else
void Particle::rescale_3d(vector<vec3>& v)
{
	double totalVelocitySquare = 0;
	vec3 totalVelocity(0, 0, 0);
	for (vec3& vi : v)
	{
		totalVelocity += vi;
		totalVelocitySquare += vi.squaredNorm();
	}
	//double tempScaleFactor = sqrt((3. * TEMP) / (totalVelocitySquare / N));
	double tempScaleFactor = sqrt(1 + TIME_STEP / BT_TAU * ((3. * TEMP) / (totalVelocitySquare / N) - 1));
	for (vec3& vi : v) { vi = (vi - totalVelocity / ((double)N)) * tempScaleFactor; }
}

void Particle::init_3d(vector<vec3>& x0, vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Box box)
{
	double totalV2 = 0;
	vec3 totalV(0, 0, 0);

	v.resize(N);
	x.resize(N);
	f.resize(N);

	for (vec3& vi : v) { vi = vec3(crand(), crand(), crand()); }
	rescale_3d(v);

	// initialize FCC-3D
	int sr = 2 * PLY + 1, margin_k = 0, margin = 0, count = 0;
	for (int k = 0; k < sr; k++)
	{
		margin_k = PLY - k;
		margin = abs(margin_k);
		for (int j = 0; j < sr - margin; j++)
		{
			for (int i = 0; i < LEN; i++)
			{
				x[count] = vec3(
					(i + 0.5) * sqrt(6) / 3. * S,
					BOX_HALF_Y + (0.5 * margin + j - PLY) * S,
					BOX_HALF_Z + (margin_k * sqrt(3) / 2.0) * S
				);
				switch (i % 3)
				{
				case 0:
					break;
				case 1:
					x[count] += vec3(0, -S / 2.0, sqrt(3) / 6.0 * S);break;
				case 2:
					x[count] += vec3(0, -S / 2.0, -sqrt(3) / 6.0 * S);break;
				}
				count++;
			}
		}
	}

	x0 = x;
}

void Particle::update_3d(vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Force force, Box box, double& totalV2)
{
	totalV2 = 0;

	for (size_t i = 0; i < N; i++)
	{
		x[i] += TIME_STEP * v[i] + TIME_STEP * TIME_STEP * f[i] * 0.5;
		box.restrictPositionPBC(x[i]);
		v[i] += HALF_DT * f[i];
	}

	force.update_3d(x, f, box);

	for (size_t i = 0; i < N; i++)
	{
		v[i] += HALF_DT * f[i];
		totalV2 += v[i].squaredNorm();
	}
}
#endif
double Particle::crand() {
	return (rand() / double(RAND_MAX)) - 0.5;
}