#include "Particle.h"
#include "Box.h"
#include "Force.h"

void Particle::init(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box)
{
	double totalV2 = 0;
	vec2 sum(0, 0);

	v.resize(N);
	x.resize(N);
	f.resize(N);
	for (size_t i = 0; i < N; i++)
	{
		v[i] = vec2(crand(), crand());
		sum += v[i];
	}

	vec2 del = sum / ((double)N);
	for (size_t i = 0; i < N; i++)
	{
		v[i] -= del;
		totalV2 += v[i].squaredNorm();
	}

	double factor_scale = sqrt(2. * N * TEMP / totalV2); // 温度标定因子
	for (size_t i = 0; i < N; i++) v[i] *= factor_scale;

	// 初始化晶胞
	for (int i = 0; i < 2 * PLY + 1; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			int k = i * LEN + j;
			x[k] = vec2(
				(double)(j + 0.5) * S + (i % 2) * 0.5 * S,
				0.5 * sqrt(3) * (i - PLY) * S + BOX_HALF_Y
			);
		}
	}
}

void Particle::update(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2)
{
	totalV2 = 0;
	vec2 vh[N]; // 半步速度

	// 更新半步速度和位置
	for (size_t i = 0; i < N; i++)
	{
		vh[i] = v[i] + HALF_DT * (f[i] - v[i]);
		x[i] += vh[i] * DT;
		box.restrictPositionPBC(x[i]);
	}

	force.update(x, f, box);

	for (size_t i = 0; i < N; i++)
	{
		f[i] += sigma * vec2(NORM_DIST(RAND_ENGINE), NORM_DIST(RAND_ENGINE));
		v[i] = coef1 * (vh[i] + HALF_DT * f[i]);
		totalV2 += v[i].squaredNorm();
	}
}

double Particle::crand() {
	return ((double)rand() / (RAND_MAX)) - 0.5;
}