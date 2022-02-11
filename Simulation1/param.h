#pragma once
#include <Eigen/Dense>

using namespace std;
using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;

const static double S            = pow(2, 1 / 6);             // ƽ�����
const static int    PLY          = 2;                         // �߲���
const static int    LEN          = 16;                        // �߳���
const static double DT           = 0.01;                      // ʱ�䲽��
const static int    N_STEP       = 50000;                     // ʱ�䲽��
const static int    LOG_RNG      = 1000;                      // ��¼����
const static double TEMP         = 0.8;                       // ��ϵ�¶�
const static int    N            = (2 * PLY + 1) * LEN;       // ��������
const static double TRUNC_DIST   = 2.5 * S;                   // �ضϾ���
const static double BOX_X        = (LEN + 0.5) * S;           // ���ӳ���
const static double BOX_Y        = sqrt(3) * (10. + PLY) * S; // ���ӿ��
const static double BOX_Z        = BOX_Y;                     // ���Ӹ߶�
const static string LOG_ADDR     = "sim.txt";                 // ��־��ַ
const static double TRUNC_ENERGY = -0.016316891136;           // �ض�����
const static double BOX_HALF_Y   = BOX_Y / 2.;                // ���Ӱ���
const static double TRUNC_DIST_2 = pow(TRUNC_DIST, 2);        // �ضϾ���ƽ��