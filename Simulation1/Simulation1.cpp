#include <iostream>
#include <cmath>
#include <cstdlib>
#include <Eigen/Dense>
#include "Simulation1.h"

using namespace std;
using namespace Eigen;
using v2 = Vector2d;


/* 初始化体系
1.	粒子数目：(2K+1)M
	盒子
		长度：(M+1/2)S
		宽度：R=(sqrt(3)/2)KS, W=sqrt3(10+K)S
	坐标范围；计算每个粒子的二维坐标
	RI条件：M>\sqrt3 \pi K+1/2= 5.44K+0.5 断裂
2. 初始化速度、力数组(N*1)，轴1是粒子，轴2是二维速度、力向量
3.
*/
const int K = 3;						// 线层数
const int M = 18;						// 线长度
const int N = (2 * K + 1) * M;			// 粒子总数
const double S = pow(2., 1. / 6.);		// 平衡距离
const double R = sqrt(3) / 2. * K * S;	// 线半径
const double L = (M + 0.5) * S;			// 盒子长度
const double W = sqrt(3) * (10 + K) * S;// 盒子宽度

double T = 0.7;	// 温度
double KE = 0;	// 热能


v2 f[N];	// 每个分子的受力
v2 v[N];	// 每个分子的速度

// 产生 (-0.5,0.5) 的随机数
const double myRand() { return ((double)rand() / (RAND_MAX)) - 0.5; }

// 产生一组平衡且恒温的初始速度
void initVelocity()
{
	v2 sum(0, 0);
	for (size_t i = 0; i < N; i++)
	{
		v[i] = v2(myRand(), myRand());
		sum += v[i];
	}
	v2 del = sum / ((double)N);
	for (size_t i = 0; i < N; i++)
	{
		v[i] -= del;
		KE += v[i].transpose() * v[i];
	}
	double fs = sqrt(2.0 * N * T / KE);
	for (size_t i = 0; i < N; i++)
	{
		v[i] *= fs;
	}
}

int main() {
	initVelocity();

	cout << KE << endl;

	return 0;
}