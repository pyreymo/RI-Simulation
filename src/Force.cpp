// Force.cpp
#include "Force.hpp"
#include "../cuda/force_kernel.cuh"
#include <cuda_runtime.h>
#include <stdexcept>
#include <vector>

// CUDA错误检查宏
#define CUDA_CHECK(call)                                       \
    do                                                         \
    {                                                          \
        cudaError_t err = call;                                \
        if (err != cudaSuccess)                                \
        {                                                      \
            throw std::runtime_error(cudaGetErrorString(err)); \
        }                                                      \
    } while (0)

void Force::update_2d_gpu(const std::vector<vec2> &x, std::vector<vec2> &f, Box &box)
{
    int N = MolecularDynamics::N;
    double BOX_X = MolecularDynamics::BOX_X;
    double BOX_Y = MolecularDynamics::BOX_Y;
    double CUTOFF_2 = MolecularDynamics::CUTOFF_2;

    // 初始化力向量
    f.assign(N, vec2(0.0, 0.0));

    // 分离x和y坐标
    std::vector<double> h_x(N);
    std::vector<double> h_y(N);
    for (int i = 0; i < N; ++i)
    {
        h_x[i] = x[i].x();
        h_y[i] = x[i].y();
    }

    // 设备内存指针
    double *d_x, *d_y, *d_fx, *d_fy;

    // 分配设备内存
    CUDA_CHECK(cudaMalloc(&d_x, N * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&d_y, N * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&d_fx, N * sizeof(double)));
    CUDA_CHECK(cudaMalloc(&d_fy, N * sizeof(double)));

    // 拷贝数据到设备
    CUDA_CHECK(cudaMemcpy(d_x, h_x.data(), N * sizeof(double), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_y, h_y.data(), N * sizeof(double), cudaMemcpyHostToDevice));

    // 初始化力为0
    CUDA_CHECK(cudaMemset(d_fx, 0, N * sizeof(double)));
    CUDA_CHECK(cudaMemset(d_fy, 0, N * sizeof(double)));

    // 启动 CUDA 内核计算力
    computeForces(d_x, d_y, d_fx, d_fy, N, BOX_X, BOX_Y, CUTOFF_2);

    // 拷贝结果回主机
    std::vector<double> h_fx(N);
    std::vector<double> h_fy(N);
    CUDA_CHECK(cudaMemcpy(h_fx.data(), d_fx, N * sizeof(double), cudaMemcpyDeviceToHost));
    CUDA_CHECK(cudaMemcpy(h_fy.data(), d_fy, N * sizeof(double), cudaMemcpyDeviceToHost));

    // 释放设备内存
    CUDA_CHECK(cudaFree(d_x));
    CUDA_CHECK(cudaFree(d_y));
    CUDA_CHECK(cudaFree(d_fx));
    CUDA_CHECK(cudaFree(d_fy));

    // 更新力向量
    for (int i = 0; i < N; ++i)
    {
        f[i].x() += h_fx[i];
        f[i].y() += h_fy[i];
    }
}
