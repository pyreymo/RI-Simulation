#pragma once
#include <Eigen/Dense>
#include <random>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using array2 = Eigen::Array2d;
using array3 = Eigen::Array3d;

const static double S            = pow(2, 1. / 6);             // 平衡距离
const static int    PLY          = 3;                          // 线层数
const static int    LEN          = 18;                         // 线长度
const static double DT           = 0.001;                      // 时间步长
const static int    N_STEP       = 150000;                     // 时间步数
const static int    LOG_STEP     = 1000;                       // 记录步长
const static double TEMP         = 2.2;                        // 体系温度
const static int    N            = (2 * PLY + 1) * LEN;        // 粒子总数
const static double TRUNC_DIST   = 2.5 * S;                    // 截断距离
const static double TRUNC_DIST_2 = TRUNC_DIST * TRUNC_DIST;    // 截断距离
const static double BOX_X        = (LEN + 0.5) * S;            // 盒子长度
const static double BOX_Y        = sqrt(3) * (10. + PLY) * S;  // 盒子宽度
const static double BOX_Z        = BOX_Y;                      // 盒子高度
const static double BOX_HALF_Y   = BOX_Y / 2.;                 // 盒子半宽度

const static double sigma = sqrt(2. * TEMP / DT);
const static double HALF_DT = DT * 0.5;
const static double coef1 = (1. / (1 + HALF_DT));

static default_random_engine RAND_ENGINE(time(0));
static normal_distribution<double> NORM_DIST(0, 1);