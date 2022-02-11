#pragma once
#include <Eigen/Dense>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;

const static double S            = pow(2, 1 / 6);             // 平衡距离
const static int    PLY          = 2;                         // 线层数
const static int    LEN          = 16;                        // 线长度
const static double DT           = 0.01;                      // 时间步长
const static int    N_STEP       = 50000;                     // 时间步数
const static int    LOG_RNG      = 1000;                      // 记录步长
const static double TEMP         = 0.8;                       // 体系温度
const static int    N            = (2 * PLY + 1) * LEN;       // 粒子总数
const static double TRUNC_DIST   = 2.5 * S;                   // 截断距离
const static double BOX_X        = (LEN + 0.5) * S;           // 盒子长度
const static double BOX_Y        = sqrt(3) * (10. + PLY) * S; // 盒子宽度
const static double BOX_Z        = BOX_Y;                     // 盒子高度
const static string LOG_ADDR     = "sim.txt";                 // 日志地址
const static double TRUNC_ENERGY = -0.016316891136;           // 截断能量
const static double BOX_HALF_Y   = BOX_Y / 2.;                // 盒子半宽度
const static double TRUNC_DIST_2 = pow(TRUNC_DIST, 2);        // 截断距离平方