#pragma once
#include <Eigen/Dense>
#include <random>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using array2 = Eigen::Array2d;
using array3 = Eigen::Array3d;

const static double S            = pow(2, 1. / 6);            // ƽ�����
const static int    PLY          = 1;                         // �߲���
const static int    LEN          = 64;                        // �߳���
const static double DT           = 0.01;                      // ʱ�䲽��
const static int    N_STEP       = 12000;                     // ʱ�䲽��
const static int    LOG_STEP     = N_STEP / 100.;             // ��¼����
const static double TEMP         = 0.48;                      // ��ϵ�¶�
const static int    N            = (2 * PLY + 1) * LEN;       // �������� - 2D
//const static int    N          = (3 * PLY * (PLY + 1) + 1) * LEN;  // �������� - 3D
const static double TRUNC_DIST   = 5. * S;                    // �ضϾ���
const static double TRUNC_DIST_2 = TRUNC_DIST * TRUNC_DIST;   // �ضϾ���
const static double BOX_X        = (LEN + 0.5) * S;           // ���ӳ��� - 2D
//const static double BOX_X      = (LEN + 0.5) * sqrt(6) / 3. * S;  // ���ӳ��� - 3D
const static double BOX_Y        = sqrt(3) * (20. + PLY) * S; // ���ӿ�� - 2D
//const static double BOX_Y      = sqrt(3) * (10. + PLY) * S;  // ���ӿ�� - 3D
const static double BOX_Z        = BOX_Y;                     // ���Ӹ߶� - 3D
const static double BOX_HALF_Y   = BOX_Y / 2.;                // ���Ӱ��
const static double BOX_HALF_Z   = BOX_Z / 2.;                // ���Ӱ�� - 3D

const static double sigma = sqrt(2. * TEMP / DT);
const static double HALF_DT = DT * 0.5;
const static double coef1 = (1. / (1 + HALF_DT));

static default_random_engine RAND_ENGINE(time(0));
static normal_distribution<double> NORM_DIST(0, 1);