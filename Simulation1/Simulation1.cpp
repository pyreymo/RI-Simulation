//#include <cmath>
//#include <cstdlib>
//#include <ctime>
//#include <fstream>
//#include <iostream>
//#include <random>
//#include <Eigen/Dense>
//
//
//using namespace std;
//using namespace Eigen;
//using vec2 = Vector2d;
//
//
//constexpr int    PLY            = 2;                        // *线层数
//constexpr int    LEN            = 16;                       // *线长度
//constexpr double DT             = 0.01;                     // *时间步长
//constexpr double TRUNC_ENERGY   = -0.016316891136;          // *截断能量
//constexpr int    N_STEP         = 50000;                    // *时间步数
//constexpr int    LOG_RNG        = 1000;                     // *记录步长
//constexpr double TEMP           = 0.71;                     // *体系温度
//constexpr int    N              = (2 * PLY + 1) * LEN;      // 粒子总数
//const     double S              = pow(2, 1 / 6);            // 平衡距离
//const	  double TRUNC_DIST     = 2.5 * S;                  // *截断距离
//const     string LOG_ADDR       = "sim.txt";                // *日志存储地址
//const     double BOX_LEN        = (LEN + 0.5) * S;          // 盒子长度
//const     double BOX_WIDTH      = sqrt(3) * (10 + PLY) * S; // 盒子宽度
//const     double BOX_HALF_WIDTH = BOX_WIDTH / 2.;           // 盒子半宽度
//const     double TRUNC_DIST_2   = pow(TRUNC_DIST, 2);       // 截断距离平方
//
//double ke           = 0;									// 热能
//double pe           = 0;                                    // 势能
//double gamma        = 1.0;
//const double TEMP1  = sqrt(2.0 * gamma * TEMP / DT);
//const double TEMP2  = 1.0 + TEMP / 2. * gamma;
//
//vec2   f[N];                                                // 每个分子的受力
//vec2   v[N];                                                // 每个分子的速度
//vec2   x[N];                                                // 当前时刻粒子位置
//vec2   xm[N];                                               // 上个时刻粒子位置
//
//
//// 代码运行计时器
//static default_random_engine e(time(0));
//static normal_distribution<double> n(0, 1);
//clock_t start, tick;
//
//
//// 判断周期性边界条件的工具函数
//int nint(double x) {
//	return x < 0 ? -1 : (int)(abs(x) >= 0.5);
//}
//
//
//// 产生 (-0.5,0.5) 的随机数
//double crand() {
//	return ((double)rand() / (RAND_MAX)) - 0.5;
//}
//
//
//void init()
//{
//	// 产生一组平衡且恒温的初始速度
//	vec2 sum(0, 0);
//	for (size_t i = 0; i < N; i++)
//	{
//		v[i] = vec2(crand(), crand());
//		sum += v[i];
//	}
//	vec2 del = sum / ((double)N);
//	for (size_t i = 0; i < N; i++)
//	{
//		v[i] -= del;
//		ke += v[i].squaredNorm();
//	}
//	double factor_scale = sqrt(2. * N * TEMP / ke); // 温度标定因子
//	for (size_t i = 0; i < N; i++)
//	{
//		v[i] *= factor_scale;
//	}
//
//	// 计算粒子初始位置
//	for (int i = 0; i < 2 * PLY + 1; i++)
//	{
//		for (int j = 0; j < LEN; j++)
//		{
//			int k = i * LEN + j;
//			x[k] = vec2(
//				(double)j * S + 0.5,
//				0.5 * sqrt(3) * (i + 0.5) * S + BOX_HALF_WIDTH
//			);
//			xm[k] = x[k] - v[k] * DT;
//		}
//	}
//}
//
//void force() {
//	pe = 0.;
//	vec2 dx;
//	double x2 = 0, x2i = 0, x6i = 0, lj = 0;
//
//	for (size_t i = 0; i < N; i++) { f[i] = vec2(0., 0.); }
//
//	for (size_t i = 0; i < N; i++)
//	{
//		for (size_t j = i + 1; j < N; j++)
//		{
//			// 应用周期性边界条件
//			dx = x[i] - x[j];
//			dx.x() -= BOX_LEN * nint(dx.x() / BOX_LEN);
//			dx.y() -= BOX_WIDTH * nint(dx.y() / BOX_WIDTH);
//			x2 = dx.squaredNorm();
//
//			// 如果在截断半径内，计算相互作用力
//			if (x2 < TRUNC_DIST_2)
//			{
//				x2i = pow(x2, -1);
//				x6i = pow(x2i, 3);
//				pe += 4 * x6i * (x6i - 1) - TRUNC_ENERGY;
//				lj = 48 * x2i * x6i * (x6i - 0.5);
//				f[i] += lj * dx;
//				f[j] -= lj * dx;
//			}
//		}
//	}
//}
//
//
//void update() {
//	gamma = 0;  // 控温参数
//	vec2 vh[N]; // 半步速度
//
//	// 更新半步速度和位置
//	for (size_t i = 0; i < N; i++)
//	{
//		vh[i] = v[i] + DT / 2. * (f[i] - gamma * v[i]);
//		x[i] += vh[i] * DT;
//	}
//
//	// 修正跑出盒子的粒子
//	for (size_t i = 0; i < N; i++)
//	{
//		if (x[i].x() >= BOX_LEN) x[i].x() -= BOX_LEN;
//		else if (x[i].x() < 0) x[i].x() += BOX_LEN;
//
//		if (x[i].y() >= BOX_WIDTH) x[i].y() -= BOX_WIDTH;
//		else if (x[i].y() < 0) x[i].y() += BOX_WIDTH;
//	}
//
//	force();
//	ke = 0;
//
//	for (size_t i = 0; i < N; ++i)
//	{
//		f[i] += TEMP1 * vec2(n(e), n(e));
//		v[i] = (vh[i] + f[i] * (DT / 2.)) / TEMP2;
//		ke += (double)(0.5 * v[i].squaredNorm());
//	}
//}
//
//
//void sample() {
//
//}
//
//
//void print_log(int iter) {
//	ofstream os;
//	os.open(LOG_ADDR, std::ios_base::app);
//	os << "Iter " << iter << endl;
//	for (size_t i = 0; i < N; i++) {
//		os << i << "," << x[i].x() << "," << x[i].y() << endl;
//	}
//	os.close();
//}
//
//
//void init_log() {
//	ofstream os;
//	os.open(LOG_ADDR, std::ios_base::out);
//	os << "Iter " << 1 << endl;
//	for (size_t i = 0; i < N; i++) {
//		os << i << "," << x[i].x() << "," << x[i].y() << endl;
//	}
//	os.close();
//}
//
//
//void debug() {
//
//}
//
//
////int main() {
////	/*int n = 1;
////
////	init();
////	print_log(0);
////	start = clock();
////	while (n <= N_STEP)
////	{
////		force();
////		update();
////		if (n % LOG_RNG == 0) {
////			tick = clock();
////			cout << (double)(tick - start) / CLOCKS_PER_SEC << "\t"
////				<< n - LOG_RNG << " to " << n << endl;
////			start = tick;
////			print_log(n);
////		}
////		n++;
////		sample();
////	}*/
////
////	debug();
////
////	return 0;
////}
