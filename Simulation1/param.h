#pragma once
#include <Eigen/Dense>
//#include <random>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using array2 = Eigen::Array2d;
using array3 = Eigen::Array3d;

#define TWO_DIMENSIONAL_SIMULATION 1;

const static int    PLY        = 10;                               // �߲���
const static int    LEN        = 20;                               // �߳���
const static double TEMP       = 0.44;                             // ��ϵ�¶�
const static double TIME_STEP  = 1e-3;                             // ʱ�䲽��
const static int    RESCALE    = 1;                                // ���²���
const static double HALF_DT    = TIME_STEP * 0.5;                  // ʱ��벽��
const static int    ITER_NUM   = 4e5;                              // ʱ�䲽��
const static int    LOG_STEP   = ITER_NUM / 200.;                  // ��¼����
const static double S          = pow(2, 1. / 6);                   // ƽ�����
const static double CUTOFF     = 5. * S;                           // �ضϾ���
const static double CUTOFF_2   = CUTOFF * CUTOFF;                  // �ضϾ���
#ifdef TWO_DIMENSIONAL_SIMULATION
const static int    N          = (2 * PLY + 1) * LEN;              // ��������
const static double BOX_X      = (LEN + 0.5) * S;                  // ���ӳ���
const static double BOX_Y      = sqrt(3) * (40. + PLY) * S;        // ���ӿ��
const static double BOX_HALF_Y = BOX_Y / 2.;                       // ���Ӱ��
#else
const static int    N          = (3 * PLY * (PLY + 1) + 1) * LEN;  // ��������
const static double BOX_X      = (LEN + 0.5) * sqrt(6) / 3. * S;   // ���ӳ���
const static double BOX_Y      = sqrt(3) * (10. + PLY) * S;        // ���ӿ��
const static double BOX_HALF_Y = BOX_Y / 2.;                       // ���Ӱ��
const static double BOX_Z      = BOX_Y;                            // ���Ӹ߶�
const static double BOX_HALF_Z = BOX_Z / 2.;                       // ���Ӱ��
#endif

const static double BT_TAU = 1;
//const static double sigma = sqrt(2. * TEMP / TIME_STEP);
//const static double coef1 = (1. / (1 + HALF_DT));
//static default_random_engine RAND_ENGINE(time(0));
//static normal_distribution<double> NORM_DIST(0, 1);