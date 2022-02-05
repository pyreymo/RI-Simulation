#include <iostream>
#include <cmath>
#include <cstdlib>
#include <Eigen/Dense>
#include "Simulation1.h"


using namespace std;
using namespace Eigen;
using vec2 = Vector2d;


constexpr int        PLY          = 3;								     // 线层数
constexpr int        LEN          = 18;							         // 线长度
constexpr int        N            = (2 * PLY + 1) * LEN;		         // 粒子总数
constexpr double     DT           = 0.01;						         // 时间步长
constexpr int        N_STEP       = 10000;					             // 时间步数
const     double     S            = pow(2, 1 / 6);			             // 平衡距离
const     double     RAD          = sqrt(3) / 2 * PLY * S;		         // 线半径
const     double     BOX_LEN      = (LEN + 0.5) * S;			         // 盒子长度
const     double     BOX_WID      = sqrt(3) * (10 + PLY) * S;		     // 盒子宽度
const     double     INSTABLE_LEN = sqrt(3);				             // 不稳定性阈值


double temp = 0.7;	        // 温度
double ke = 0;		        // 热能
vec2   f[N];	            // 每个分子的受力
vec2   v[N];	            // 每个分子的速度
vec2   x[N];	            // 当前时刻粒子位置
vec2   xm[N];	            // 上个时刻粒子位置


// 产生 (-0.5,0.5) 的随机数
const double crand() { return ((double)rand() / (RAND_MAX)) - 0.5; }


void init()
{
	// 产生一组平衡且恒温的初始速度
	vec2 sum(0, 0);
	for (size_t i = 0; i < N; i++)
	{
		v[i] = vec2(crand(), crand());
		sum += v[i];
	}
	vec2 del = sum / ((double)N);
	for (size_t i = 0; i < N; i++)
	{
		v[i] -= del;	// 总动量为零
		ke += v[i].transpose() * v[i];
	}
	double fs = sqrt(2 * N * temp / ke);	// 温度标定因子
	for (size_t i = 0; i < N; i++)
	{
		v[i] *= fs;	// 控制瞬时温度
	}

	// 计算粒子初始位置
	for (size_t i = 0; i < 2 * PLY + 1; i++)
	{
		for (size_t j = 0; j < LEN; j++)
		{
			int k = i * LEN + j;
			x[k] = vec2(
				j * S,
				sqrt(3) / 2 * (i - PLY) * S
			);
			xm[k] = x[k] - v[k] * DT;
		}
	}

}


void force() {

}


void integrate() {

}


void sample() {

}


int main() {
	// 初始化粒子
	init();

	double t = 0;
	while (t < N_STEP * DT)
	{
		force();
		integrate();
		t += DT;
		sample();
	}

	return 0;
}