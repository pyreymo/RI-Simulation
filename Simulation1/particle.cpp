#include "Particle.h"
#include "Box.h"
#include "Force.h"
#include <iostream>

void Particle::init_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Box box)
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

	double temp_scale_factor = sqrt(2. * N * TEMP / totalV2);
	for (size_t i = 0; i < N; i++) v[i] *= temp_scale_factor;

	// 初始化晶胞
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
}

void Particle::init_3d(vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Box box)
{
	double totalV2 = 0;
	v.resize(N);
	x.resize(N);
	f.resize(N);

	for (size_t i = 0; i < N; i++) v[i] = vec3(crand(), crand(), crand());
	vec3 totalV(0, 0, 0);
	for (size_t i = 0; i < N; i++)
	{
		totalV += v[i];
		totalV2 += v[i].squaredNorm();
	}

	vec3 averageV = totalV / ((double)N);
	double factor_scale = sqrt((3. * TEMP * N) / totalV2);
	for (size_t i = 0; i < N; i++) v[i] = (v[i] - averageV) * factor_scale;

	// 初始化晶胞
	int length_coef1 = 2 * PLY + 1, margin = 0, count = 0;
	for (int k = 0; k < length_coef1; k++)
	{
		margin = abs(PLY - k);
		for (int j = 0; j < length_coef1 - margin; j++)
		{
			for (int i = 0; i < LEN; i++)
			{
				x[count++] = vec3(
					(i + 0.5) * sqrt(6) / 3. * S,
					(0.5 * margin + j - PLY) * S + BOX_HALF_Y,
					(k + (i % 2) * sqrt(3) / 3. - sqrt(3) / 2. * PLY) * S + BOX_HALF_Z
				);
			}
		}
	}
}

void Particle::rescale_2d(vector<vec2>& v)
{
	double totalV2 = 0;
	vec2 sum(0, 0);
	for (size_t i = 0; i < N; i++)
	{
		sum += v[i];
		totalV2 += v[i].squaredNorm();
	}

	vec2 averageV = sum / ((double)N);
	double averageV2 = totalV2 / N;
	double factor_scale = sqrt((2. * TEMP) / averageV2); // 温度标定因子
	for (size_t i = 0; i < N; i++) v[i] = (v[i] - averageV) * factor_scale;
}

void Particle::update_2d(vector<vec2>& x, vector<vec2>& v, vector<vec2>& f, Force force, Box box, double& totalV2)
{
	totalV2 = 0;
	//vec2 vh[N]; // 半步速度

	//// 更新半步速度和位置
	//for (size_t i = 0; i < N; i++)
	//{
	//	vh[i] = v[i] + HALF_DT * (f[i] - v[i]);
	//	x[i] += vh[i] * DT;
	//	box.restrictPositionPBC(x[i]);
	//}

	//force.update_2d(x, f, box);

	//for (size_t i = 0; i < N; i++)
	//{
	//	f[i] += sigma * vec2(NORM_DIST(RAND_ENGINE), NORM_DIST(RAND_ENGINE));
	//	v[i] = coef1 * (vh[i] + HALF_DT * f[i]);
	//	totalV2 += v[i].squaredNorm();
	//}

	for (size_t i = 0; i < N; i++)
	{
		x[i] += DT * v[i] + DT * DT * f[i] * 0.5;
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

void Particle::rescale_3d(vector<vec3>& v)
{
	double totalV2 = 0;
	vec3 totalV(0, 0, 0);
	for (size_t i = 0; i < N; i++)
	{
		totalV += v[i];
		totalV2 += v[i].squaredNorm();
	}

	vec3 averageV = totalV / ((double)N);
	double factor_scale = sqrt((3. * TEMP * N) / totalV2);
	for (size_t i = 0; i < N; i++) v[i] = (v[i] - averageV) * factor_scale;
}

void Particle::update_3d(vector<vec3>& x, vector<vec3>& v, vector<vec3>& f, Force force, Box box, double& totalV2)
{
	totalV2 = 0;

	for (size_t i = 0; i < N; i++)
	{
		x[i] += DT * v[i] + DT * DT * f[i] * 0.5;
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

double Particle::crand() {
	return (rand() / double(RAND_MAX)) - 0.5;
}