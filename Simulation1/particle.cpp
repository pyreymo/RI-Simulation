#include "particle.h"
#include "box.h"
#include "force.h"

void particle::init(vector<vec2>& x, vector<vec2>& xm, vector<vec2>& v)
{
	// 初始化速度
	double ke = 0;
	vec2 sum(0, 0);
	for (size_t i = 0; i < N; i++)
	{
		v[i] = vec2(crand(), crand());
		sum += v[i];
	}
	vec2 del = sum / ((double)N);
	for (size_t i = 0; i < N; i++)
	{
		v[i] -= del;
		ke += v[i].squaredNorm();
	}
	double factor_scale = sqrt(2. * N * TEMP / ke); // 温度标定因子
	for (size_t i = 0; i < N; i++) v[i] *= factor_scale;

	// 初始化晶胞
	for (int i = 0; i < 2 * PLY + 1; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			int k = i * LEN + j;
			x[k] = vec2(
				(double)j * S + 0.5,
				0.5 * sqrt(3) * (i + 0.5) * S + BOX_HALF_Y
			);
			xm[k] = x[k] - v[k] * DT;
		}
	}
}

double particle::velocity_verlet(vector<vec2>& x, vector<vec2>& xm, vector<vec2>& v, vector<vec2>& f)
{
	double ke = 0;

	force forceObj = force();
	box boxObj = box(BOX_X, BOX_Y);

	for (size_t i = 0; i < N; i++)
	{
		x[i] += DT * x[i] + DT * DT * f[i] * 0.5;
		boxObj.pbc_restrict(x[i]);
		v[i] += f[i] * DT * 0.5;
		forceObj.cell_list();
	}

	// TODO 刷新一次force

	for (size_t i = 0; i < N; i++)
	{
		v[i] += f[i] * DT * 0.5;
		ke += v[i].squaredNorm();
	}

	return ke;


}

double particle::crand() {
	return ((double)rand() / (RAND_MAX)) - 0.5;
}