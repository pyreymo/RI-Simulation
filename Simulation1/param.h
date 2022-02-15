#pragma once
#include <Eigen/Dense>
#include <random>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using array2 = Eigen::Array2d;
using array3 = Eigen::Array3d;

const static double S            = pow(2, 1. / 6);            // 平衡距离
const static int    PLY          = 1;                         // 线层数
const static int    LEN          = 64;                        // 线长度
const static double DT           = 0.01;                      // 时间步长
const static int    N_STEP       = 12000;                     // 时间步数
const static int    LOG_STEP     = N_STEP / 100.;             // 记录步长
const static double TEMP         = 0.48;                      // 体系温度
const static int    N            = (2 * PLY + 1) * LEN;       // 粒子总数 - 2D
//const static int    N          = (3 * PLY * (PLY + 1) + 1) * LEN;  // 粒子总数 - 3D
const static double TRUNC_DIST   = 5. * S;                    // 截断距离
const static double TRUNC_DIST_2 = TRUNC_DIST * TRUNC_DIST;   // 截断距离
const static double BOX_X        = (LEN + 0.5) * S;           // 盒子长度 - 2D
//const static double BOX_X      = (LEN + 0.5) * sqrt(6) / 3. * S;  // 盒子长度 - 3D
const static double BOX_Y        = sqrt(3) * (20. + PLY) * S; // 盒子宽度 - 2D
//const static double BOX_Y      = sqrt(3) * (10. + PLY) * S;  // 盒子宽度 - 3D
const static double BOX_Z        = BOX_Y;                     // 盒子高度 - 3D
const static double BOX_HALF_Y   = BOX_Y / 2.;                // 盒子半宽
const static double BOX_HALF_Z   = BOX_Z / 2.;                // 盒子半高 - 3D

const static double sigma = sqrt(2. * TEMP / DT);
const static double HALF_DT = DT * 0.5;
const static double coef1 = (1. / (1 + HALF_DT));

static default_random_engine RAND_ENGINE(time(0));
static normal_distribution<double> NORM_DIST(0, 1);