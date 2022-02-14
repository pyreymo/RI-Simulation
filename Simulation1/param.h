#pragma once
#include <Eigen/Dense>
#include <random>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using array2 = Eigen::Array2d;
using array3 = Eigen::Array3d;

const static double S            = pow(2, 1. / 6);             // ƽ�����
const static int    PLY          = 3;                          // �߲���
const static int    LEN          = 18;                         // �߳���
const static double DT           = 0.001;                      // ʱ�䲽��
const static int    N_STEP       = 150000;                     // ʱ�䲽��
const static int    LOG_STEP     = 1000;                       // ��¼����
const static double TEMP         = 2.2;                        // ��ϵ�¶�
const static int    N            = (2 * PLY + 1) * LEN;        // ��������
const static double TRUNC_DIST   = 2.5 * S;                    // �ضϾ���
const static double TRUNC_DIST_2 = TRUNC_DIST * TRUNC_DIST;    // �ضϾ���
const static double BOX_X        = (LEN + 0.5) * S;            // ���ӳ���
const static double BOX_Y        = sqrt(3) * (10. + PLY) * S;  // ���ӿ��
const static double BOX_Z        = BOX_Y;                      // ���Ӹ߶�
const static double BOX_HALF_Y   = BOX_Y / 2.;                 // ���Ӱ���

const static double sigma = sqrt(2. * TEMP / DT);
const static double HALF_DT = DT * 0.5;
const static double coef1 = (1. / (1 + HALF_DT));

static default_random_engine RAND_ENGINE(time(0));
static normal_distribution<double> NORM_DIST(0, 1);